#ifndef LIBME_LANG_AST_OPERATOR_HPP
  #define LIBME_LANG_AST_OPERATOR_HPP

#include "libme/lang/ast/Expression.hpp"
#include "libme/lang/lexer/Token.hpp"
#include "libme/UniquePtr.hpp"

namespace me::lang {

  class OperatorExpr : public Expression {

  private:

    const TokenKinds m_operator;
    UniquePtr<Expression> m_lhs;
    UniquePtr<Expression> m_rhs;

  public:

    OperatorExpr(TokenKinds opr, UniquePtr<Expression> lhs, UniquePtr<Expression> rhs)
      : m_operator(opr), m_lhs(move(lhs)), m_rhs(move(rhs)) { }
    ~OperatorExpr() override = default;

    TokenKinds get_operator() const { return m_operator; }
    const UniquePtr<Expression>& get_lhs() const { return m_lhs; }
    const UniquePtr<Expression>& get_rhs() const { return m_rhs; }

    SharedPtr<Variable> execute(Interpreter &interpreter) override;
    void to_string(String &str) override;

  };

}

#endif
