//===-- AddConstAnalysis.cpp ----------------------------------------------===//
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
/// This file contains the implementation of the AddConstAnalysis pass as well
/// as the AddConstPrinterPass.
//===----------------------------------------------------------------------===//

#include "AddConst.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/Casting.h"

using namespace llvm;

namespace addconst {
/// Takes an instruction and checks whether its operands are constant or not.
///
/// \returns true if all operands are constant; otherwise, returns false.
bool isConstantIntOnly(Instruction &I) {
    for (Use &Op : I.operands()) {
        // Check if the operand is a constant integer:
        if (!isa<ConstantInt>(Op)) return false;
    }
    // Return true if all operands are constant integer.
    return true;
}

// Initialize the analysis key.
AnalysisKey AddConstAnalysis::Key;

AddConstAnalysis::Result AddConstAnalysis::run(Function &F,
                                               FunctionAnalysisManager &FAM) {
    SmallVector<BinaryOperator *, 0> AddInsts;
    for (BasicBlock &BB : F) {
        for (Instruction &I : BB) {
            // First, check if "I" is an instance of BinaryOperator:
            if (!I.isBinaryOp()) continue;
            // If it is, check if its opcode is "Add":
            if (!(I.getOpcode() == Instruction::BinaryOps::Add)) continue;
            // Check if all operands are constant integer:
            if (!isConstantIntOnly(I)) continue;
            // If it is "Add", append it to the result vector:
            AddInsts.push_back(&cast<BinaryOperator>(I));
        }
    }
    return AddInsts;
}

PreservedAnalyses AddConstPrinterPass::run(Function &F,
                                           FunctionAnalysisManager &FAM) {
    auto &AddInsts = FAM.getResult<AddConstAnalysis>(F);
    OS << "=============================================\n";
    OS << "|| " << F.getName() << " ||\n";
    OS << "=============================================\n";
    for (auto &Add : AddInsts) OS << *Add << "\n";
    OS << "=============================================\n";
    return PreservedAnalyses::all();
}
} // namespace addconst
