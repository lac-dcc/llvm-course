//===-- AddConstPlugin.cpp ------------------------------------------------===//
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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//===----------------------------------------------------------------------===//
///
/// \file
/// This file is the entry point for the New PM opt plugin. That is, it
/// contains the New PM registration for all the analyses and transformations
/// related to the AddConst plugin.
//===----------------------------------------------------------------------===//
//
#include "AddConst.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

PassPluginLibraryInfo getAddConstPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "AddConst", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                // 1: Register the AddConstAnalysis as an analysis pass so that
                // it can be requested by other passes as following:
                // FPM.getResult<AddConstAnalysis>(F), where FPM is the
                // FunctionAnalysisManager and F is the Function that shall be
                // analyzed.
                PB.registerAnalysisRegistrationCallback(
                    [](FunctionAnalysisManager &FAM) {
                        FAM.registerPass(
                            [&] { return addconst::AddConstAnalysis(); });
                    });

                // 2: Register the AddConstPrinterPass as "print<add-const>" so
                // that it can be used when specifying pass pipelines with
                // "-passes=". Also register AddConstPass as "add-const".
                PB.registerPipelineParsingCallback(
                    [&](StringRef Name, FunctionPassManager &FPM,
                        ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "print<add-const>") {
                            FPM.addPass(addconst::AddConstPrinterPass(errs()));
                            return true;
                        }

                        if (Name == "add-const") {
                            FPM.addPass(addconst::AddConstPass());
                            return true;
                        }

                        return false;
                    });
            }};
}

// The public entry point for a pass plugin:
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getAddConstPluginInfo();
}
