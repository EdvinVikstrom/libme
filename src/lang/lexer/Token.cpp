#include "libme/lang/lexer/Token.hpp"

/* ----------------------- */
/* class me::script::Token */
/* ----------------------- */
me::lang::TokenKinds me::lang::Token::get_kind() const
{
  return m_kind;
}

const me::lang::SourceLocation& me::lang::Token::get_location() const
{
  return m_location;
}

const me::StringView& me::lang::Token::get_value() const
{
  return m_value;
}

void me::lang::Token::set_kind(TokenKinds kind)
{
  m_kind = kind;
}

void me::lang::Token::set_location(const SourceLocation &location)
{
  m_location = location;
}

void me::lang::Token::set_value(const StringView &value)
{
  m_value = value;
}

me::String& me::lang::Token::get_string()
{
  return m_string;
}

int& me::lang::Token::get_integer()
{
  return m_integer;
}

float& me::lang::Token::get_float()
{
  return m_float;
}

bool me::lang::Token::is_identifier() const
{
  return m_kind == TokenKinds::IDENTIFIER;
}

bool me::lang::Token::is_keyword() const
{
  switch (m_kind)
  {
#define KEYWORD(x, y) case TokenKinds::KEYWORD_ ## x:;
#include "libme/lang/lexer/TokenKinds.hpp"
      return true;
    default:
      return false;
  }
}

bool me::lang::Token::is_punctuator() const
{
  switch (m_kind)
  {
#define PUNCTUATOR(x, y) case TokenKinds::PUNCTUATOR_ ## x:;
#include "libme/lang/lexer/TokenKinds.hpp"
      return true;
    default:
      return false;
  }
}

bool me::lang::Token::is_operator() const
{
  switch (m_kind)
  {
#define OPERATOR(x, y) case TokenKinds::OPERATOR_ ## x:;
#include "libme/lang/lexer/TokenKinds.hpp"
      return true;
    default:
      return false;
  }
}

bool me::lang::Token::is_literal() const
{
  switch (m_kind)
  {
#define LITERAL(x) case TokenKinds::LITERAL_ ## x:;
#include "libme/lang/lexer/TokenKinds.hpp"
      return true;
    default:
      return false;
  }
}

bool me::lang::Token::is_comment() const
{
  return m_kind == TokenKinds::COMMENT;
}
/* end class me::script::Token */

const char* me::lang::token_kind_name(TokenKinds kind)
{
  switch (kind)
  {
#define TOKEN(x) case TokenKinds::x: return # x;
#include "libme/lang/lexer/TokenKinds.hpp"
    default:
      return "UNKNOWN";
  }
}
