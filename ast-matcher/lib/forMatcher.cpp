// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace llvm;
using namespace clang::ast_matchers;
using namespace clang::tooling;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static cl::OptionCategory MatcherCategory("matcher options");

StatementMatcher forCond = forStmt(
                            hasLoopInit(
                              declStmt(
                                hasSingleDecl(
                                  varDecl(
                                    hasInitializer(
                                      integerLiteral(
                                        equals(0)))).bind("init_var")))));

StatementMatcher LoopMatcher =
  forStmt(hasLoopInit(declStmt(hasSingleDecl(varDecl(
    hasInitializer(integerLiteral(equals(0)))))))).bind("forLoop");

class MatchPrinter: public MatchFinder::MatchCallback {
    public:
    virtual void run(const MatchFinder::MatchResult &Result) {
        if (const clang::VarDecl *var = Result.Nodes.getNodeAs<clang::VarDecl>("init_var"))
          outs() << var->getNameAsString() << "\n";
    }
};

int main(int argc, const char **argv) {
  auto ExpectedParser = CommonOptionsParser::create(argc, argv, MatcherCategory);

  if (!ExpectedParser) {
    // Fail gracefully for unsupported options.
    llvm::errs() << ExpectedParser.takeError();
    return 1;
  }

  CommonOptionsParser& OptionsParser = ExpectedParser.get();

  ClangTool Tool(OptionsParser.getCompilations(), 
                 OptionsParser.getSourcePathList());

  //return Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get());

  MatchPrinter Printer; 
	MatchFinder Finder;
	Finder.addMatcher(traverse(clang::TK_IgnoreUnlessSpelledInSource, forCond), &Printer);
  return Tool.run(newFrontendActionFactory(&Finder).get());
}