#include "libme/lang/ast/Function.hpp"
#include "libme/lang/interpreter/Variable.hpp"
#include "libme/lang/interpreter/Value.hpp"

me::SharedPtr<me::lang::Variable> me::lang::FunctionExpr::execute(Interpreter &interpreter)
{
  return m_scope->execute(interpreter);
}

void me::lang::FunctionExpr::to_string(String &str)
{
  str.append("Function");
}
