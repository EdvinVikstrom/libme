#ifndef LIBME_LANG_AST_INTEGER_HPP
  #define LIBME_LANG_AST_INTEGER_HPP

#include "libme/lang/ast/Expression.hpp"
#include "libme/lang/interpreter/Value.hpp"

namespace me::lang {

  class IntegerExpr : public Expression {

  private:

    SharedPtr<IntegerVal> m_value;

  public:

    IntegerExpr(int integer)
      : m_value(make_shared<IntegerVal>(integer)) { }
    ~IntegerExpr() override = default;

    SharedPtr<IntegerVal> get_value() const { return m_value; }

    SharedPtr<Variable> execute(Interpreter &interpreter) override;
    void to_string(String &str) override;

  };

}

#endif
