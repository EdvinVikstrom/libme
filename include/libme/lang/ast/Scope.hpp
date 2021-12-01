#ifndef LIBME_LANG_AST_SCOPE_HPP
  #define LIBME_LANG_AST_SCOPE_HPP

#include "libme/lang/ast/Expression.hpp"
#include "libme/UniquePtr.hpp"
#include "libme/Vector.hpp"

namespace me::lang {

  class ScopeExpr : public Expression {

  private:

    Vector<UniquePtr<Expression>> m_body;

  public:

    ScopeExpr(Vector<UniquePtr<Expression>> body)
      : m_body(move(body)) { }
    ~ScopeExpr() override = default;

    const Vector<UniquePtr<Expression>>& get_expressions() const { return m_body; }

    SharedPtr<Variable> execute(Interpreter &interpreter) override;
    void to_string(String &str) override;

  };

}

#endif
