//===-- AddConstPass.cpp --------------------------------------------------===//
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
/// This file contains the implementation of the AddConstPass, which uses
/// AddConstAnalysis to get all the constant-only add instructions and replace
/// their uses by their final values.
///
//===----------------------------------------------------------------------===//

#include "AddConst.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

namespace addconst {
void ReplaceAddInstWithConstant(BinaryOperator *BO) {
    assert(BO->getOpcode() == Instruction::BinaryOps::Add);
    auto Fst = cast<ConstantInt>(BO->getOperand(0));
    auto Snd = cast<ConstantInt>(BO->getOperand(1));
    auto Sum = ConstantExpr::getAdd(Fst, Snd);
    BO->replaceAllUsesWith(Sum);
    BO->eraseFromParent();
}

PreservedAnalyses AddConstPass::run(Function &F, FunctionAnalysisManager &FAM) {
    auto &AddInsts = FAM.getResult<AddConstAnalysis>(F);
    for (auto BO : AddInsts) ReplaceAddInstWithConstant(BO);
    auto PA = PreservedAnalyses::all();
    PA.abandon<AddConstAnalysis>();
    return PA;
}
} // namespace addconst
