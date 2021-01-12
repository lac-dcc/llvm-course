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

	/**
		* This methods prints information about a user-defined type. It access every field
		* and prints their names and types.
		* @param Output_File_Ptr is the pointer to the type of the output file.
		*/
	void detailUDType(llvm::DIType* UDType);

	/**
		* This methods returns a string containing the name of a basic debug type. It uses
		* the DWARF tag of the LLVM Debug type to identify it. 
		* @param DwarfTag is the dwarf tag that identifies a Debug type.
		* @return a string corresponding to name of the type.
		*/
	std::string getBasicTypeStr(unsigned DwarfTag);

	/**
		* This methods prints information about a LLVM Debug type. 
		* @param DIT is the debug type to be inspected.
		*/
	void analyzeDebugType(llvm::DIType* DIT);

	/**
		* This methods analyzes a subprogram. It prints its name and call methods to inspect the
	  * arguments of such subprogram (function).
		* @param DIS is the subprogram to be analyzed.
		*/
	void analyzeSubprogram(llvm::DISubprogram* DIS);
};

#endif
