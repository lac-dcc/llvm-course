//===-- Main.cpp ----------------------------------------------------------===//
// Copyright (C) 2020  Luigi D. C. Soares, Augusto Dias Noronha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//===----------------------------------------------------------------------===//
///
/// \file
/// A command-line tool to evaluate add instructions with only constant
/// operands at compile time.
///
//===----------------------------------------------------------------------===//

#include "AddConst.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

/// A category for the options specified for this tool.
static cl::OptionCategory AddConstCategory("addconst pass options");

/// A required argument that specifies the module that will be transformed.
static cl::opt<std::string> InputModule(cl::Positional,
                                        cl::desc("<Input module>"),
                                        cl::value_desc("bitcode filename"),
                                        cl::init(""), cl::Required,
                                        cl::cat(AddConstCategory));

/// An optional argument that specifies the name of the output file.
static cl::opt<std::string> OutputModule("o", cl::Positional,
                                         cl::desc("<Output module>"),
                                         cl::value_desc("bitcode filename"),
                                         cl::init("out.ll"),
                                         cl::cat(AddConstCategory));

int main(int Argc, char **Argv) {
    // Hide all options apart from the ones specific to this tool.
    cl::HideUnrelatedOptions(AddConstCategory);

    // Parse the command-line options that should be passed to the invariant
    // pass.
    cl::ParseCommandLineOptions(
        Argc, Argv, "evaluate constant add instructions at compile time.\n");

    // Makes sure llvm_shutdown() is called (which cleans up LLVM objects)
    // http://llvm.org/docs/ProgrammersManual.html#ending-execution-with-llvm-shutdown
    llvm_shutdown_obj SDO;

    // Parse the IR file passed on the command line.
    SMDiagnostic Err;
    LLVMContext Ctx;
    std::unique_ptr<Module> M = parseIRFile(InputModule.getValue(), Err, Ctx);

    if (!M) {
        errs() << "Error reading bitcode file: " << InputModule << "\n";
        Err.print(Argv[0], errs());
        return -1;
    }

    // Create a FunctionPassManager and add the AddConstPass to it:
    addconst::AddConstPass Pass;
    FunctionPassManager FPM;
    FPM.addPass(Pass);

    // Create a FunctionAnalysisManager and add the AddConstAnalysis to it:
    FunctionAnalysisManager FAM;
    FAM.registerPass([&] { return addconst::AddConstAnalysis(); });

    // Register the module analyses:
    PassBuilder PB;
    PB.registerFunctionAnalyses(FAM);

    // Finally, run the passes registered with FPM.
    for (Function &F : *M) FPM.run(F, FAM);

    std::error_code EC;
    raw_fd_ostream OS(OutputModule.getValue(), EC);

    if (EC) {
        errs() << "Couldn't open " << OutputModule.getValue() << ": "
               << EC.message() << "\n";
        return -1;
    }

    // Write the transformed code into the output file.
    M->print(OS, nullptr);
    OS.close();

    return 0;
}
