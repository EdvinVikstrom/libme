#include "libme/lang/ast/Call.hpp"
#include "libme/lang/interpreter/Interpreter.hpp"
#include "libme/lang/interpreter/Variable.hpp"
#include "libme/lang/interpreter/Value.hpp"

me::SharedPtr<me::lang::Variable> me::lang::CallExpr::execute(Interpreter &interpreter)
{
  Vector<SharedPtr<Variable>> args;
  for (const UniquePtr<Expression> &arg : m_args)
    args.push_back(arg->execute(interpreter));
  return interpreter.execute_function(m_function, move(args));
}

void me::lang::CallExpr::to_string(String &str)
{
  str.append("Call");
}
