#ifndef LIBME_STRING_HPP
  #define LIBME_STRING_HPP

#include "libme/Allocator.hpp"
#include "libme/StringView.hpp"
#include "libme/detail/String.hpp"

namespace me {

  using String = detail::String<char, detail::CharTraits<char>, DefaultAllocator<char>>;
  using WString = detail::String<wchar_t, detail::CharTraits<wchar_t>, DefaultAllocator<wchar_t>>;
  using U8String = detail::String<char8_t, detail::CharTraits<char8_t>, DefaultAllocator<char8_t>>;
  using U16String = detail::String<char16_t, detail::CharTraits<char16_t>, DefaultAllocator<char16_t>>;
  using U32String = detail::String<char32_t, detail::CharTraits<char32_t>, DefaultAllocator<char32_t>>;


} // namespace me

#endif
