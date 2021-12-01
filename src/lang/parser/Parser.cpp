#include "libme/lang/parser/Parser.hpp"
#include "libme/UniquePtr.hpp"
#include "libme/lang/lexer/Lexer.hpp"
#include "libme/lang/Storage.hpp"
#include "libme/lang/ast/Expression.hpp"
#include "libme/lang/ast/String.hpp"
#include "libme/lang/ast/Integer.hpp"
#include "libme/lang/ast/Operator.hpp"
#include "libme/lang/ast/Variable.hpp"
#include "libme/lang/ast/Call.hpp"
#include "libme/lang/ast/Scope.hpp"
#include "libme/lang/ast/Function.hpp"
#include "libme/Exception.hpp"
#include "libme/Vector.hpp"

me::lang::Parser::Parser(Lexer &lexer, Storage &storage)
  : m_lexer(lexer), m_storage(storage)
{
}

me::lang::TokenKinds me::lang::Parser::consume_token()
{
  m_lexer.tokenize(m_token);
  return m_token.get_kind();
}

me::UniquePtr<me::lang::Expression> me::lang::Parser::parse()
{
  if (m_token.get_kind() == TokenKinds::KEYWORD_FUNCTION)
    return parse_function();
  else if (m_token.get_kind() == TokenKinds::PUNCTUATOR_LBRACE)
    return parse_scope();
  else if (m_token.is_identifier())
    return parse_identifier();
  else if (m_token.is_literal())
    return parse_literal();

  return nullptr;
}

me::UniquePtr<me::lang::Expression> me::lang::Parser::parse_expression()
{
  auto lhs = parse();
  if (!lhs)
    return nullptr;

  return parse_operator(move(lhs));
}

me::UniquePtr<me::lang::Expression> me::lang::Parser::parse_identifier()
{
  const StringView identifier = m_token.get_value();
  consume_token();

  if (m_token.get_kind() == TokenKinds::PUNCTUATOR_LPAREN)
  {
    consume_token();
    Vector<UniquePtr<Expression>> args;
    while (true)
    {
      UniquePtr<Expression> expr = parse_expression();
      if (expr)
	args.push_back(move(expr));
      if (m_token.get_kind() == TokenKinds::PUNCTUATOR_COMMA)
      {
	consume_token();
	continue;
      }
      if (m_token.get_kind() != TokenKinds::PUNCTUATOR_RPAREN)
	throw RuntimeError("expected ')'");
      consume_token();
      break;
    }
    return make_unique<CallExpr>(identifier, move(args));
  }else
    return make_unique<VariableExpr>(identifier);
}

me::UniquePtr<me::lang::Expression> me::lang::Parser::parse_function()
{
  consume_token();
  const StringView name = m_token.get_value();
  consume_token();

  if (m_token.get_kind() != TokenKinds::PUNCTUATOR_LBRACE)
    throw RuntimeError("expected scope");
  me::UniquePtr<Expression> scope = parse();
  m_storage.add_user_function(name, make_unique<FunctionExpr>(name, move(scope)));
  ::printf("function added! [%s]\n", name.c_str(new char[256]));
  return parse();
}

me::UniquePtr<me::lang::Expression> me::lang::Parser::parse_scope()
{
  consume_token(); // eat '{'

  Vector<UniquePtr<Expression>> body;
  while (true)
  {
    if (m_token.get_kind() == TokenKinds::PUNCTUATOR_RBRACE)
    {
      consume_token(); // eat '}'
      return make_unique<ScopeExpr>(move(body));
    }
    UniquePtr<Expression> expr = parse_expression();
    if (!expr)
      throw RuntimeError("missing '}'");
    body.push_back(move(expr));
  }
  throw RuntimeError("missing '}'");
}

me::UniquePtr<me::lang::Expression> me::lang::Parser::parse_literal()
{
  if (m_token.get_kind() == TokenKinds::LITERAL_STRING)
  {
    UniquePtr<Expression> expr = make_unique<StringExpr>(m_token.get_string());
    consume_token();
    return expr;
  }else if (m_token.get_kind() == TokenKinds::LITERAL_INTEGER)
  {
    UniquePtr<Expression> expr = make_unique<IntegerExpr>(m_token.get_integer());
    consume_token();
    return expr;
  }
  return nullptr;
}

me::UniquePtr<me::lang::Expression> me::lang::Parser::parse_operator(UniquePtr<Expression> lhs)
{
  while (true)
  {
    if (!m_token.is_operator())
      return lhs;

    TokenKinds opr = m_token.get_kind();
    consume_token(); // eat operator

    auto rhs = parse();
    if (!rhs)
      return nullptr;

    if (m_token.is_operator())
    {
      rhs = parse_operator(move(rhs));
      if (!rhs)
	return nullptr;
    }
    return make_unique<OperatorExpr>(opr, move(lhs), move(rhs));
  }
}
