#ifndef LIBME_DETAIL_STRING_HPP
  #define LIBME_DETAIL_STRING_HPP

#include "libme/Allocator.hpp"
#include "libme/InitializerList.hpp"
#include "libme/Iterator.hpp"

namespace me::detail {

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

  private:

    Pointer m_data;
    SizeType m_length;
    SizeType m_capacity;

  public:

    constexpr String() noexcept;
    constexpr String(SizeType count, CharT ch);
    constexpr String(const String &other, SizeType pos, SizeType count);
    constexpr String(const CharT* str, SizeType count);
    constexpr String(const CharT* str);
    template<typename InputIt> constexpr String(InputIt first, InputIt last);
    constexpr String(const String &other);
    constexpr String(String &&other) noexcept;
    constexpr String(InitializerList<CharT> list);
    template<typename StringViewLike> explicit constexpr String(const StringViewLike &string);
    template<typename StringViewLike> explicit constexpr String(const StringViewLike &string, SizeType pos, SizeType num);
    constexpr String(nullptr_t) = delete;

    constexpr ~String();

  };

} // namespace me::detail

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
constexpr me::detail::String<CharT, Traits, Allocator>::String(SizeType count, CharT ch)
{
  m_capacity = count + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = count;
  for (SizeType i = 0; i != count; i++)
    m_data[i] = ch;
  m_data[m_length] = CharT('\0');
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const String &other, SizeType pos, SizeType count)
{
  m_capacity = count + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = count;
  for (SizeType i = 0; i != count; i++)
    m_data[i] = other.m_data[pos++];
  m_data[m_length] = CharT('\0');
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const CharT* str, SizeType count)
{
  m_capacity = count + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = count;
  for (SizeType i = 0; i != count; i++)
    m_data[i] = str[i];
  m_data[m_length] = CharT('\0');
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const CharT* str)
  : String(str, Traits::length(str))
{
}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
constexpr me::detail::String<CharT, Traits, Allocator>::String(InputIt first, InputIt last)
{
  m_length = last - first;
  m_capacity = m_length + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  for (SizeType i = 0; i != m_length; i++)
    m_data[i] = first[i];
  m_data[m_length] = CharT('\0');
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const String &other)
{
  m_length = other.m_length;
  m_capacity = m_length + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  for (SizeType i = 0; i != m_length; i++)
    m_data[i] = other.m_data[i];
  m_data[m_length] = CharT('\0');
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(String &&other)
  noexcept
{
  m_data = other.m_data;
  m_length = other.m_length;
  m_capacity = other.m_capacity;
  other.m_data = nullptr;
  other.m_length = other.m_capacity = 0;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(InitializerList<CharT> list)
{
  m_length = list.length();
  m_capacity = m_length + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  for (SizeType i = 0; i != m_length; i++)
    m_data[i] = list.begin()[i];
  m_data[m_length] = CharT('\0');
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const StringViewLike &string)
  : String(string.data(), string.length())
{
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const StringViewLike &string, SizeType pos, SizeType num)
  : String(string.substring(pos, num))
{
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::~String()
{
  if (m_data == nullptr)
    return;

  AllocatorTraits<Allocator>::deallocate(m_data);
}

/* end class me::detail::String */

#endif
