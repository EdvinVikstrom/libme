#ifndef LIBME_LANG_PARSER_HPP
  #define LIBME_LANG_PARSER_HPP

#include "libme/lang/lexer/Forward.hpp"
#include "libme/lang/ast/Forward.hpp"
#include "libme/lang/lexer/Token.hpp"
#include "libme/lang/Forward.hpp"
#include "libme/UniquePtr.hpp"
#include "libme/Vector.hpp"

namespace me::lang {

  class Parser {

  private:

    Lexer &m_lexer;
    Storage &m_storage;
    Token m_token;
    
  public:

    Parser(Lexer &lexer, Storage &storage);

    TokenKinds consume_token();

    UniquePtr<Expression> parse();
    UniquePtr<Expression> parse_expression();
    UniquePtr<Expression> parse_identifier();
    UniquePtr<Expression> parse_function();
    UniquePtr<Expression> parse_scope();
    UniquePtr<Expression> parse_literal();
    UniquePtr<Expression> parse_operator(UniquePtr<Expression> lhs);

  };

}

#endif
