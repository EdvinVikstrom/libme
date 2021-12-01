#include "libme/lang/ast/Scope.hpp"
#include "libme/lang/interpreter/Variable.hpp"
#include "libme/lang/interpreter/Value.hpp"

me::SharedPtr<me::lang::Variable> me::lang::ScopeExpr::execute(Interpreter &interpreter)
{
  for (size_t i = 0; i != m_body.length(); i++)
  {
    SharedPtr<Variable> val = m_body.at(i)->execute(interpreter);
    if (i == m_body.length() - 1)
      return val;
  }
  return nullptr;
}

void me::lang::ScopeExpr::to_string(String &str)
{
  str.append("Scope");
}
