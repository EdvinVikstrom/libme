#ifndef LIBME_LANG_INTERPRETER_VARIABLE_HPP
  #define LIBME_LANG_INTERPRETER_VARIABLE_HPP

#include "libme/lang/interpreter/Forward.hpp"
#include "libme/SharedPtr.hpp"

namespace me::lang {

  enum VariableFlags : uint8_t {
    VARIABLE_FLAGS_CONSTANT = 1
  };

  class Variable {

  private:

    uint8_t m_flags;
    SharedPtr<Value> m_value;

  public:

    Variable(uint8_t flags, SharedPtr<Value> value)
      : m_flags(flags), m_value(value) { }

    bool is_constant() const { return m_flags & VARIABLE_FLAGS_CONSTANT; }

    void set_value(SharedPtr<Value> value) { m_value = value; }
    SharedPtr<Value> get_value() const { return m_value; }

  };

}

#endif
