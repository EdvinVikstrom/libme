#include "libme/lang/interpreter/Interpreter.hpp"
#include "libme/lang/Storage.hpp"
#include "libme/lang/ast/Expression.hpp"
#include "libme/lang/ast/Function.hpp"
#include "libme/lang/interpreter/Forward.hpp"
#include "libme/lang/interpreter/Variable.hpp"
#include "libme/lang/interpreter/Value.hpp"

void me::lang::Interpreter::execute(UniquePtr<Expression> expr)
{
  SharedPtr<Variable> var = expr->execute(*this);
  (void) var;
}

me::SharedPtr<me::lang::Variable> me::lang::Interpreter::execute_function(const StringView &name, const Vector<SharedPtr<Variable>> &args)
{
  (void) args;

  FunctionExpr* func_expr = reinterpret_cast<FunctionExpr*>(m_storage.get_user_function(name));
  if (func_expr)
    return func_expr->execute(*this);

  if (name == "print")
  {
    for (const SharedPtr<Variable> &arg : args)
    {
      String output;
      arg->get_value()->to_string(output);
      ::printf("%s\n", output.c_str());
    }
    return nullptr;
  }

  char temp[name.length() + 1];
  throw RuntimeError("unknown function '%s'", name.c_str(temp));
}

void me::lang::Interpreter::add_variable(const StringView &name, SharedPtr<Variable> variable)
{
  ::printf("variable added! [%s][%p]\n", name.c_str(new char[256]), variable.get());
  m_variables[name] = variable;
}

me::SharedPtr<me::lang::Variable> me::lang::Interpreter::get_variable(const StringView &name)
{
  if (!m_variables.contains(name))
    return nullptr;
  return m_variables.at(name);
}
