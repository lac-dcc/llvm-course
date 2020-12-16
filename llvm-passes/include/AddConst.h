//===-- AddConst.h ----------------------------------------------*- C++ -*-===//
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
/// This file contains the declaration of the analysis used to collect all add
/// instructions within a function.
///
//===----------------------------------------------------------------------===//

#ifndef ADD_CONST_H
#define ADD_CONST_H

#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"

namespace addconst {
/// An analysis that traverses a function and collects all the "add"
/// instructions with constant operands.
struct AddConstAnalysis : public llvm::AnalysisInfoMixin<AddConstAnalysis> {
    /// Result of the analysis: a list of instructions of type
    /// "BinaryOperator", opcode "add" and constant operands.
    using Result = llvm::SmallVector<llvm::BinaryOperator *, 0>;
    /// Traverses the function \p F, collecting all the "add" instructions
    /// inside it.
    ///
    /// \returns a list of all the collected "add" instructions.
    Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
    // A special type used by analysis passes to provide an address that
    // identifies that particular analysis pass type.
    static llvm::AnalysisKey Key;
};

/// A wrapper around AddAnalysis to be used with "opt -passes=" to print the
/// collected add instructions.
struct AddConstPrinterPass : public llvm::PassInfoMixin<AddConstPrinterPass> {
    /// Takes a ostream \p OS and constructs an instance of the
    // AddPrinterClass.
    explicit AddConstPrinterPass(llvm::raw_ostream &OS) : OS(OS) {}
    /// Run the AddAnalysis on function \p F and prints its result.
    ///
    /// \returns llvm::PreservedAnalyses::all(), since nothing changed.
    llvm::PreservedAnalyses run(llvm::Function &F,
                                llvm::FunctionAnalysisManager &FAM);

  private:
    llvm::raw_ostream &OS;
};

/// A transformation pass that evaluates all constant-only add instructions
/// and replaces their uses by the computed constant.
struct AddConstPass : public llvm::PassInfoMixin<AddConstPass> {
    /// Gets the result of AddConstAnalysis for the function \p F and uses it
    /// to replace the uses of the collected add instructions by their final
    /// value.
    ///
    /// \returns set of preserved analyses (all of them, except for
    /// AddConstAnalysis).
    llvm::PreservedAnalyses run(llvm::Function &F,
                                llvm::FunctionAnalysisManager &FAM);
};
} // namespace addconst

#endif
