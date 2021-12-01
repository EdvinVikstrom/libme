#ifndef LIBME_LANG_AST_VARIABLE_HPP
  #define LIBME_LANG_AST_VARIABLE_HPP

#include "libme/lang/ast/Expression.hpp"

namespace me::lang {

  class VariableExpr : public Expression {

  private:

    const StringView m_name;

  public:

    VariableExpr(const StringView &name)
      : m_name(name) { }
    ~VariableExpr() override = default;

    const StringView& get_name() const { return m_name; }

    SharedPtr<Variable> execute(Interpreter &interpreter) override;
    void to_string(String &str) override;

  };

}

#endif
