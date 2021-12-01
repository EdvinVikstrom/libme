#ifndef LIBME_LANG_AST_FUNCTION_HPP
  #define LIBME_LANG_AST_FUNCTION_HPP

#include "libme/lang/ast/Expression.hpp"
#include "libme/UniquePtr.hpp"

namespace me::lang {

  class FunctionExpr : public Expression {

  private:

    const StringView m_name;
    UniquePtr<Expression> m_scope;

  public:

    FunctionExpr(const StringView &name, UniquePtr<Expression> scope)
      : m_name(name), m_scope(move(scope)) { }
    ~FunctionExpr() override = default;

    const StringView& get_name() const { return m_name; }
    const UniquePtr<Expression>& get_scope() const { return m_scope; }

    SharedPtr<Variable> execute(Interpreter &interpreter) override;
    void to_string(String &str) override;

  };

}

#endif
