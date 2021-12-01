#ifndef LIBME_STRING_VIEW_HPP
  #define LIBME_STRING_VIEW_HPP

#include "libme/detail/CharTraits.hpp"
#include "libme/detail/StringView.hpp"

#include <wchar.h>

namespace me {

  using StringView = detail::StringView<char, detail::CharTraits<char>>;
  using WStringView = detail::StringView<wchar_t, detail::CharTraits<wchar_t>>;
  using U8StringView = detail::StringView<char8_t, detail::CharTraits<char8_t>>;
  using U16StringView = detail::StringView<char16_t, detail::CharTraits<char16_t>>;
  using U32StringView = detail::StringView<char32_t, detail::CharTraits<char32_t>>;

} // namespace me

#endif
