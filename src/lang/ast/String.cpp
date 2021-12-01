#include "libme/lang/ast/String.hpp"
#include "libme/lang/interpreter/Interpreter.hpp"
#include "libme/lang/interpreter/Variable.hpp"
#include "libme/lang/interpreter/Value.hpp"

me::SharedPtr<me::lang::Variable> me::lang::StringExpr::execute(Interpreter &interpreter)
{
  (void) interpreter;
  return make_shared<Variable>(VARIABLE_FLAGS_CONSTANT, m_value);
}

void me::lang::StringExpr::to_string(String &str)
{
  str.append("String");
}
