#ifndef LIBME_LANG_LEXER_HPP
  #define LIBME_LANG_LEXER_HPP

#include "libme/lang/lexer/Token.hpp"

namespace me::lang {

  class Lexer {

  private:

    const StringView m_source;
    const char* m_position;

  public:

    Lexer(const StringView &source);

    bool tokenize(Token &token);
    void tokenize_identifier(Token &token);
    void tokenize_number(Token &token);
    void tokenize_string(Token &token);
    void tokenize_comment(Token &token);

  private:

    void skip_whitespace();

  };

}

#endif
