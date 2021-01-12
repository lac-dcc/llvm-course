//===-- SignatureRecover.cpp ----------------------------------------------===//
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
/// This file contains the implementation of the SignatureRecover pass which 
/// reconstructs signatures of functions using LLVM Metadata
//===----------------------------------------------------------------------===//

#include "../include/SignatureRecover.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/DebugInfo.h" //To use DebugInfoFinder class
#include "llvm/IR/DebugInfoMetadata.h" //To use metadata types

#define DEBUG_TYPE "RecSign"

using namespace llvm;

void SignatureRecover::detailUDType(DIType* UDType){
  if(DICompositeType* Composite = dyn_cast<DICompositeType>(UDType)){
    if(Composite->getTag() == dwarf::DW_TAG_structure_type)
      errs() << "struct ";
    if(Composite->getTag() == dwarf::DW_TAG_union_type)
      errs() << "union ";
    if(Composite->getTag() == dwarf::DW_TAG_enumeration_type)
      errs() << "enum ";
    
    errs() << UDType->getName() <<"\n";
    errs() << " Elements: \n";
    
    DINodeArray Elements = Composite->getElements();
    for(unsigned i = 0; i < Elements.size(); i++){
     DIDerivedType* Field = dyn_cast<DIDerivedType>(Elements[i]);
     errs() <<"\t" << Field->getName() << ". Type: ";
     analyzeDebugType(Field);
    }
  }
  else{
    if(DIDerivedType* Derived = dyn_cast<DIDerivedType>(UDType)){
      errs() << "typedef ";
      analyzeDebugType(Derived->getBaseType());
    }
  }
  
  errs() << "\n";
}

std::string SignatureRecover::getBasicTypeStr(unsigned DwarfTag){
  std::string TypeStr;
  switch (DwarfTag){
    case dwarf::DW_ATE_address:
      TypeStr =  "address of variable";
      break;
      
   case dwarf::DW_ATE_boolean:
     TypeStr = "boolean";
     break;
     
   case dwarf::DW_ATE_float:
     TypeStr = "float";
     break;
     
   case dwarf::DW_ATE_signed:
     TypeStr = "integer";
     break;
     
   case dwarf::DW_ATE_signed_char:
     TypeStr = "char";
     break;
     
   case dwarf::DW_ATE_unsigned:
     TypeStr = "unsigned integer";
     break;
     
   case dwarf::DW_ATE_unsigned_char:
     TypeStr = "unsigned char";
     break;
     
   default:
      errs() << "Unknown basic type!\n";
      break;
  }
        
  return TypeStr + "\n";
}

void SignatureRecover::analyzeDebugType(DIType* DIT){
  if(DIBasicType* Basic = dyn_cast<DIBasicType>(DIT)){
    errs() << getBasicTypeStr(Basic->getEncoding());
  }
  
  if(DIDerivedType* Derived = dyn_cast<DIDerivedType>(DIT)){
    if(Derived->getTag() == dwarf::DW_TAG_pointer_type)
      errs() << "pointer to ";
    if(Derived->getTag() == dwarf::DW_TAG_const_type)
      errs() << "const ";
    if(Derived->getTag() == dwarf::DW_TAG_reference_type)
      errs() << "reference to ";
        
    analyzeDebugType(Derived->getBaseType());
  }
  
  if(DICompositeType* Composite = dyn_cast<DICompositeType>(DIT)){
    if(Composite->getTag() == dwarf::DW_TAG_array_type)
      errs() << "array of ";
    
    if(Composite->getTag() == dwarf::DW_TAG_structure_type || Composite->getTag() == dwarf::DW_TAG_union_type || Composite->getTag() == dwarf::DW_TAG_enumeration_type)
      errs() << Composite->getName() <<"\n";
  }
  
  /*if(DISubroutineType* STR = dyn_cast<DISubroutineType>(DIT))
    SignatureRecover(DIT->  );*/
  
}

void SignatureRecover::analyzeSubprogram(DISubprogram* DIS){
  errs() << "Function: " << DIS->getName() <<" ";
  errs() << "at line " << DIS->getLine() <<"\n";
  DISubroutineType* SRT = DIS->getType();
  DITypeRefArray FuncTypes = SRT->getTypeArray();
  for(unsigned i = 0; i < FuncTypes.size(); i++){
    if(i == 0){
      errs() << "Return type: ";
      if(FuncTypes[i] == nullptr){
        errs() << "void\n";
        continue;
      }
    }
    else
      errs() << "Argument " << std::to_string(i) << " type: ";
    
    analyzeDebugType(FuncTypes[i]);
  }
  
  errs() <<"\n";
  
}

bool SignatureRecover::runOnModule(Module &M){
  DebugInfoFinder DBF;
  DBF.processModule(M);
  errs() << "****************************************************************************\n";  
  
  for(DISubprogram* DIS : DBF.subprograms())
    analyzeSubprogram(DIS);
  
  errs() << "User defined types:\n";
  for(DIType* DIT : DBF.types()){
    if(DIDerivedType* Derived = dyn_cast<DIDerivedType>(DIT)){
      if(Derived->getTag() == dwarf::DW_TAG_typedef)
        detailUDType(DIT);
    }
    
    if(isa<DICompositeType>(DIT))
      detailUDType(DIT);
  }
  
  return false;
  
}

char SignatureRecover::ID = 0;
static RegisterPass<SignatureRecover> X("recsign", "Signature Reconstructor Pass");
