#ifndef LIBME_DETAIL_CHAR_TRAITS_HPP
  #define LIBME_DETAIL_CHAR_TRAITS_HPP

#include "libme/Type.hpp"

namespace me::detail {

  template<typename CharType, typename Traits> static constexpr CharType* __movel(CharType* dest, const CharType* src, size_t num);
  template<typename CharType, typename Traits> static constexpr CharType* __mover(CharType* dest, const CharType* src, size_t num);
  template<typename CharType, typename Traits> static constexpr CharType* __move(CharType* dest, const CharType* src, size_t num);
  template<typename CharType, typename Traits> static constexpr CharType* __copy(CharType* dest, const CharType* src, size_t num);
  template<typename CharType, typename Traits> static constexpr int __compare(const CharType* str1, const CharType* str2, size_t num);
  template<typename CharType, typename Traits> static constexpr size_t __length(const CharType* str);
  template<typename CharType, typename Traits> static constexpr const CharType* __find(const CharType* first, const CharType* last, CharType &chr);
  template<typename CharType, typename Traits> static constexpr const CharType* __find(const CharType* first1, const CharType* last1,
										       const CharType* first2, const CharType* last2);
  template<typename CharType, typename Traits> static constexpr const CharType* __rfind(const CharType* first, const CharType* last, CharType &chr);
  template<typename CharType, typename Traits> static constexpr const CharType* __rfind(const CharType* first1, const CharType* last1,
											const CharType* first2, const CharType* last2);

  template<typename CharType>
  class CharTraits;

  template<>
  class CharTraits<char> {

  public:

    static constexpr void assign(char &dest, char chr);
    static constexpr void assign(char* dest, size_t num, char chr);
    static constexpr bool equals(char chr1, char chr2);
    static constexpr bool less_than(char chr1, char chr2);
    static constexpr char* movel(char* dest, const char* src, size_t num);
    static constexpr char* mover(char* dest, const char* src, size_t num);
    static constexpr char* move(char* dest, const char* src, size_t num);
    static constexpr char* copy(char* dest, const char* src, size_t num);
    static constexpr int compare(const char* str1, const char* str2, size_t num);
    static constexpr size_t length(const char* str);
    static constexpr const char* find(const char* first, const char* last, char chr);
    static constexpr const char* find(const char* first1, const char* last1, const char* first2, const char* last2);
    static constexpr const char* rfind(const char* first, const char* last, char chr);
    static constexpr const char* rfind(const char* first1, const char* last1, const char* first2, const char* last2);

  };


} // namespace me::detail

template<typename CharType, typename Traits>
constexpr CharType*
me::detail::__movel(CharType* dest, const CharType* src, size_t num)
{
  for (size_t i = 0; num--; i++)
    Traits::assign(dest[i], src[i]);
  return dest;
}

template<typename CharType, typename Traits>
constexpr CharType*
me::detail::__mover(CharType* dest, const CharType* src, size_t num)
{
  for (size_t i = num - 1; num--; i--)
    Traits::assign(dest[i], src[i]);
  return dest;
}

template<typename CharType, typename Traits>
constexpr CharType*
me::detail::__move(CharType* dest, const CharType* src, size_t num)
{
  if (dest < src)
    __movel<CharType, Traits>(dest, src, num);
  else if (dest > src)
    __mover<CharType, Traits>(dest, src, num);
  return dest;
}

template<typename CharType, typename Traits>
constexpr CharType*
me::detail::__copy(CharType* dest, const CharType* src, size_t num)
{
  for (size_t i = 0; i != num; i++)
    Traits::assign(dest[i], src[i]);
  return dest;
}

template<typename CharType, typename Traits>
constexpr int
me::detail::__compare(const CharType* str1, const CharType* str2, size_t num)
{
  while (num--, str1++, str2++)
  {
    if (Traits::less_than(*str1, *str2))
      return -1;
    if (Traits::less_than(*str2, *str1))
      return 1;
  }
  return 0;
}

template<typename CharType, typename Traits>
constexpr me::size_t
me::detail::__length(const CharType* str)
{
  size_t len = 0;
  while (!Traits::equals(str[len], CharType(0)))
    len++;
  return len;
}

template<typename CharType, typename Traits>
static constexpr const CharType*
me::detail::__find(const CharType* first, const CharType* last, CharType &chr)
{
  for (; first != last; first++)
  {
    if (Traits::equals(*first, chr))
      return first;
  }
  return nullptr;
}

template<typename CharType, typename Traits>
static constexpr const CharType*
me::detail::__find(const CharType* first1, const CharType* last1, const CharType* first2, const CharType* last2)
{
  size_t len = last2 - first2;
  for (; first1 != last1 - len; first1++)
  {
    if (Traits::compare(first1, first2, len) == 0)
      return first1;
  }
  return nullptr;
}

template<typename CharType, typename Traits>
static constexpr const CharType*
me::detail::__rfind(const CharType* first, const CharType* last, CharType &chr)
{
  last--;
  first--;
  for (; last != first; last--)
  {
    if (Traits::equals(*last, chr))
      return last;
  }
  return nullptr;
}

template<typename CharType, typename Traits>
static constexpr const CharType*
me::detail::__rfind(const CharType* first1, const CharType* last1, const CharType* first2, const CharType* last2)
{
  size_t len = last2 - first2;
  last1 -= len;
  first1--;
  for (; last1 != first1; last1--)
  {
    if (Traits::compare(last1, first2, len) == 0)
      return last1;
  }
  return nullptr;
}

/* ---------------------------- */
/* class me::detail::CharTraits */
/* ---------------------------- */
constexpr void
me::detail::CharTraits<char>::assign(char &dest, char chr)
{
  dest = chr;
}

constexpr void
me::detail::CharTraits<char>::assign(char* dest, size_t num, char chr)
{
  for (size_t i = 0; i != num; i++)
    dest[i] = chr;
}

constexpr bool
me::detail::CharTraits<char>::equals(char chr1, char chr2)
{
  return chr1 == chr2;
}

constexpr bool
me::detail::CharTraits<char>::less_than(char chr1, char chr2)
{
  return static_cast<unsigned char>(chr1) < static_cast<unsigned char>(chr2);
}

constexpr char*
me::detail::CharTraits<char>::movel(char* dest, const char* src, size_t num)
{
  return __movel<char, CharTraits<char>>(dest, src, num);
}

constexpr char*
me::detail::CharTraits<char>::mover(char* dest, const char* src, size_t num)
{
  return __mover<char, CharTraits<char>>(dest, src, num);
}

constexpr char*
me::detail::CharTraits<char>::move(char* dest, const char* src, size_t num)
{
  return __move<char, CharTraits<char>>(dest, src, num);
}

constexpr char*
me::detail::CharTraits<char>::copy(char* dest, const char* src, size_t num)
{
  return __copy<char, CharTraits<char>>(dest, src, num);
}

constexpr int
me::detail::CharTraits<char>::compare(const char* str1, const char* str2, size_t num)
{
  return __compare<char, CharTraits<char>>(str1, str2, num);
}

constexpr me::size_t
me::detail::CharTraits<char>::length(const char* str)
{
  return __length<char, CharTraits<char>>(str);
}

constexpr const char*
me::detail::CharTraits<char>::find(const char* first, const char* last, char chr)
{
  return __find<char, CharTraits<char>>(first, last, chr);
}

constexpr const char*
me::detail::CharTraits<char>::find(const char* first1, const char* last1, const char* first2, const char* last2)
{
  return __find<char, CharTraits<char>>(first1, last1, first2, last2);
}

constexpr const char*
me::detail::CharTraits<char>::rfind(const char* first, const char* last, char chr)
{
  return __rfind<char, CharTraits<char>>(first, last, chr);
}

constexpr const char*
me::detail::CharTraits<char>::rfind(const char* first1, const char* last1, const char* first2, const char* last2)
{
  return __rfind<char, CharTraits<char>>(first1, last1, first2, last2);
}
/* end class me::detail::CharTraits */

#endif
