#ifndef LIBME_LANG_AST_EXPRESSION_HPP
  #define LIBME_LANG_AST_EXPRESSION_HPP

#include "libme/lang/interpreter/Forward.hpp"
#include "libme/String.hpp"
#include "libme/SharedPtr.hpp"

namespace me::lang {

  class Expression {

  public:

    virtual ~Expression() { };

    virtual SharedPtr<Variable> execute(Interpreter &interpreter) = 0;
    virtual void to_string(String &str) = 0;

  };

}

#endif
