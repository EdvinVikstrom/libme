#ifndef LIBME_LANG_AST_STRING_HPP
  #define LIBME_LANG_AST_STRING_HPP

#include "libme/lang/ast/Expression.hpp"
#include "libme/lang/interpreter/Value.hpp"

namespace me::lang {

  class StringExpr : public Expression {

  private:

    SharedPtr<StringVal> m_value;

  public:

    StringExpr(const String &string)
      : m_value(make_shared<StringVal>(string)) { }
    ~StringExpr() override = default;

    SharedPtr<StringVal> get_value() const { return m_value; }

    SharedPtr<Variable> execute(Interpreter &interpreter) override;
    void to_string(String &str) override;

  };

}

#endif
