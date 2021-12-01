#ifndef LIBME_LANG_AST_CALL_HPP
  #define LIBME_LANG_AST_CALL_HPP

#include "libme/lang/ast/Expression.hpp"
#include "libme/Vector.hpp"
#include "libme/UniquePtr.hpp"

namespace me::lang {

  class CallExpr : public Expression {

  private:

    const StringView m_function;
    const Vector<UniquePtr<Expression>> m_args;

  public:

    CallExpr(const StringView &function, Vector<UniquePtr<Expression>> args)
      : m_function(function), m_args(move(args)) { }
    ~CallExpr() override = default;

    const StringView& get_function() const { return m_function; }
    const Vector<UniquePtr<Expression>>& get_args() const { return m_args; }

    SharedPtr<Variable> execute(Interpreter &interpreter) override;
    void to_string(String &str) override;

  };

}

#endif
