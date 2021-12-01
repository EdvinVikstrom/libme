#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include <clang/Frontend/FrontendAction.h>
#include <llvm/ADT/StringRef.h>

namespace test {

  class ClassVisitor : public clang::RecursiveASTVisitor<ClassVisitor> {

  private:

    clang::ASTContext* m_context;

  public:

    void set_context(clang::ASTContext* context)
    {
      m_context = context;
    }

    bool VisitFunctionDecl(clang::FunctionDecl *fd) override
    {
      ::printf("Function!\n");
      return true;
    }

  };

  class FunctionGenerator : public clang::ASTConsumer {

  private:

    ClassVisitor m_visitor;

  public:

    void HandleTranslationUnit(clang::ASTContext &ctx) override
    {
      m_visitor.set_context(&ctx);
      m_visitor.TraverseDecl(ctx.getTranslationUnitDecl());
    }

  };

  class FuncGenASTAction : public clang::PluginASTAction {

  public:

    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &compiler, llvm::StringRef in_file) override
    {
      (void) compiler;
      (void) in_file;
      return std::make_unique<FunctionGenerator>();
    }

    bool ParseArgs(const clang::CompilerInstance &ci, const std::vector<std::string>& args) override
    {
      return true;
    }

  };

}

static clang::FrontendPluginRegistry::Add<FuncGenASTAction>
X("FuncGenClangPlugin", "FuncGen Clang Plugin");
