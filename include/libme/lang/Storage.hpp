#ifndef LIBME_LANG_STORAGE_HPP
  #define LIBME_LANG_STORAGE_HPP

#include "libme/lang/ast/Forward.hpp"
#include "libme/UniquePtr.hpp"
#include "libme/String.hpp"
#include "libme/Map.hpp"

namespace me::lang {

  class Storage {

  private:

    Map<StringView, UniquePtr<Expression>> m_user_functions;

  public:

    void add_user_function(const StringView &name, UniquePtr<Expression> expression)
    {
      m_user_functions[name] = move(expression);
    }

    Expression* get_user_function(const StringView &name)
    {
      if (!m_user_functions.contains(name))
	return nullptr;
      return m_user_functions.at(name).get();
    }


  };

} // namespace me::lang

#endif
