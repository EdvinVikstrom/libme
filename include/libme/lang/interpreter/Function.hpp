#ifndef LIBME_LANG_INTERPRETER_FUNCTION_HPP
  #define LIBME_LANG_INTERPRETER_FUNCTION_HPP

#include "libme/lang/ast/Expression.hpp"
#include "libme/UniquePtr.hpp"
#include "libme/Vector.hpp"

namespace me::lang {

  class Function {

  private:

    UniquePtr<Expression> m_body;

  public:

    Function(UniquePtr<Expression> body)
      : m_body(move(body)) { }

    SharedPtr<Variable> execute(const Vector<UniquePtr<Expression>> &args);

  };

}

#endif
