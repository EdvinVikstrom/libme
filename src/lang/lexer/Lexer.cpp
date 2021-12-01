#include "libme/lang/lexer/Lexer.hpp"
#include "libme/Utility.hpp"
#include "libme/Exception.hpp"

/* --------------------- */
/* class me::lang::Lexer */
/* --------------------- */
me::lang::Lexer::Lexer(const StringView &source)
  : m_source(source), m_position(source.begin())
{
}

bool me::lang::Lexer::tokenize(Token &token)
{
  if (*m_position == '\0')
    return false;

  skip_whitespace();

  switch (*m_position)
  {
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': 
    case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': 
    case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': 
    case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': 
    case 'Y': case 'Z': case 'a': case 'b': case 'c': case 'd': 
    case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': 
    case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': 
    case 'q': case 'r': case 's': case 't': case 'u': case 'v': 
    case 'w': case 'x': case 'y': case 'z': case '_': case '$': 
      tokenize_identifier(token);
      break;

    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      tokenize_number(token);
      break;

    case '"':
      tokenize_string(token);
      break;

    case '#':
      tokenize_comment(token);
      break;

    case '(':
      m_position++;
      token.set_kind(TokenKinds::PUNCTUATOR_LPAREN);
      break;

    case ')':
      m_position++;
      token.set_kind(TokenKinds::PUNCTUATOR_RPAREN);
      break;

    case '[':
      m_position++;
      token.set_kind(TokenKinds::PUNCTUATOR_LSQUARE);
      break;

    case ']':
      m_position++;
      token.set_kind(TokenKinds::PUNCTUATOR_RSQUARE);
      break;

    case '{':
      m_position++;
      token.set_kind(TokenKinds::PUNCTUATOR_LBRACE);
      break;

    case '}':
      m_position++;
      token.set_kind(TokenKinds::PUNCTUATOR_RBRACE);
      break;

    case ',':
      m_position++;
      token.set_kind(TokenKinds::PUNCTUATOR_COMMA);
      break;

    case '&':
      m_position++;
      if (*m_position == '&')
      {
	m_position++;
	token.set_kind(TokenKinds::PUNCTUATOR_ANDAND);
      }else
	token.set_kind(TokenKinds::OPERATOR_AND);
      break;

    case '|':
      m_position++;
      if (*m_position == '|')
      {
	m_position++;
	token.set_kind(TokenKinds::PUNCTUATOR_LINELINE);
      }else
	token.set_kind(TokenKinds::OPERATOR_LINE);
      break;

    case '+':
      m_position++;
      if (*m_position == '+')
      {
	m_position++;
	token.set_kind(TokenKinds::OPERATOR_PLUSPLUS);
      }else if (*m_position == '=')
      {
	m_position++;
	token.set_kind(TokenKinds::OPERATOR_PLUSEQUAL);
      }else
	token.set_kind(TokenKinds::OPERATOR_PLUS);
      break;

    case '-':
      m_position++;
      if (*m_position == '-')
      {
	m_position++;
	token.set_kind(TokenKinds::OPERATOR_MINUSMINUS);
      }else if (*m_position == '=')
      {
	m_position++;
	token.set_kind(TokenKinds::OPERATOR_MINUSEQUAL);
      }else
	token.set_kind(TokenKinds::OPERATOR_MINUS);
      break;

    case '=':
      m_position++;
      if (*m_position == '=')
      {
	m_position++;
	token.set_kind(TokenKinds::OPERATOR_EQUALEQUAL);
      }else
	token.set_kind(TokenKinds::OPERATOR_EQUAL);
      break;

    case '\0':
      return false;

    default:
      throw RuntimeError("me::lang::Lexer::tokenize(): unknown character '%x' %x", *m_position, '\n');
      break;
  }
  return true;
}

void me::lang::Lexer::tokenize_identifier(Token &token)
{
  const char* first = m_position;
  do {
    m_position++;
  }while (is_ascii(*m_position) || *m_position == '_' || *m_position == '$');

  const StringView identifier(first, m_position);
  if (identifier == "if")
    token.set_kind(TokenKinds::KEYWORD_IF);
  else if (identifier == "else")
    token.set_kind(TokenKinds::KEYWORD_ELSE);
  else if (identifier == "for")
    token.set_kind(TokenKinds::KEYWORD_FOR);
  else if (identifier == "while")
    token.set_kind(TokenKinds::KEYWORD_WHILE);
  else if (identifier == "return")
    token.set_kind(TokenKinds::KEYWORD_RETURN);
  else if (identifier == "break")
    token.set_kind(TokenKinds::KEYWORD_BREAK);
  else if (identifier == "continue")
    token.set_kind(TokenKinds::KEYWORD_CONTINUE);
  else if (identifier == "function")
    token.set_kind(TokenKinds::KEYWORD_FUNCTION);
  else
    token.set_kind(TokenKinds::IDENTIFIER);
  token.set_value(identifier);
}

void me::lang::Lexer::tokenize_number(Token &token)
{
  const char* first = m_position;
  do {
    m_position++;
  }while (is_digit(*m_position));

  const StringView number(first, m_position);
  token.set_kind(TokenKinds::LITERAL_INTEGER);
  token.get_integer() = number.to_integer();
}

void me::lang::Lexer::tokenize_string(Token &token)
{
  String &string = token.get_string();
  string.clear();

  m_position++; // eat '"'
  while (*m_position)
  {
    if (*m_position == '\\')
    {
      m_position++;
      switch (*m_position++)
      {
	case '\\':
	  string += '\\';
	  break;
	case '"':
	  string += '"';
	  break;
	case 'n':
	  string += '\n';
	  break;
	case '0':
	  string += '\0';
	  break;
      }
    }else if (*m_position == '"')
    {
      m_position++;
      break;
    }
    string += *m_position++;
  }
  token.set_kind(TokenKinds::LITERAL_STRING);
}

void me::lang::Lexer::tokenize_comment(Token &token)
{
  const char* first = m_position;
  do {
    m_position++;
  }while (*m_position != '\n' || *m_position == '\0');
  token.set_kind(TokenKinds::COMMENT);
  token.set_value(StringView(first, m_position));
}

void me::lang::Lexer::skip_whitespace()
{
  while (*m_position == ' ' || *m_position == '\t' || *m_position == '\n')
    m_position++;
}
/* end class me::lang::Lexer */
