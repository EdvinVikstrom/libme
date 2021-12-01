#include "libme/lang/ast/Variable.hpp"
#include "libme/lang/interpreter/Interpreter.hpp"
#include "libme/lang/interpreter/Variable.hpp"
#include "libme/lang/interpreter/Value.hpp"

me::SharedPtr<me::lang::Variable> me::lang::VariableExpr::execute(Interpreter &interpreter)
{
  SharedPtr<Variable> var = interpreter.get_variable(m_name);;
  if (!var)
  {
    var = make_shared<Variable>(0, nullptr);
    interpreter.add_variable(m_name, var);
  }
  return var;
}

void me::lang::VariableExpr::to_string(String &str)
{
  str.append("Variable");
}
