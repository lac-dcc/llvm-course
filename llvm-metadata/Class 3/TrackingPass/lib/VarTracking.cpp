//===-- VarTracking.cpp ----------------------------------------------===//
// Copyright (C) 2021  José Wesley de S. Magalhães
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
/// This file contains the implementation of the VarTracking pass which 
/// prints the tracking of a source code variable.
//===----------------------------------------------------------------------===//

#include "../include/VarTracking.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstIterator.h" //To use the instructions iterator
#include "llvm/IR/DebugInfo.h"

#define DEBUG_TYPE "VarTracking"

using namespace llvm;

void VarTracking::handleDbgVariableIntrinsic(DbgVariableIntrinsic* DVI){
  DILocalVariable* Var = DVI->getVariable();
  
  
  if(DVI->isAddressOfVariable()){
    Value* Address = dyn_cast<DbgDeclareInst>(DVI)->getAddress();
    errs() << "Describing an address of a variable in the stack " << Var->getName() << "\n";
    errs() << "Address in the IR: "; Address->dump();
    MDNode* MD = DVI->getMetadata("dbg");
    DILocation* Loc = dyn_cast<DILocation>(MD);
    errs() << "At line " <<  Loc->getLine() <<" of function " << DVI->getFunction()->getName() <<"\n\n";
  }
  else{
    Value* NewVal = dyn_cast<DbgValueInst>(DVI)->getValue();
    
    //We don't deal with Phi functions because they don't have a straight correspondent at the source code.
    if(isa<PHINode>(NewVal))
      return;
      
    errs() << "Variable " << Var->getName() << " assigned to a new value. \n";
    
    if(Constant* C = dyn_cast<Constant>(NewVal)){
      errs() << "It is a constant value.\n\n";
      if(C->isNullValue())
        errs() << "And it is null.\n\n";
    }
    else if(isa<UndefValue>(NewVal)) 
      errs() << "It is an undefined value\n\n";
    
    else if(isa<AllocaInst>(NewVal))
      errs() << "It is an address of a variable\n\n";
    
    else{
      if(Instruction* ValAsInst = dyn_cast<Instruction>(NewVal)){
        if(ValAsInst->hasMetadata("dbg")){
          MDNode* MD = dyn_cast<Instruction>(NewVal)->getMetadata("dbg");
          DILocation* Loc = dyn_cast<DILocation>(MD);
          errs() << "At line " <<  Loc->getLine() <<" of function " << DVI->getFunction()->getName() <<"\n\n";
        }
      }
    }
  }
}

bool VarTracking::runOnModule(Module &M){
  errs() << "****************************************************************************\n";  
  
  for(Function &F : M){
    for(Instruction &I : instructions(F)){
    
      if(DbgVariableIntrinsic* DVI = dyn_cast<DbgVariableIntrinsic>(&I))
          handleDbgVariableIntrinsic(DVI);
    }
  }
  
  errs() << "****************************************************************************\n";
  return false;
  
}

char VarTracking::ID = 0;
static RegisterPass<VarTracking> X("vartrack", "Variable Tracking Pass");
