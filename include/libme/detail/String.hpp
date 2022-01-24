#ifndef LIBME_DETAIL_STRING_HPP
  #define LIBME_DETAIL_STRING_HPP

#define LIBME_STRING_VALIDATE 1
#define LIBME_STRING_CHECK 1

#include "libme/Algorithm.hpp"
#include "libme/Exceptions.hpp"
#include "libme/bits/iterator/Access.hpp"
#include "libme/Allocator.hpp"
#include "libme/InitializerList.hpp"
#include "libme/Iterator.hpp"
#include "libme/TypeTraits.hpp"
#include "libme/Utility.hpp"

// TODO: functions with npos as a default arg value

namespace me::detail {

  template<typename CharT, typename Traits>
  class StringView;

  template<typename CharT, typename Traits, typename Allocator>
  class String {

  public:

    typedef Traits TraitsType;
    typedef CharT ValueType;
    typedef Allocator AllocatorType;
    typedef typename AllocatorTraits<Allocator>::SizeType SizeType;
    typedef typename AllocatorTraits<Allocator>::DifferenceType DifferenceType;
    typedef ValueType& Reference;
    typedef const ValueType& ConstReference;
    typedef typename AllocatorTraits<Allocator>::Pointer Pointer;
    typedef typename AllocatorTraits<Allocator>::ConstPointer ConstPointer;
    typedef Pointer Iterator;
    typedef ConstPointer ConstIterator;
    typedef ReverseIterator<ConstIterator> ConstReverseIterator;
    typedef ReverseIterator<Iterator> ReverseIterator;

    static constexpr SizeType npos = SizeType(~0);

  private:

    Pointer m_data;
    SizeType m_length;
    SizeType m_capacity;

  public:

    constexpr String() noexcept; /* default constructor */
    constexpr String(SizeType chr_num, CharT chr); /* chars constructor */
    constexpr String(const CharT* str, SizeType str_len); /* cstring constructor1 */
    constexpr String(const CharT* str); /* cstring constructor2 */
    constexpr String(const String &str, SizeType str_pos, SizeType str_len); /* string constructor */
    template<typename InputIt>
      constexpr String(InputIt first, InputIt last); /* iterator constructor */
    constexpr String(InitializerList<CharT> list); /* list constructor */
    template<typename StringViewLike>
      explicit constexpr String(const StringViewLike &str, SizeType str_pos, SizeType str_len); /* StringViewLike constructor1 */
    template<typename StringViewLike>
      explicit constexpr String(const StringViewLike &str); /* StringViewLike constructor2 */
    constexpr String(const String &str); /* copy constructor */
    constexpr String(String &&str) noexcept; /* move constructor */
    constexpr String(nullptr_t) = delete; /* nullptr constructor */

    constexpr ~String(); /* destructor */

    /* --- Access --- */
    constexpr Reference at(SizeType pos);
    constexpr ConstReference at(SizeType pos) const;

    constexpr Reference operator[](SizeType pos);
    constexpr ConstReference operator[](SizeType pos) const;

    constexpr CharT& front();
    constexpr const CharT& front() const;

    constexpr CharT& back();
    constexpr const CharT& back() const;

    constexpr const CharT* data() const noexcept;
    constexpr CharT* data() noexcept;

    constexpr const CharT* c_str() const noexcept;

    constexpr SizeType copy(CharT* dest, SizeType len, SizeType pos = 0) const;

    constexpr String substring(SizeType pos = 0, SizeType len = npos) const;

    constexpr operator StringView<CharT, Traits>() const noexcept;

    /* --- Iterators --- */
    constexpr Iterator begin() noexcept;
    constexpr ConstIterator begin() const noexcept;
    constexpr ConstIterator cbegin() const noexcept;

    constexpr Iterator end() noexcept;
    constexpr ConstIterator end() const noexcept;
    constexpr ConstIterator cend() const noexcept;

    constexpr ReverseIterator rbegin() noexcept;
    constexpr ConstReverseIterator rbegin() const noexcept;
    constexpr ConstReverseIterator crbegin() const noexcept;

    constexpr ReverseIterator rend() noexcept;
    constexpr ConstReverseIterator rend() const noexcept;
    constexpr ConstReverseIterator crend() const noexcept;

    /* --- Capacity --- */

    [[nodiscard]] constexpr bool is_empty() const noexcept;

    [[nodiscard]] constexpr SizeType length() const noexcept;

    [[nodiscard]] constexpr SizeType max_length() const noexcept;

    [[nodiscard]] constexpr SizeType capacity() const noexcept;

    /* --- Modify --- */

    constexpr void clear() noexcept;

    constexpr void reserve(SizeType capacity);

    constexpr void shrink_to_fit();

    constexpr void resize(SizeType len);
    constexpr void resize(SizeType len, CharT chr);

    template<typename Operation>
      constexpr void resize_and_overwrite(SizeType len, Operation opr);

    template<typename InputIt>
      constexpr String& assign(InputIt first, InputIt last);
    template<typename StringViewLike>
      constexpr String& assign(const StringViewLike &str);
    constexpr String& assign(InitializerList<CharT> list);
    constexpr String& assign(SizeType chr_num, CharT chr);
    constexpr String& assign(CharT chr);

    template<typename StringViewLike>
      constexpr String& operator=(const StringViewLike &str);
    constexpr String& operator=(InitializerList<CharT> list);
    constexpr String& operator=(CharT chr);
    constexpr String& operator=(const String &str);
    constexpr String& operator=(String &&str);

    template<typename InputIt>
      constexpr String& append(InputIt first, InputIt last);
    template<typename StringViewLike>
      constexpr String& append(const StringViewLike &str);
    constexpr String& append(InitializerList<CharT> list);
    constexpr String& append(SizeType chr_num, CharT chr);

    template<typename StringViewLike>
      constexpr String& operator+=(const StringViewLike &str);
    constexpr String& operator+=(InitializerList<CharT> list);
    constexpr String& operator+=(CharT chr);

    constexpr String& erase(SizeType pos = 0, SizeType len = npos);
    constexpr Iterator erase(ConstIterator pos);
    constexpr Iterator erase(ConstIterator first, ConstIterator last);

    template<typename InputIt>
      constexpr String& insert(SizeType pos, InputIt first, InputIt last);
    template<typename StringViewLike>
      constexpr String& insert(SizeType pos, const StringViewLike &str);
    constexpr String& insert(SizeType pos, InitializerList<CharT> list);
    constexpr String& insert(SizeType pos, SizeType chr_num, CharT chr);

    template<typename InputIt>
      constexpr String& replace(SizeType pos, SizeType len, InputIt first, InputIt last);
    template<typename StringViewLike>
      constexpr String& replace(SizeType pos, SizeType len, const StringViewLike &str);
    constexpr String& replace(SizeType pos, SizeType len, InitializerList<CharT> list);
    constexpr String& replace(SizeType pos, SizeType len, SizeType chr_num, CharT chr);

    constexpr void push_back(CharT chr);

    constexpr void pop_back();

    constexpr void swap(String &other)
      noexcept(AllocatorTraits<Allocator>::PropagateOnContainerSwap::value ||
	  AllocatorTraits<Allocator>::IsAlwaysEqual::value);

    /* --- Search --- */

    template<typename InputIt>
      constexpr int compare(InputIt first, InputIt last) const;
    template<typename StringViewLike>
      constexpr int compare(const StringViewLike &str) const;
    constexpr int compare(InitializerList<CharT> list) const;

    template<typename InputIt>
      constexpr bool starts_with(InputIt first, InputIt last) const;
    template<typename StringViewLike>
      constexpr bool starts_with(const StringViewLike &str) const;
    constexpr bool starts_with(InitializerList<CharT> list) const;

    template<typename InputIt>
      constexpr bool ends_with(InputIt first, InputIt last) const;
    template<typename StringViewLike>
      constexpr bool ends_with(const StringViewLike &str) const;
    constexpr bool ends_with(InitializerList<CharT> list) const;

    template<typename InputIt>
      constexpr bool contains(InputIt first, InputIt last) const;
    template<typename StringViewLike>
      constexpr bool contains(const StringViewLike &str) const;
    constexpr bool contains(InitializerList<CharT> list) const;

    template<typename InputIt>
      constexpr SizeType find(InputIt first, InputIt last, SizeType pos = 0) const;
    template<typename StringViewLike>
      constexpr SizeType find(const StringViewLike &str, SizeType pos = 0) const;
    constexpr SizeType find(InitializerList<CharT> list, SizeType pos = 0) const;

    template<typename InputIt>
      constexpr SizeType rfind(InputIt first, InputIt last, SizeType pos = npos) const;
    template<typename StringViewLike>
      constexpr SizeType rfind(const StringViewLike &str, SizeType pos = npos) const;
    constexpr SizeType rfind(InitializerList<CharT> list, SizeType pos = npos) const;

  };

} // namespace me::detail

namespace me {

  template<typename CharT, typename Traits, typename Allocator>
  constexpr bool operator==(const detail::String<CharT, Traits, Allocator> &lhs,
      const detail::String<CharT, Traits, Allocator> &rhs) noexcept;

  template<typename CharT, typename Traits, typename Allocator>
  constexpr CommonComparsionCategory_T<SynthThreeWayResult<detail::String<CharT, Traits, Allocator>>>
    operator==(const detail::String<CharT, Traits, Allocator> &lhs, const detail::String<CharT, Traits, Allocator> &rhs) noexcept;

} // namespace me

/* ------------------------ */
/* class me::detail::String */
/* ------------------------ */

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String()
  noexcept
  : m_data(nullptr), m_length(0), m_capacity(0)
{
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(SizeType chr_num, CharT chr)
{
  m_capacity = chr_num + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = chr_num;

  Pointer ptr = m_data;
  for (SizeType i = 0; i != chr_num; i++)
    Traits::assign(*ptr++, chr);

  Traits::assign(*ptr, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const CharT* str, SizeType str_len)
{
  m_capacity = str_len + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = str_len;

  Pointer ptr = m_data;
  for (SizeType i = 0; i != str_len; i++)
    Traits::assign(*ptr++, str[i]);

  Traits::assign(*ptr, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const CharT* str)
  : String(str, Traits::length(str))
{
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const String &str, SizeType str_pos, SizeType str_len)
{
  m_capacity = str_len + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = str_len;

  Pointer ptr = m_data;
  for (SizeType i = 0; i != str_len; i++)
    Traits::assign(*ptr++, str[str_pos++]);

  Traits::assign(*ptr, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr me::detail::String<CharT, Traits, Allocator>::String(InputIt first, InputIt last)
{
  m_length = last - first;
  m_capacity = m_length + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);

  Pointer ptr = m_data;
  for (; first != last; first++)
    Traits::assign(*ptr++, *first);

  Traits::assign(*ptr, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(InitializerList<CharT> list)
{
  m_length = list.length();
  m_capacity = m_length + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);

  Pointer ptr = m_data;
  for (SizeType i = 0; i != m_length; i++)
    Traits::assign(*ptr++, list.begin()[i]);

  Traits::assign(*ptr, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const StringViewLike &str, SizeType str_pos, SizeType str_len)
  : String(str.substring(str_pos, str_len))
{
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const StringViewLike &str)
  : String(str.data(), str.length())
{
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const String &str)
{
  m_length = str.m_length;
  m_capacity = m_length + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);

  Pointer ptr = m_data;
  for (SizeType i = 0; i != m_length; i++)
    Traits::assign(*ptr++, str[i]);

  Traits::assign(*ptr, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(String &&str)
  noexcept
{
  m_data = str.m_data;
  m_length = str.m_length;
  m_capacity = str.m_capacity;
  str.m_data = nullptr;
  str.m_length = str.m_capacity = 0;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::~String()
{
  if (m_data == nullptr)
    return;

  AllocatorTraits<Allocator>::deallocate(m_data);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::Reference
  me::detail::String<CharT, Traits, Allocator>::at(SizeType pos)
{
#if LIBME_STRING_VALIDATE >= 1
  if (pos >= m_length)
    throw OutOfRangeError();
#endif

  return m_data[pos];
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstReference
  me::detail::String<CharT, Traits, Allocator>::at(SizeType pos) const
{
#if LIBME_STRING_VALIDATE >= 1
  if (pos >= m_length)
    throw OutOfRangeError();
#endif

  return m_data[pos];
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::Reference
  me::detail::String<CharT, Traits, Allocator>::operator[](SizeType pos)
{
  return m_data[pos];
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstReference
  me::detail::String<CharT, Traits, Allocator>::operator[](SizeType pos) const
{
  return m_data[pos];
}

template<typename CharT, typename Traits, typename Allocator>
constexpr CharT&
  me::detail::String<CharT, Traits, Allocator>::front()
{
  return operator[](0);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr const CharT&
  me::detail::String<CharT, Traits, Allocator>::front() const
{
  return operator[](0);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr CharT&
  me::detail::String<CharT, Traits, Allocator>::back()
{
  return operator[](m_length - 1);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr const CharT&
  me::detail::String<CharT, Traits, Allocator>::back() const
{
  return operator[](m_length - 1);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr const CharT*
  me::detail::String<CharT, Traits, Allocator>::data() const
  noexcept
{
  return m_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr CharT*
  me::detail::String<CharT, Traits, Allocator>::data()
  noexcept
{
  return m_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr const CharT*
  me::detail::String<CharT, Traits, Allocator>::c_str() const
  noexcept
{
  return m_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::copy(CharT* dest, SizeType len, SizeType pos) const
{
  Pointer ptr = m_data + pos;
  for (SizeType i = 0; i != len; i++)
    Traits::assign(*dest++, *ptr++);
  Traits::assign(*dest, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>
  me::detail::String<CharT, Traits, Allocator>::substring(SizeType pos, SizeType len) const
{
  return String<CharT, Traits, Allocator>(m_data + pos, len);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::operator
  me::detail::StringView<CharT, Traits>() const
  noexcept
{
  return StringView<CharT, Traits>(m_data, m_length);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::Iterator
  me::detail::String<CharT, Traits, Allocator>::begin()
  noexcept
{
  return m_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstIterator
  me::detail::String<CharT, Traits, Allocator>::begin() const
  noexcept
{
  return m_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstIterator
  me::detail::String<CharT, Traits, Allocator>::cbegin() const
  noexcept
{
  return m_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::Iterator
  me::detail::String<CharT, Traits, Allocator>::end()
  noexcept
{
  return m_data + m_length;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstIterator
  me::detail::String<CharT, Traits, Allocator>::end() const
  noexcept
{
  return m_data + m_length;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstIterator
  me::detail::String<CharT, Traits, Allocator>::cend() const
  noexcept
{
  return m_data + m_length;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ReverseIterator
  me::detail::String<CharT, Traits, Allocator>::rbegin()
  noexcept
{
  return make_reverse_iterator(m_data);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstReverseIterator
  me::detail::String<CharT, Traits, Allocator>::rbegin() const
  noexcept
{
  return make_reverse_iterator(m_data);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstReverseIterator
  me::detail::String<CharT, Traits, Allocator>::crbegin() const
  noexcept
{
  return make_reverse_iterator(m_data);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ReverseIterator
  me::detail::String<CharT, Traits, Allocator>::rend()
  noexcept
{
  return make_reverse_iterator(m_data + m_length);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstReverseIterator
  me::detail::String<CharT, Traits, Allocator>::rend() const
  noexcept
{
  return make_reverse_iterator(m_data + m_length);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::ConstReverseIterator
  me::detail::String<CharT, Traits, Allocator>::crend() const
  noexcept
{
  return make_reverse_iterator(m_data + m_length);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::is_empty() const
  noexcept
{
  return m_length == 0;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::length() const
  noexcept
{
  return m_length;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::max_length() const
  noexcept
{
  return 123456; // TODO
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::capacity() const
  noexcept
{
  return m_capacity;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::clear()
  noexcept
{
  m_length = 0;
  Traits::assign(*m_data, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::reserve(SizeType capacity)
{
  if (capacity <= m_capacity)
    return;

  Pointer new_data = AllocatorTraits<Allocator>::allocate(capacity);
  for (SizeType i = 0; i != m_length; i++)
    Traits::assign(new_data[i], m_data[i]);
  Traits::assign(new_data[m_length], ValueType());

  AllocatorTraits<Allocator>::deallocate(m_data);

  m_data = new_data;
  m_capacity = capacity;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::shrink_to_fit()
{
  if (m_capacity == m_length + 1)
    return;

  m_capacity = m_length + 1;
  Pointer new_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  for (SizeType i = 0; i != m_length; i++)
    Traits::assign(new_data[i], m_data[i]);
  Traits::assign(new_data[m_length], ValueType());

  AllocatorTraits<Allocator>::deallocate(m_data);

  m_data = new_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::resize(SizeType len)
{
  m_length = len;

  reserve(m_length + 1);

  Traits::assign(m_data + m_length, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::resize(SizeType len, CharT chr)
{
  Pointer ptr = m_data;
  for (; len != 0; len--)
    Traits::assign(*ptr++, chr);
  Traits::assign(*ptr, ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
template<typename Operation>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::resize_and_overwrite(SizeType len, Operation opr)
{
  // TODO
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::assign(InputIt first, InputIt last)
{
  m_length = last - first;

  reserve(m_length + 1);

  Pointer ptr = m_data;
  for (; first != last; first++)
    Traits::assign(*ptr++, *first);
  Traits::assign(*ptr, ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::assign(const StringViewLike &str)
{
  m_length = str.length();

  reserve(m_length + 1);

  Pointer ptr = m_data;
  for (SizeType i = 0; i != m_length; i++)
    Traits::assign(*ptr++, str[i]);
  Traits::assign(*ptr, ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::assign(InitializerList<CharT> list)
{
  m_length = list.length();

  reserve(m_length + 1);

  Pointer ptr = m_data;
  for (Pointer i = list.begin(); i != list.end(); i++)
    Traits::assign(*ptr++, *i);
  Traits::assign(*ptr, ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::assign(SizeType chr_num, CharT chr)
{
  m_length = chr_num;

  reserve(m_length + 1);

  Pointer ptr = m_data;
  for (; chr_num != 0; chr_num--)
    Traits::assign(*ptr++, chr);
  Traits::assign(*ptr, ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::assign(CharT chr)
{
  m_length = 1;

  reserve(2);

  Traits::assign(m_data[0], chr);
  Traits::assign(m_data[1], ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(const StringViewLike &str)
{
  return assign(str);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(InitializerList<CharT> list)
{
  return assign(list);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(CharT chr)
{
  return assign(chr);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(const String &str)
{
  m_length = str.length();

  reserve(m_length + 1);

  Pointer ptr = m_data;
  for (SizeType i = 0; i != m_length; i++)
    Traits::assign(*ptr++, str[i]);
  Traits::assign(*ptr, ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(String &&str)
{
  m_data = str.m_data;
  m_length = str.m_length;
  m_capacity = str.m_capacity;
  str.m_data = nullptr;
  str.m_length = str.m_capacity = 0;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::append(InputIt first, InputIt last)
{
  SizeType len = last - first;
  SizeType new_len = m_length + len;

  reserve(new_len + 1);

  Pointer ptr = m_data + m_length;
  for (; first != last; first++)
    Traits::assign(*ptr++, *first);
  Traits::assign(*ptr, ValueType());

  m_length = new_len;
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::append(const StringViewLike &str)
{
  SizeType new_len = m_length + str.length();

  reserve(new_len + 1);

  Pointer ptr = m_data + m_length;
  for (SizeType i = 0; i != str.length(); i++)
    Traits::assign(*ptr++, str[i]);
  Traits::assign(*ptr, ValueType());

  m_length = new_len;
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::append(InitializerList<CharT> list)
{
  SizeType new_len = m_length + list.length();

  reserve(new_len + 1);

  Pointer ptr = m_data + m_length;
  for (Pointer i = list.begin(); i != list.end(); i++)
    Traits::assign(*ptr++, *i);
  Traits::assign(*ptr, ValueType());
  
  m_length = new_len;
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::append(SizeType chr_num, CharT chr)
{
  SizeType new_len = m_length + chr_num;

  reserve(new_len + 1);

  Pointer ptr = m_data + m_length;
  for (; chr_num != 0; chr_num--)
    Traits::assign(*ptr++, chr);
  Traits::assign(*ptr, ValueType());

  m_length = new_len;
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator+=(const StringViewLike &str)
{
  return append(str);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator+=(InitializerList<CharT> list)
{
  return append(list);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator+=(CharT chr)
{
  return append(chr);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::erase(SizeType pos, SizeType len)
{
  m_length = m_length - len;

  Traits::movel(m_data + pos, m_data + pos + len, m_length);

  Traits::assign(m_data[m_length], ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::Iterator
  me::detail::String<CharT, Traits, Allocator>::erase(ConstIterator pos)
{
  // TODO
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::Iterator
  me::detail::String<CharT, Traits, Allocator>::erase(ConstIterator first, ConstIterator last)
{
  // TODO
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::insert(SizeType pos, InputIt first, InputIt last)
{
  SizeType len = last - first;
  SizeType new_len = m_length + len;

  reserve(new_len + 1);

  Traits::mover(m_data + pos + len, m_data + pos, m_length - pos);

  Pointer ptr = m_data + pos;
  for (; first != last; first++)
    Traits::assign(*ptr++, *first);

  m_length = new_len;
  Traits::assign(m_data[m_length], ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::insert(SizeType pos, const StringViewLike &str)
{
  SizeType new_len = m_length + str.length();

  reserve(new_len + 1);

  Traits::mover(m_data + pos + str.length(), m_data + pos, m_length - pos);

  Pointer ptr = m_data + pos;
  for (SizeType i = 0; i != str.length(); i++)
    Traits::assign(*ptr++, str[i]);

  m_length = new_len;
  Traits::assign(m_data[m_length], ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::insert(SizeType pos, InitializerList<CharT> list)
{
  SizeType new_len = m_length + list.length();

  reserve(new_len + 1);

  Traits::mover(m_data + pos + list.length(), m_data + pos, m_length - pos);

  Pointer ptr = m_data + pos;
  for (Pointer i = list.begin(); i != list.end(); i++)
    Traits::assign(*ptr++, *i);

  m_length = new_len;
  Traits::assign(m_data[m_length], ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::insert(SizeType pos, SizeType chr_num, CharT chr)
{
  SizeType new_len = m_length + chr_num;

  reserve(new_len + 1);

  Traits::mover(m_data + pos + chr_num, m_data + pos, m_length - pos);

  Pointer ptr = m_data + pos;
  for (SizeType i = 0; i != chr_num; i++)
    Traits::assign(*ptr++, chr);

  m_length = new_len;
  Traits::assign(m_data[m_length], ValueType());
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::replace(SizeType pos, SizeType len, InputIt first, InputIt last)
{
  // TODO
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::replace(SizeType pos, SizeType len, const StringViewLike &str)
{
  // TODO
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::replace(SizeType pos, SizeType len, InitializerList<CharT> list)
{
  // TODO
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::replace(SizeType pos, SizeType len, SizeType chr_num, CharT chr)
{
  // TODO
}

template<typename CharT, typename Traits, typename Allocator>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::push_back(CharT chr)
{
  reserve(m_length + 2);

  Traits::assign(m_data[m_length], chr);
  m_length += 1;
  Traits::assign(m_data[m_length], ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::pop_back()
{
  m_length -= 1;

  Traits::assign(m_data[m_length], ValueType());
}

template<typename CharT, typename Traits, typename Allocator>
constexpr void
  me::detail::String<CharT, Traits, Allocator>::swap(String &other)
  noexcept(AllocatorTraits<Allocator>::PropagateOnContainerSwap::value || AllocatorTraits<Allocator>::IsAlwaysEqual::value)
{
  ::me::swap(m_data, other.m_data);
  ::me::swap(m_length, other.m_length);
  ::me::swap(m_capacity, other.m_capacity);
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr int
  me::detail::String<CharT, Traits, Allocator>::compare(InputIt first, InputIt last) const
{
  return Traits::compare(m_data, first, ::me::min(m_length, last - first));
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr int
  me::detail::String<CharT, Traits, Allocator>::compare(const StringViewLike &str) const
{
  return Traits::compare(m_data, str.data(), ::me::min(m_length, str.length()));
}

template<typename CharT, typename Traits, typename Allocator>
constexpr int
  me::detail::String<CharT, Traits, Allocator>::compare(InitializerList<CharT> list) const
{
  return Traits::compare(m_data, list.begin(), ::me::min(m_length, list.length()));
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::starts_with(InputIt first, InputIt last) const
{
  SizeType len = last - first;
  if (len > m_length)
    return false;

  return Traits::compare(m_data, first, ::me::min(m_length, last - first)) == 0;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::starts_with(const StringViewLike &str) const
{
  if (str.length() > m_length)
    return false;

  return Traits::compare(m_data, str.data(), ::me::min(m_length, str.length())) == 0;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::starts_with(InitializerList<CharT> list) const
{
  if (list.length() > m_length)
    return false;

  return Traits::compare(m_data, list.begin(), ::me::min(m_length, list.length())) == 0;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::ends_with(InputIt first, InputIt last) const
{
  SizeType len = last - first;
  if (len > m_length)
    return false;

  return Traits::compare(m_data + m_length - len, first, ::me::min(m_length, last - first)) == 0;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::ends_with(const StringViewLike &str) const
{
  if (str.length() > m_length)
    return false;

  return Traits::compare(m_data + m_length + str.length(), str.data(), ::me::min(m_length, str.length())) == 0;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::ends_with(InitializerList<CharT> list) const
{
  if (list.length() > m_length)
    return false;

  return Traits::compare(m_data + m_length - list.length(), list.begin(), ::me::min(m_length, list.length())) == 0;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::contains(InputIt first, InputIt last) const
{
  SizeType len = last - first;

  for (Pointer i = m_data; i != m_data + (m_length - len); i++)
  {
    if (Traits::compare(i, first, len) == 0)
      return true;
  }
  return false;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::contains(const StringViewLike &str) const
{
  for (Pointer i = m_data; i != m_data + (m_length - str.length()); i++)
  {
    if (Traits::compare(i, str.data(), str.length()) == 0)
      return true;
  }
  return false;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr bool
  me::detail::String<CharT, Traits, Allocator>::contains(InitializerList<CharT> list) const
{
  for (Pointer i = m_data; i != m_data + (m_length - list.length()); i++)
  {
    if (Traits::compare(i, list.begin(), list.length()) == 0)
      return true;
  }
  return false;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::find(InputIt first, InputIt last, SizeType pos) const
{
  ConstPointer begin = m_data + pos;
  ConstPointer end = m_data + m_length;
  return Traits::find(begin, end, first, last) - m_data;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::find(const StringViewLike &str, SizeType pos) const
{
  ConstPointer begin = m_data + pos;
  ConstPointer end = m_data + m_length;
  return Traits::find(begin, end, str.begin(), str.end()) - m_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::find(InitializerList<CharT> list, SizeType pos) const
{
  ConstPointer begin = m_data + pos;
  ConstPointer end = m_data + m_length;
  return Traits::find(begin, end, list.begin(), list.end()) - m_data;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::rfind(InputIt first, InputIt last, SizeType pos) const
{
  if (pos == npos)
    pos = m_length;

  ConstPointer begin = m_data;
  ConstPointer end = m_data + pos;
  return Traits::rfind(begin, end, first, last) - m_data;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::rfind(const StringViewLike &str, SizeType pos) const
{
  if (pos == npos)
    pos = m_length;

  ConstPointer begin = m_data;
  ConstPointer end = m_data + pos;
  return Traits::rfind(begin, end, str.begin(), str.end()) - m_data;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr typename me::detail::String<CharT, Traits, Allocator>::SizeType
  me::detail::String<CharT, Traits, Allocator>::rfind(InitializerList<CharT> list, SizeType pos) const
{
  if (pos == npos)
    pos = m_length;

  ConstPointer begin = m_data;
  ConstPointer end = m_data + pos;
  return Traits::rfind(begin, end, list.begin(), list.end()) - m_data;
}

/* end class me::detail::String */

template<typename CharT, typename Traits, typename Allocator>
constexpr bool
  me::operator==(const detail::String<CharT, Traits, Allocator> &lhs, const detail::String<CharT, Traits, Allocator> &rhs)
  noexcept
{
  if (lhs.length() != rhs.length())
    return false;

  for (size_t i = 0; i != lhs.length(); i++)
  {
    if (!Traits::equals(lhs[i], rhs[i]))
      return false;
  }
  return true;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::CommonComparsionCategory_T<me::SynthThreeWayResult<me::detail::String<CharT, Traits, Allocator>>>
  me::operator==(const detail::String<CharT, Traits, Allocator> &lhs, const detail::String<CharT, Traits, Allocator> &rhs)
  noexcept
{
}

#endif // LIBME_DETAIL_STRING_HPP
