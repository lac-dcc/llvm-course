// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;
using namespace clang::tooling;


static llvm::cl::OptionCategory MatcherCategory("matcher options");

StatementMatcher forCond = forStmt(
                            hasLoopInit(
                              declStmt(
                                hasSingleDecl(
                                  varDecl(
                                    hasInitializer(
                                      integerLiteral(
                                        equals(0)))).bind("init_var")))));

class MatchPrinter: public MatchFinder::MatchCallback {

public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const clang::VarDecl *var = Result.Nodes.getNodeAs<clang::VarDecl>("init_var"))
    	llvm::outs() << var-> getNameAsString();
  }
};


int main(int argc, const char **argv) {
  CommonOptionsParser OptionsParser(argc, argv, MatcherCategory);
  ClangTool Matcher(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

  MatchPrinter Printer; 
  MatchFinder Finder;
  Finder.addMatcher(traverse(clang::TK_IgnoreUnlessSpelledInSource, forCond), &Printer);
  Matcher.run(newFrontendActionFactory(&Finder).get());
  
  return 0;
}


// StatementMatcher forCond =  forStmt(hasCondition(
//                        binaryOperator(
//                             hasOperatorName("<"),
//                                 hasLHS(ignoringParenImpCasts(declRefExpr(
//                                    to(varDecl(hasType(isInteger())).bind("condVarName"))))),
//                        hasRHS(
//                            expr(
//                              hasType(
//                                isInteger())).bind("condValue")))));







// int main(int argc, const char **argv) {
//   CommonOptionsParser OptionsParser(argc, argv, MatcherCategory);
//   ClangTool Matcher(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

//   LoopPrinter Printer; 
//   MatchFinder Finder;
//   Finder.addMatcher(traverse(clang::TK_IgnoreUnlessSpelledInSource, forCond), &Printer);
//   Matcher.run(newFrontendActionFactory(&Finder).get());
  
//   return 0;
// }
