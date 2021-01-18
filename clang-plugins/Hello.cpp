// Usage: clang -cc1 -load libHello.so -plugin hello example.c -plugin-arg-hello arguments

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Lex/Pragma.h"
#include "clang/Lex/Preprocessor.h"


class HelloVisitor : public clang::RecursiveASTVisitor<HelloVisitor> {
public:

  bool VisitFunctionDecl(clang::FunctionDecl *F) {
    F->dump();
    return true;
  }

};

class HelloConsumer : public clang::ASTConsumer {
public:
  void HandleTranslationUnit(clang::ASTContext &Context) override {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  HelloVisitor Visitor;
};

class HelloAction : public clang::PluginASTAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
      return std::unique_ptr<clang::ASTConsumer>(new HelloConsumer);
    }

protected:
  bool ParseArgs(const clang::CompilerInstance &Compiler, 
                 const std::vector<std::string> &args) override {
    return true;
  }
};

static clang::FrontendPluginRegistry::Add<HelloAction>
X("hello", "Hello world plugin");