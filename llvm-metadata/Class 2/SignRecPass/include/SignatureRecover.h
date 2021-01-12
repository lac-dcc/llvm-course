//===-- AddConst.h ----------------------------------------------*- C++ -*-===//
// Copyright (C) 2021  José Wesley S. Magalhães
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
/// This file contains the declaration of the analysis used to reconstruct
/// the signature of a function using LLVM Metadata
///
//===----------------------------------------------------------------------===//

#ifndef RECSIGN_H
#define RECSIGN_H

#include "llvm/IR/Module.h"
#include "llvm/Pass.h"


class SignatureRecover : public llvm::ModulePass {
	public:
		static char ID; // Pass identification, replacement for typeid

		//! Class constructor. To initialize the pass identifier.
		SignatureRecover() : ModulePass(ID) {}

		//! Class destructor.
		~SignatureRecover() {}

		//! This method performs the work of the LLVM pass.
		/*! It processes an LLVM IR file of a program, which contains all the information attached to that
		@param M is an LLVM Module, which is the IR form of the program.
		@return true if the program is modified, or false otherwise.
		*/
		bool runOnModule(llvm::Module &M) override;

	private:

	void detailUDType(llvm::DIType* UDType);
	std::string getBasicTypeStr(unsigned DwarfTag);
	void analyzeDebugType(llvm::DIType* DIT);
	void analyzeSubprogram(llvm::DISubprogram* DIS);
};

#endif
