#include "libme/lang/ast/Operator.hpp"
#include "libme/lang/interpreter/Interpreter.hpp"
#include "libme/lang/interpreter/Variable.hpp"
#include "libme/lang/interpreter/Value.hpp"

me::SharedPtr<me::lang::Variable> me::lang::OperatorExpr::execute(Interpreter &interpreter)
{
  SharedPtr<Variable> var1 = m_lhs->execute(interpreter);
  SharedPtr<Variable> var2 = m_rhs->execute(interpreter);

  if (m_operator == TokenKinds::OPERATOR_PLUS)
  {
    SharedPtr<Value> new_val = var1->get_value()->clone();
    new_val->operator_add(var2->get_value());
    return make_shared<Variable>(VARIABLE_FLAGS_CONSTANT, new_val);
  }else if (m_operator == TokenKinds::OPERATOR_EQUAL)
  {
    if (var1->is_constant())
      throw RuntimeError("cannot assign constant");

    if (!var1->get_value())
      var1->set_value(var2->get_value());
    else
      var1->get_value()->operator_assign(var2->get_value());
  }
  return nullptr;
}

void me::lang::OperatorExpr::to_string(String &str)
{
  str.append("Operator");
}
