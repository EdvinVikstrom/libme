#ifndef LIBME_LANG_LEXER_TOKEN_HPP
  #define LIBME_LANG_LEXER_TOKEN_HPP

#include "libme/Type.hpp"
#include "libme/lang/lexer/SourceLocation.hpp"

namespace me::lang {

  enum class TokenKinds : uint16_t {
#define TOKEN(x) x,
#include "libme/lang/lexer/TokenKinds.hpp"
    END,
    MAX
  };


  class Token {

  private:

    TokenKinds m_kind;
    SourceLocation m_location;
    StringView m_value;

    String m_string;
    int m_integer;
    float m_float;

  public:

    TokenKinds get_kind() const;
    const SourceLocation& get_location() const;
    const StringView& get_value() const;

    void set_kind(TokenKinds kind);
    void set_location(const SourceLocation &location);
    void set_value(const StringView &value);

    String& get_string();
    int& get_integer();
    float& get_float();

    bool is_identifier() const;
    bool is_keyword() const;
    bool is_punctuator() const;
    bool is_operator() const;
    bool is_literal() const;
    bool is_comment() const;

  };

  const char* token_kind_name(TokenKinds kind);

}

#endif
