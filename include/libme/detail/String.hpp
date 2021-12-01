#ifndef LIBME_DETAIL_STRING_HPP
  #define LIBME_DETAIL_STRING_HPP

#include "libme/detail/BasicString.hpp"
#include "libme/Utility.hpp"

namespace me::detail {

  template<typename CharType, typename Traits, typename Alloc>
  class String : public BasicString<CharType, Traits> {

  public:

    typedef size_t Size;
    typedef ssize_t SSize;
    typedef CharType* Pointer;
    typedef const CharType* ConstPointer;
    typedef CharType* Iterator;
    typedef const CharType* ConstIterator;

    static constexpr CharType nullchar = CharType(0);
    static constexpr Size npos = Size(~0);

  private:

    Pointer m_begin;
    Size m_length;
    Size m_capacity;

  public:

    constexpr String(ConstPointer str, Size len);
    constexpr String(ConstPointer str);
    constexpr String(CharType chr, Size num);
    constexpr String(const StringView<CharType, Traits> &str);
    template<typename Iter> constexpr String(Iter first, Iter last);
    constexpr String(const String &str);
    constexpr String(String &&str);
    constexpr String();
    constexpr ~String();
    constexpr String& operator=(ConstPointer str);
    constexpr String& operator=(const StringView<CharType, Traits> &str);
    constexpr String& operator=(const String &str);
    constexpr String& operator=(String &&str);

    [[nodiscard]] constexpr Pointer data() const;
    [[nodiscard]] constexpr Iterator begin();
    [[nodiscard]] constexpr Iterator end();
    [[nodiscard]] constexpr ConstIterator begin() const override;
    [[nodiscard]] constexpr ConstIterator end() const override;
    [[nodiscard]] constexpr CharType& front();
    [[nodiscard]] constexpr CharType& back();
    [[nodiscard]] constexpr const CharType& front() const;
    [[nodiscard]] constexpr const CharType& back() const;
    [[nodiscard]] constexpr ConstPointer c_str() const;

    constexpr String& assign(CharType chr);
    constexpr String& assign(CharType chr, Size chr_num);
    constexpr String& assign(ConstPointer str, Size str_len);
    constexpr String& assign(ConstPointer str);
    constexpr String& assign(const StringView<CharType, Traits> &str);
    template<typename Iter> constexpr String& assign(Iter first, Iter last);
    constexpr String& assign(std::initializer_list<CharType> list);
    constexpr String& insert(Size pos, CharType chr);
    constexpr String& insert(Size pos, CharType chr, Size chr_num);
    constexpr String& insert(Size pos, ConstPointer str, Size str_len);
    constexpr String& insert(Size pos, ConstPointer str);
    constexpr String& insert(Size pos, const StringView<CharType, Traits> &str);
    template<typename Iter> constexpr String& insert(Size pos, Iter first, Iter last);
    constexpr String& insert(Size pos, std::initializer_list<CharType> list);
    constexpr String& replace(Size pos, Size num, CharType chr, Size chr_num);
    constexpr String& replace(Size pos, Size num, ConstPointer str, Size str_len);
    constexpr String& replace(Size pos, Size num, ConstPointer str);
    constexpr String& replace(Size pos, Size num, const StringView<CharType, Traits> &str);
    template<typename Iter> constexpr String& replace(Size pos, Size num, Iter first, Iter last);
    constexpr String& replace(Size pos, Size num, std::initializer_list<CharType> list);
    constexpr String& erase(Size pos, Size num);
    constexpr Iterator erase(ConstIterator pos);
    constexpr Iterator erase(ConstIterator first, ConstIterator last);

    constexpr void clear();
    constexpr void push_back(CharType chr);
    constexpr void pop_back();
    constexpr String& append(CharType chr, Size chr_num);
    constexpr String& append(ConstIterator str, Size str_num);
    constexpr String& append(ConstIterator str);
    constexpr String& append(const StringView<CharType, Traits> &str);
    template<typename Iter> constexpr String& append(Iter first, Iter last);
    constexpr String& append(std::initializer_list<CharType> list);
    constexpr String& operator+=(CharType chr);
    constexpr String& operator+=(ConstPointer str);
    constexpr String& operator+=(const StringView<CharType, Traits> &str);
    constexpr String& operator+=(std::initializer_list<CharType> list);
    constexpr void resize(Size num);
    constexpr void resize(Size num, CharType chr);
    constexpr void reserve(Size new_cap);
    constexpr void shrink_to_fit();

    [[nodiscard]] constexpr CharType& at(Size pos);
    [[nodiscard]] constexpr CharType at(Size pos) const override;
    [[nodiscard]] constexpr CharType& operator[](Size pos);
    [[nodiscard]] constexpr CharType operator[](Size pos) const;

    [[nodiscard]] constexpr bool is_empty() const;
    [[nodiscard]] constexpr Size length() const override;
    [[nodiscard]] constexpr Size max_length() const;
    [[nodiscard]] constexpr Size capacity() const;

  };

} // namespace me::detail

/* ------------------------ */
/* class me::detail::String */
/* ------------------------ */
template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>::String(ConstPointer str, Size len)
{
  LIBME_ASSERT(str != nullptr, "me::detail::String(): received nullptr");

  m_length = len;
  m_capacity = m_length + 1;
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], str[i]);
  Traits::assign(m_begin[m_length], nullchar);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>::String(ConstPointer str)
{
  LIBME_ASSERT(str != nullptr, "me::detail::String(): received nullptr");

  m_length = Traits::length(str);
  m_capacity = m_length + 1;
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], str[i]);
  Traits::assign(m_begin[m_length], nullchar);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>::String(CharType chr, Size num)
{
  m_length = num;
  m_capacity = m_length + 1;
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], chr);
  Traits::assign(m_begin[m_length], nullchar);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>::String(const StringView<CharType, Traits> &str)
{
  m_length = str.length();
  m_capacity = m_length + 1;
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], str.at(i));
  Traits::assign(m_begin[m_length], nullchar);
}

template<typename CharType, typename Traits, typename Alloc>
template<typename Iter>
constexpr me::detail::String<CharType, Traits, Alloc>::String(Iter first, Iter last)
{
  LIBME_ASSERT(str != nullptr, "me::detail::String(): received nullptr");

  m_length = last - first;
  m_capacity = m_length + 1;
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], first[i]);
  Traits::assign(m_begin[m_length], nullchar);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>::String(const String &str)
{
  m_length = str.length();
  m_capacity = str.capacity();
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], str.at(i));
  Traits::assign(m_begin[m_length], nullchar);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>::String(String &&str)
{
  m_begin = str.m_begin;
  m_length = str.m_length;
  m_capacity = str.m_capacity;
  str.m_begin = nullptr;
  str.m_length = str.m_capacity = 0;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>::String()
{
  m_begin = nullptr;
  m_length = 0;
  m_capacity = 0;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>::~String()
{
  if (m_begin != nullptr)
    Alloc::deallocate(m_begin);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::operator=(ConstPointer str)
{
  LIBME_ASSERT(str != nullptr, "me::detail::String(): received nullptr");

  m_length = Traits::length(str);
  m_capacity = m_length + 1;
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], str[i]);
  Traits::assign(m_begin[m_length], nullchar);
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::operator=(const StringView<CharType, Traits> &str)
{
  m_length = str.length();
  m_capacity = m_length + 1;
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], str.at(i));
  Traits::assign(m_begin[m_length], nullchar);
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::operator=(const String &str)
{
  m_length = str.length();
  m_capacity = str.capacity();
  m_begin = Alloc::allocate(m_capacity);

  for (Size i = 0; i != m_length; i++)
    Traits::assign(m_begin[i], str.at(i));
  Traits::assign(m_begin[m_length], nullchar);
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::operator=(String &&str)
{
  m_begin = forward<String>(str).m_begin;
  m_length = forward<String>(str).m_length;
  m_capacity = forward<String>(str).m_capacity;
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::Pointer
me::detail::String<CharType, Traits, Alloc>::data() const
{
  return m_begin;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::Iterator
me::detail::String<CharType, Traits, Alloc>::begin()
{
  return m_begin;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::Iterator
me::detail::String<CharType, Traits, Alloc>::end()
{
  return m_begin + m_length;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::ConstIterator
me::detail::String<CharType, Traits, Alloc>::begin() const
{
  return m_begin;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::ConstIterator
me::detail::String<CharType, Traits, Alloc>::end() const
{
  return m_begin + m_length;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr CharType&
me::detail::String<CharType, Traits, Alloc>::front()
{
  return m_begin[0];
}

template<typename CharType, typename Traits, typename Alloc>
constexpr CharType&
me::detail::String<CharType, Traits, Alloc>::back()
{
  return *m_begin[m_length - 1];
}

template<typename CharType, typename Traits, typename Alloc>
constexpr const CharType&
me::detail::String<CharType, Traits, Alloc>::front() const
{
  return m_begin[0];
}

template<typename CharType, typename Traits, typename Alloc>
constexpr const CharType&
me::detail::String<CharType, Traits, Alloc>::back() const
{
  return *m_begin[m_length - 1];
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::ConstPointer
me::detail::String<CharType, Traits, Alloc>::c_str() const
{
  return m_begin;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::assign(CharType chr)
{
  reserve(2);
  m_length = 1;

  Traits::assign(m_begin[0], chr);
  Traits::assign(m_begin[1], nullchar);
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::assign(CharType chr, Size chr_num)
{
  Size len = chr_num;
  reserve(len + 1);

  for (Size i = 0; i != len; i++)
    Traits::assign(m_begin[i], chr);
  Traits::assign(m_begin[len], nullchar);
  m_length = len;
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::assign(ConstPointer str, Size str_len)
{
  LIBME_ASSERT(str != nullptr, "me::detail::String::assign(): received nullptr");

  Size len = str_len;
  reserve(len + 1);

  for (Size i = 0; i != len; i++)
    Traits::assign(m_begin[i], str[i]);
  Traits::assign(m_begin[len], nullchar);
  m_length = len;
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::assign(ConstPointer str)
{
  return assign(str, Traits::length(str));
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::assign(const StringView<CharType, Traits> &str)
{
  return assign(str.data(), str.length());
}

template<typename CharType, typename Traits, typename Alloc>
template<typename Iter>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::assign(Iter first, Iter last)
{
  return assign(first, last - first);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::assign(std::initializer_list<CharType> list)
{
  return assign(list.begin(), list.end());
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::insert(Size pos, CharType chr)
{
  Size i = pos - m_begin;
  return insert(i, chr, 1);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::insert(Size pos, CharType chr, Size chr_num)
{
  LIBME_ASSERT(pos <= m_length, "me::detail::String::insert(): pos out of range");

  Size mov = m_length - pos;
  Size len = m_length + chr_num;
  reserve(len + 1);

  Pointer src = m_begin + pos;
  Traits::move(src + chr_num, src, mov);
  for (; chr_num; chr_num--)
    Traits::assign(m_begin[pos++], chr);
  Traits::assign(m_begin[len], nullchar);
  m_length = len;
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::insert(Size pos, ConstPointer str, Size str_len)
{
  LIBME_ASSERT(pos <= m_length, "me::detail::String::insert(): pos out of range");
  LIBME_ASSERT(str != nullptr, "me::detail::String::insert(): received nullptr");

  Size mv = m_length - pos;
  Size len = m_length + str_len;
  reserve(m_length + 1);

  Pointer src = m_begin + pos;
  Traits::move(src + str_len, src, mv);
  for (Size i = 0; i != str_len; i++)
    Traits::assign(m_begin[pos++], str[i]);
  Traits::assign(m_begin[len], nullchar);
  m_length = len;
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::insert(Size pos, ConstPointer str)
{
  return insert(pos, str, Traits::length(str));
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::insert(Size pos, const StringView<CharType, Traits> &str)
{
  return insert(pos, str.data(), str.length());
}

template<typename CharType, typename Traits, typename Alloc>
template<typename Iter>
constexpr typename me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::insert(Size pos, Iter first, Iter last)
{
  return insert(pos, first, last - first);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::insert(Size pos, std::initializer_list<CharType> list)
{
  return insert(pos, list.begin(), list.end());
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::replace(Size pos, Size num, CharType chr, Size chr_num)
{
  LIBME_ASSERT(pos < m_length, "me::detail::String::replace(): pos out of range");

  SSize add = chr_num - num;
  Size dst = pos + chr_num;
  Size src = pos + num;
  Size mov = m_length - pos - num;

  m_length = m_length + add;
  if (add > 0)
  {
    reserve(m_length + 1);
    Traits::mover(m_begin + dst, m_begin + src, mov);
  }else
    Traits::movel(m_begin + dst, m_begin + src, mov);

  for (; chr_num; chr_num--)
    Traits::assign(m_begin[pos++], chr);
  Traits::assign(m_begin[m_length], nullchar);
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::replace(Size pos, Size num, ConstPointer str, Size str_len)
{
  LIBME_ASSERT(pos < m_length, "me::detail::String::replace(): pos out of range");
  LIBME_ASSERT(str != nullptr, "me::detail::String::replace(): received nullptr");

  SSize add = str_len - num;
  Size dst = pos + str_len;
  Size src = pos + num;
  Size mov = m_length - pos - num;

  Size len = m_length + add;
  if (add > 0)
  {
    reserve(len + 1);
    Traits::mover(m_begin + dst, m_begin + src, mov);
  }else
    Traits::movel(m_begin + dst, m_begin + src, mov);

  for (Size i = 0; i != str_len; i++)
    Traits::assign(m_begin[pos++], str[i]);
  Traits::assign(m_begin[len], nullchar);
  m_length = len;
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::replace(Size pos, Size num, ConstPointer str)
{
  return replace(pos, num, str, Traits::length(str));
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::replace(Size pos, Size num, const StringView<CharType, Traits> &str)
{
  return replace(pos, num, str.begin(), str.length());
}

template<typename CharType, typename Traits, typename Alloc>
template<typename Iter>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::replace(Size pos, Size num, Iter first, Iter last)
{
  return replace(pos, num, first, last - first);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::replace(Size pos, Size num, std::initializer_list<CharType> list)
{
  return replace(pos, num, list.begin(), list.end());
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::erase(Size pos, Size num)
{
  LIBME_ASSERT(pos < m_length && (pos + num) < m_length, "me::detail::String::erase(): pos out of range");

  m_length -= num;
  Traits::move(m_begin + pos, m_begin + pos + num, m_length);
  Traits::assign(m_begin[m_length], nullchar);
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::Iterator
me::detail::String<CharType, Traits, Alloc>::erase(ConstIterator pos)
{
  LIBME_ASSERT(pos >= begin() && pos <= end(), "me::detail::String::erase(): pos does not refer to this string");
  return erase(pos, pos + 1);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::Iterator
me::detail::String<CharType, Traits, Alloc>::erase(ConstIterator first, ConstIterator last)
{
  LIBME_ASSERT(first >= m_begin && last <= m_end, "me::detail::String::erase(): first and last does not refer to this string");

  Size num = last - first;
  Size pos = first - m_begin;
  erase(pos, num);
  return m_begin + pos;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr void
me::detail::String<CharType, Traits, Alloc>::clear()
{
  if (m_length != 0)
  {
    Traits::assign(m_begin[0], nullchar);
    m_length = 0;
  }
}

template<typename CharType, typename Traits, typename Alloc>
constexpr void
me::detail::String<CharType, Traits, Alloc>::push_back(CharType chr)
{
  reserve(m_length + 2);

  Traits::assign(m_begin[m_length++], chr);
  Traits::assign(m_begin[m_length], nullchar);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr void
me::detail::String<CharType, Traits, Alloc>::pop_back()
{
  LIBME_ASSERT(m_length != 0, "me::detail::String::pop_back(): nothing in the back");

  m_length--;
  Traits::assign(m_begin[m_length], nullchar);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::append(CharType chr, Size chr_num)
{
  Size pos = m_length;
  Size len = m_length + chr_num;
  reserve(len + 1);

  for (; chr_num; chr_num--)
    Traits::assign(m_begin[pos++], chr);
  Traits::assign(m_begin[len], nullchar);
  m_length = len;
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::append(ConstIterator str, Size str_num)
{
  LIBME_ASSERT(str != nullptr, "me::detail::String::append(): received nullptr");

  Size pos = m_length;
  Size len = m_length + str_num;
  reserve(len + 1);

  for (Size i = 0; i != str_num; i++)
    Traits::assign(m_begin[pos++], str[i]);
  Traits::assign(m_begin[len], nullchar);
  m_length = len;
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::append(ConstIterator str)
{
  return append(str, Traits::length(str));
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::append(const StringView<CharType, Traits> &str)
{
  return append(str.begin(), str.length());
}

template<typename CharType, typename Traits, typename Alloc>
template<typename Iter>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::append(Iter first, Iter last)
{
  return append(first, last - first);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::append(std::initializer_list<CharType> list)
{
  return append(list.begin(), list.end());
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::operator+=(CharType chr)
{
  push_back(chr);
  return *this;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::operator+=(ConstPointer str)
{
  return append(str);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::operator+=(const StringView<CharType, Traits> &str)
{
  return append(str);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr me::detail::String<CharType, Traits, Alloc>&
me::detail::String<CharType, Traits, Alloc>::operator+=(std::initializer_list<CharType> list)
{
  return append(list);
}

template<typename CharType, typename Traits, typename Alloc>
constexpr void
me::detail::String<CharType, Traits, Alloc>::resize(Size num)
{
  reserve(num + 1);

  Traits::assign(m_begin[m_length], nullchar);;
  m_length = num;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr void
me::detail::String<CharType, Traits, Alloc>::resize(Size num, CharType chr)
{
  LIBME_ASSERT(num > m_length, "me::detail::String::resize(): num must be greater than the length");

  Size pos = m_length;
  reserve(num + 1);

  for (; num; num--)
    Traits::assign(m_begin[pos++], chr);
  Traits::assign(m_begin[m_length], nullchar);;
  m_length = num;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr void
me::detail::String<CharType, Traits, Alloc>::reserve(Size new_cap)
{
  if (new_cap <= capacity())
    return;

  Pointer new_data = Alloc::allocate(new_cap);
  for (Size i = 0; i != m_length; i++)
    Traits::assign(new_data[i], m_begin[i]);
  Traits::assign(new_data[m_length], nullchar);

  Alloc::deallocate(m_begin);

  m_begin = new_data;
  m_capacity = new_cap;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr void
me::detail::String<CharType, Traits, Alloc>::shrink_to_fit()
{
  Pointer new_data = Alloc::allocate(m_length + 1);
  for (Size i = 0; i != m_length; i++)
    Traits::assign(new_data[i], m_begin[i]);
  Traits::assign(new_data[m_length], nullchar);

  Alloc::deallocate(m_begin);

  m_begin = new_data;
  m_capacity = m_length + 1;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr CharType&
me::detail::String<CharType, Traits, Alloc>::at(Size pos)
{
  LIBME_ASSERT(pos < m_length, "me::detail::String::at(): pos is out of range");
  return m_begin[pos];
}

template<typename CharType, typename Traits, typename Alloc>
constexpr CharType
me::detail::String<CharType, Traits, Alloc>::at(Size pos) const
{
  LIBME_ASSERT(pos < m_length, "me::detail::String::at(): pos is out of range");
  return m_begin[pos];
}
template<typename CharType, typename Traits, typename Alloc>
constexpr CharType&
me::detail::String<CharType, Traits, Alloc>::operator[](Size pos)
{
  LIBME_ASSERT(pos < m_length, "me::detail::String::operator[](): pos is out of range");
  return m_begin[pos];
}

template<typename CharType, typename Traits, typename Alloc>
constexpr CharType
me::detail::String<CharType, Traits, Alloc>::operator[](Size pos) const
{
  LIBME_ASSERT(pos < m_length, "me::detail::String::operator[](): pos is out of range");
  return m_begin[pos];
}

template<typename CharType, typename Traits, typename Alloc>
constexpr bool
me::detail::String<CharType, Traits, Alloc>::is_empty() const
{
  return m_length == 0;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::Size
me::detail::String<CharType, Traits, Alloc>::length() const
{
  return m_length;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::Size
me::detail::String<CharType, Traits, Alloc>::max_length() const
{
  return 1234567;
}

template<typename CharType, typename Traits, typename Alloc>
constexpr typename me::detail::String<CharType, Traits, Alloc>::Size
me::detail::String<CharType, Traits, Alloc>::capacity() const
{
  return m_capacity;
}
/* end class me::detail::String */

#define LIBME_TEST_STRING(f, v, r) \
{ \
  me::detail::String<char, me::detail::CharTraits<char>, me::DefaultAllocator<char>> str(v); \
  str.f; \
  if (str.equals(r)) \
    ::printf("String::%s passed\n", #f); \
  else \
  { \
    ::printf("String::%s failed\n", #f); \
    ::printf("result was: \"%s\"\n", str.c_str()); \
    ::printf("expected:   \"%s\"\n", r); \
    exit(1); \
  } \
}

#endif
