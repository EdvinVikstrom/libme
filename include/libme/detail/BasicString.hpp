#ifndef LIBME_DETAIL_BASIC_STRING_HPP
  #define LIBME_DETAIL_BASIC_STRING_HPP

#include "libme/detail/StringForward.hpp"
#include "libme/detail/CharTraits.hpp"

#include <initializer_list>

namespace me::detail {

  template<typename CharType, typename Traits>
  class BasicString {

  public:

    typedef size_t Size;
    typedef CharType* Pointer;
    typedef const CharType* ConstPointer;
    typedef CharType* Iterator;
    typedef const CharType* ConstIterator;

    static constexpr Size npos = Size(~0);

    [[nodiscard]] virtual constexpr ConstIterator begin() const = 0;
    [[nodiscard]] virtual constexpr ConstIterator end() const = 0;
    [[nodiscard]] virtual constexpr Size length() const = 0;
    [[nodiscard]] virtual constexpr CharType at(Size pos) const = 0;

    //[[nodiscard]] constexpr int compare(ConstPointer str, Size str_len);
    //[[nodiscard]] constexpr int compare(ConstPointer str);
    //[[nodiscard]] constexpr int compare(const BasicString &str);

    constexpr void copy(Pointer dest, Size off, Size len) const;
    constexpr void copy(Pointer dest) const;
    [[nodiscard]] constexpr StringView<CharType, Traits> substring(Size off, Size len) const;
    [[nodiscard]] constexpr StringView<CharType, Traits> substring(Size off) const;
    [[nodiscard]] constexpr operator bool() const;
    [[nodiscard]] constexpr bool equals(ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr bool equals(ConstPointer str) const;
    [[nodiscard]] constexpr bool equals(const BasicString &str) const;
    [[nodiscard]] constexpr bool operator==(ConstPointer str) const;
    [[nodiscard]] constexpr bool operator==(const BasicString &str) const;
    [[nodiscard]] constexpr bool operator!=(ConstPointer str) const;
    [[nodiscard]] constexpr bool operator!=(const BasicString &str) const;
    [[nodiscard]] constexpr bool starts_with(CharType chr) const;
    [[nodiscard]] constexpr bool starts_with(ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr bool starts_with(ConstPointer str) const;
    [[nodiscard]] constexpr bool starts_with(const BasicString &str) const;
    [[nodiscard]] constexpr bool ends_with(CharType chr) const;
    [[nodiscard]] constexpr bool ends_with(ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr bool ends_with(ConstPointer str) const;
    [[nodiscard]] constexpr bool ends_with(const BasicString &str) const;
    [[nodiscard]] constexpr bool contains(CharType chr) const;
    [[nodiscard]] constexpr bool contains(ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr bool contains(ConstPointer str) const;
    [[nodiscard]] constexpr bool contains(const BasicString &str) const;
    [[nodiscard]] constexpr Size find(CharType chr) const;
    [[nodiscard]] constexpr Size find(ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr Size find(ConstPointer str) const;
    [[nodiscard]] constexpr Size find(const BasicString &str) const;
    [[nodiscard]] constexpr Size find(Size off, CharType chr) const;
    [[nodiscard]] constexpr Size find(Size off, ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr Size find(Size off, ConstPointer str) const;
    [[nodiscard]] constexpr Size find(Size off, const BasicString &str) const;
    [[nodiscard]] constexpr Size rfind(CharType chr) const;
    [[nodiscard]] constexpr Size rfind(ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr Size rfind(ConstPointer str) const;
    [[nodiscard]] constexpr Size rfind(const BasicString &str) const;
    [[nodiscard]] constexpr Size rfind(Size off, CharType chr) const;
    [[nodiscard]] constexpr Size rfind(Size off, ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr Size rfind(Size off, ConstPointer str) const;
    [[nodiscard]] constexpr Size rfind(Size off, const BasicString &str) const;
    [[nodiscard]] constexpr Size count(CharType chr) const;
    [[nodiscard]] constexpr Size count(ConstPointer str, Size str_len) const;
    [[nodiscard]] constexpr Size count(ConstPointer str) const;
    [[nodiscard]] constexpr Size count(const BasicString &str) const;
    template<typename IntType = int> [[nodiscard]] constexpr IntType to_integer(uint8_t base = 10) const;

  };

} // namespace me::detail

#include "libme/detail/StringView.hpp"

/* ----------------------------- */
/* class me::detail::BasicString */
/* ----------------------------- */
//template<typename CharType, typename Traits>
//constexpr int
//me::detail::BasicString<CharType, Traits>::compare(ConstPointer str, Size str_len)
//{
//}
//
//template<typename CharType, typename Traits>
//constexpr int
//me::detail::BasicString<CharType, Traits>::compare(ConstPointer str)
//{
//}
//
//template<typename CharType, typename Traits>
//constexpr int
//me::detail::BasicString<CharType, Traits>::compare(const BasicString &str)
//{
//}

template<typename CharType, typename Traits>
constexpr void
me::detail::BasicString<CharType, Traits>::copy(Pointer dest, Size off, Size len) const
{
  for (; len; len--)
    *dest++ = begin()[off++];
}

template<typename CharType, typename Traits>
constexpr void
me::detail::BasicString<CharType, Traits>::copy(Pointer dest) const
{
  return copy(dest, 0, length());
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>
me::detail::BasicString<CharType, Traits>::substring(Size off, Size len) const
{
  return StringView<CharType, Traits>(begin() + off, len);
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>
me::detail::BasicString<CharType, Traits>::substring(Size off) const
{
  return StringView<CharType, Traits>(begin() + off, end());
}

template<typename CharType, typename Traits>
constexpr
me::detail::BasicString<CharType, Traits>::operator bool() const
{
  return length() != 0;
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::equals(ConstPointer str, Size str_len) const
{
  if (length() != str_len)
    return false;

  for (Size i = 0; i != str_len; i++)
  {
    if (at(i) != str[i])
      return false;
  }
  return true;
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::equals(ConstPointer str) const
{
  return equals(str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::equals(const BasicString &str) const
{
  return equals(str.begin(), str.length());
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::operator==(ConstPointer str) const
{
  return equals(str);
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::operator==(const BasicString &str) const
{
  return equals(str);
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::operator!=(ConstPointer str) const
{
  return !equals(str);
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::operator!=(const BasicString &str) const
{
  return !equals(str);
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::starts_with(CharType chr) const
{
  return Traits::find(begin(), end(), chr) == begin();
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::starts_with(ConstPointer str, Size str_len) const
{
  return Traits::find(begin(), end(), str, str + str_len) == begin();
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::starts_with(ConstPointer str) const
{
  return starts_with(str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::starts_with(const BasicString &str) const
{
  return starts_with(str.begin(), str.length());
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::ends_with(CharType chr) const
{
  return Traits::rfind(begin(), end(), chr) == end() - 1;
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::ends_with(ConstPointer str, Size str_len) const
{
  return Traits::rfind(begin(), end(), str, str_len) == end() - str_len;
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::ends_with(ConstPointer str) const
{
  return ends_with(str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::ends_with(const BasicString &str) const
{
  return ends_with(str.begin(), str.length());
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::contains(CharType chr) const
{
  return Traits::find(begin(), end(), chr) != nullptr;
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::contains(ConstPointer str, Size str_len) const
{
  return Traits::find(begin(), end(), str, str + str_len) != nullptr;
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::contains(ConstPointer str) const
{
  return contains(str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::BasicString<CharType, Traits>::contains(const BasicString &str) const
{
  return contains(str.begin(), str.length());
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::find(CharType chr) const
{
  ConstIterator pos = Traits::find(begin(), end(), chr);
  if (pos == nullptr)
    return npos;
  return pos - begin();
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::find(ConstPointer str, Size str_len) const
{
  ConstIterator pos = Traits::find(begin(), end(), str, str + str_len);
  if (pos == nullptr)
    return npos;
  return pos - begin();
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::find(ConstPointer str) const
{
  return rfind(str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::find(const BasicString &str) const
{
  return rfind(str.begin(), str.length());
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::find(Size off, CharType chr) const
{
  ConstIterator pos = Traits::find(begin() + off, end(), chr);
  if (pos == nullptr)
    return npos;
  return pos - begin();
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::find(Size off, ConstPointer str, Size str_len) const
{
  ConstIterator pos = Traits::find(begin() + off, end(), str, str + str_len);
  if (pos == nullptr)
    return npos;
  return pos - begin();
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::find(Size off, ConstPointer str) const
{
  return rfind(off, str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::find(Size off, const BasicString &str) const
{
  return rfind(off, str.begin(), str.length());
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::rfind(CharType chr) const
{
  ConstIterator pos = Traits::rfind(begin(), end(), chr);
  if (pos == nullptr)
    return npos;
  return pos - begin();
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::rfind(ConstPointer str, Size str_len) const
{
  ConstIterator pos = Traits::rfind(begin(), end(), str, str + str_len);
  if (pos == nullptr)
    return npos;
  return pos - begin();
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::rfind(ConstPointer str) const
{
  return rfind(str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::rfind(const BasicString &str) const
{
  return rfind(str.begin(), str.length());
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::rfind(Size off, CharType chr) const
{
  ConstIterator pos = Traits::rfind(begin(), end() - off, chr);
  if (pos == nullptr)
    return npos;
  return pos - begin();
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::rfind(Size off, ConstPointer str, Size str_len) const
{
  ConstIterator pos = Traits::rfind(begin(), end() - off, str, str + str_len);
  if (pos == nullptr)
    return npos;
  return pos - begin();
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::rfind(Size off, ConstPointer str) const
{
  return rfind(off, str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::rfind(Size off, const BasicString &str) const
{
  return rfind(off, str.begin(), str.length());
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::count(CharType chr) const
{
  Size num = 0;
  for (CharType c : *this)
  {
    if (c == chr)
      num++;
  }
  return num;
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::count(ConstPointer str, Size str_len) const
{
  Size num = 0;
  for (Size i = 0; i != str_len; i++)
  {
    Size pos = find(i, str, str_len);
    if (pos != npos)
    {
      num++;
      i = pos;
    }
  }
  return num;
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::count(ConstPointer str) const
{
  return count(str, Traits::length(str));
}

template<typename CharType, typename Traits>
constexpr typename me::detail::BasicString<CharType, Traits>::Size
me::detail::BasicString<CharType, Traits>::count(const BasicString &str) const
{
  return count(str.begin(), str.length());
}

template<typename CharType, typename Traits>
template<typename IntType>
constexpr IntType
me::detail::BasicString<CharType, Traits>::to_integer(uint8_t base) const
{
  IntType i = 0;

  ConstIterator iter = begin();
  while (is_digit(*iter))
    i = base * i + *iter++ - '0';
  return i;
}
/* end class me::detail::BasicString */

#endif
