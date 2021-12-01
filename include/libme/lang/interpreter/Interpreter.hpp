#ifndef LIBME_LANG_INTERPRETER_HPP
  #define LIBME_LANG_INTERPRETER_HPP

#include "libme/lang/interpreter/Forward.hpp"
#include "libme/lang/ast/Forward.hpp"
#include "libme/lang/Forward.hpp"
#include "libme/Map.hpp"
#include "libme/String.hpp"
#include "libme/SharedPtr.hpp"
#include "libme/UniquePtr.hpp"

namespace me::lang {

  class Interpreter {

  private:

    Storage &m_storage;
    Map<StringView, SharedPtr<Variable>> m_variables;

  public:

    Interpreter(Storage &storage)
      : m_storage(storage) { }

    void execute(UniquePtr<Expression> expr);
    SharedPtr<Variable> execute_function(const StringView &name, const Vector<SharedPtr<Variable>> &args);

    void add_variable(const StringView &name, SharedPtr<Variable> variable);
    SharedPtr<Variable> get_variable(const StringView &name);

  };

}

#endif
