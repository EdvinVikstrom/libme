#ifndef LIBME_DETAIL_STRING_VIEW_HPP
  #define LIBME_DETAIL_STRING_VIEW_HPP

#include "libme/detail/StringForward.hpp"
#include "libme/Utility.hpp"

namespace me::detail {

  template<typename CharType, typename Traits>
  class StringView : public BasicString<CharType, Traits> {

  public:

    typedef size_t Size;
    typedef ssize_t SSize;
    typedef CharType* Pointer;
    typedef const CharType* ConstPointer;
    typedef const CharType* ConstIterator;

    static constexpr CharType nullchar = CharType(0);
    static constexpr Size npos = Size(~0);

  private:

    ConstPointer m_begin;
    Size m_length;

  public:

    constexpr StringView(ConstPointer str, Size len);
    constexpr StringView(ConstPointer str);
    template<typename Alloc> constexpr StringView(const String<CharType, Traits, Alloc> &str);
    template<typename Iter> constexpr StringView(Iter first, Iter last);
    constexpr StringView(const StringView &str);
    constexpr StringView(StringView &&str);
    constexpr StringView();
    constexpr StringView& operator=(ConstPointer str);
    constexpr StringView& operator=(const StringView &str);
    constexpr StringView& operator=(StringView &&str);

    constexpr ConstPointer data() const;
    constexpr ConstIterator begin() const override;
    constexpr ConstIterator end() const override;
    constexpr ConstPointer c_str(Pointer dest) const;

    constexpr CharType at(Size pos) const override;
    constexpr CharType operator[](Size pos) const;

    constexpr bool is_empty() const;
    constexpr Size length() const override;

  };

} // namespace me::detail

/* ---------------------------- */
/* class me::detail::StringView */
/* ---------------------------- */
template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>::StringView(ConstPointer str, Size len)
  : m_begin(str), m_length(len)
{
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>::StringView(ConstPointer str)
  : m_begin(str), m_length(Traits::length(str))
{
}

template<typename CharType, typename Traits>
template<typename Alloc>
constexpr me::detail::StringView<CharType, Traits>::StringView(const String<CharType, Traits, Alloc> &str)
  : m_begin(str.begin()), m_length(str.length())
{
}

template<typename CharType, typename Traits>
template<typename Iter>
constexpr me::detail::StringView<CharType, Traits>::StringView(Iter first, Iter last)
  : m_begin(first), m_length(last - first)
{
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>::StringView(const StringView &str)
  : m_begin(str.begin()), m_length(str.length())
{
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>::StringView(StringView &&str)
  : m_begin(str.begin()), m_length(str.length())
{
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>::StringView()
  : m_begin(nullptr), m_length(0)
{
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>&
me::detail::StringView<CharType, Traits>::operator=(ConstPointer str)
{
  m_begin = str;
  m_length = Traits::length(str);
  return *this;
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>&
me::detail::StringView<CharType, Traits>::operator=(const StringView &str)
{
  m_begin = str.begin();
  m_length = str.length();
  return *this;
}

template<typename CharType, typename Traits>
constexpr me::detail::StringView<CharType, Traits>&
me::detail::StringView<CharType, Traits>::operator=(StringView &&str)
{
  m_begin = forward<StringView>(str).m_begin;
  m_length = forward<StringView>(str).m_length;
  return *this;
}

template<typename CharType, typename Traits>
constexpr typename me::detail::StringView<CharType, Traits>::ConstPointer
me::detail::StringView<CharType, Traits>::data() const
{
  return m_begin;
}

template<typename CharType, typename Traits>
constexpr typename me::detail::StringView<CharType, Traits>::ConstIterator
me::detail::StringView<CharType, Traits>::begin() const
{
  return m_begin;
}

template<typename CharType, typename Traits>
constexpr typename me::detail::StringView<CharType, Traits>::ConstIterator
me::detail::StringView<CharType, Traits>::end() const
{
  return m_begin + m_length;
}

template<typename CharType, typename Traits>
constexpr typename me::detail::StringView<CharType, Traits>::ConstPointer
me::detail::StringView<CharType, Traits>::c_str(Pointer dest) const
{
  //BasicString<CharType, Traits>::copy(dest);
  //return dest;
  for (Size i = 0; i != m_length; i++)
    dest[i] = m_begin[i];
  return dest;
}

template<typename CharType, typename Traits>
constexpr CharType
me::detail::StringView<CharType, Traits>::at(Size pos) const
{
  LIBME_ASSERT(pos < m_length, "me::detail::StringView::at(): pos is out of range");
  return m_begin[pos];
}

template<typename CharType, typename Traits>
constexpr CharType
me::detail::StringView<CharType, Traits>::operator[](Size pos) const
{
  LIBME_ASSERT(pos < m_length, "me::detail::StringView::operator[](): pos is out of range");
  return m_begin[pos];
}

template<typename CharType, typename Traits>
constexpr bool
me::detail::StringView<CharType, Traits>::is_empty() const
{
  return m_length == 0;
}

template<typename CharType, typename Traits>
constexpr typename me::detail::StringView<CharType, Traits>::Size
me::detail::StringView<CharType, Traits>::length() const
{
  return m_length;
}

/* end class me::detail::StringView */

#endif
