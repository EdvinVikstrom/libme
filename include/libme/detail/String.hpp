#ifndef LIBME_DETAIL_STRING_HPP
  #define LIBME_DETAIL_STRING_HPP

#define LIBME_STRING_VALIDATE 1
#define LIBME_STRING_CHECK 1

#include "libme/Allocator.hpp"
#include "libme/InitializerList.hpp"
#include "libme/Iterator.hpp"
#include "libme/TypeTraits.hpp"

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

    constexpr String() noexcept;
    constexpr String(SizeType chr_count, CharT chr);
    constexpr String(const String &str, SizeType str_pos, SizeType str_len);
    constexpr String(const CharT* str, SizeType str_len);
    constexpr String(const CharT* str);
    template<typename InputIt> constexpr String(InputIt first, InputIt last);
    constexpr String(const String &str);
    constexpr String(String &&str) noexcept;
    constexpr String(InitializerList<CharT> list);
    template<typename StringViewLike> explicit constexpr String(const StringViewLike &str);
    template<typename StringViewLike> explicit constexpr String(const StringViewLike &str, SizeType str_pos, SizeType str_len);
    constexpr String(nullptr_t) = delete;

    constexpr ~String();

    constexpr String& operator=(const String &str);
    constexpr String& operator=(String &&str)
      noexcept(AllocatorTraits<Allocator>::PropagateOnContainerMoveAssignment::value ||
	  AllocatorTraits<Allocator>::IsAlwaysEqual::value);
    constexpr String& operator=(const CharT* str);
    constexpr String& operator=(CharT chr);
    constexpr String& operator=(InitializerList<CharT> list);
    template<typename StringViewLike> constexpr String& operator=(const StringViewLike &str);
    constexpr String& operator=(nullptr_t) = delete;

    constexpr String& assign(SizeType chr_count, CharT chr);
    constexpr String& assign(const String &str);
    constexpr String& assign(const String &str, SizeType str_pos, SizeType str_len = npos);
    constexpr String& assign(String &&str)
      noexcept(AllocatorTraits<Allocator>::PropagateOnContainerMoveAssignment::value ||
	  AllocatorTraits<Allocator>::IsAlwaysEqual::value);
    constexpr String& assign(const CharT* str, SizeType str_len);
    constexpr String& assign(const CharT* str);
    template<typename InputIt> constexpr String& assign(InputIt first, InputIt last);
    constexpr String& assign(InitializerList<CharT> list);
    template<typename StringViewLike> constexpr String& assign(const StringViewLike &str);
    template<typename StringViewLike> constexpr String& assign(const StringViewLike &str, SizeType str_pos, SizeType str_len = npos);

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

    constexpr void reserve(SizeType capacity);

    [[nodiscard]] constexpr SizeType capacity() const noexcept;

    constexpr void shrink_to_fit();

    /* --- Operations --- */
    constexpr void clear() noexcept;

    constexpr String& insert(SizeType index, SizeType chr_count, CharT chr);
    constexpr String& insert(SizeType index, const CharT* str);
    constexpr String& insert(SizeType index, const CharT* str, SizeType str_len);
    constexpr String& insert(SizeType index, const String &str);
    constexpr String& insert(SizeType index, const String &str, SizeType str_pos, SizeType str_len = npos);
    constexpr Iterator insert(ConstIterator pos, CharT chr);
    constexpr Iterator insert(ConstIterator pos, SizeType chr_count, CharT chr);
    template<typename InputIt> constexpr Iterator insert(ConstIterator pos, InputIt first, InputIt last);
    constexpr Iterator insert(ConstIterator pos, InitializerList<CharT> list);
    template<typename StringViewLike> constexpr String& insert(SizeType pos, const StringViewLike &str);
    template<typename StringViewLike> constexpr String& insert(SizeType pos, const StringViewLike &str, SizeType str_pos, SizeType str_len = npos);

    constexpr String& erase(SizeType pos = 0, SizeType len = npos);
    constexpr Iterator erase(ConstIterator pos);
    constexpr Iterator erase(ConstIterator first, ConstIterator last);

    constexpr void push_back(CharT chr);

    constexpr void pop_back();

    constexpr String& append(SizeType chr_count, CharT chr);
    constexpr String& append(const String &str);
    constexpr String& append(const String &str, SizeType str_pos, SizeType str_len = npos);
    constexpr String& append(const CharT* str, SizeType str_len);
    constexpr String& append(const CharT* str);
    template<typename InputIt>
      constexpr String& append(InputIt first, InputIt last);
    constexpr String& append(InitializerList<CharT> list);
    template<typename StringViewLike>
      constexpr String& append(const StringViewLike &str);
    template<typename StringViewLike>
      constexpr String& append(const StringViewLike &str, SizeType str_pos, SizeType str_len = npos);

    constexpr String& operator+=(const String &str);
    constexpr String& operator+=(CharT chr);
    constexpr String& operator+=(const CharT* str);
    constexpr String& operator+=(InitializerList<CharT> list);
    template<typename StringViewLike>
      constexpr String& operator+=(const StringViewLike &str);

    constexpr int compare(const String &str) const noexcept;
    constexpr int compare(SizeType pos, SizeType len, const String &str) const;
    constexpr int compare(SizeType pos, SizeType len, const String &str, SizeType str_pos, SizeType str_len = npos) const;
    constexpr int compare(const CharT* str) const;
    constexpr int compare(SizeType pos, SizeType count, const CharT* str) const;
    constexpr int compare(SizeType pos, SizeType count, const CharT* str, SizeType str_len) const;
    template<typename StringViewLike> constexpr int compare(const StringViewLike &str) const
      noexcept(is_nothrow_convertible_v<const StringViewLike&, StringView<CharT, Traits>>);
    template<typename StringViewLike>
      constexpr int compare(SizeType pos, SizeType len, const StringViewLike &str) const;
    template<typename StringViewLike>
      constexpr int compare(SizeType pos, SizeType len, const StringViewLike &str, SizeType str_pos, SizeType str_len = npos) const;

    constexpr bool starts_with(StringView<CharT, Traits> str) const noexcept;
    constexpr bool starts_with(CharT chr) const noexcept;
    constexpr bool starts_with(const CharT* str) const;

    constexpr bool ends_with(StringView<CharT, Traits> str) const noexcept;
    constexpr bool ends_with(CharT chr) const noexcept;
    constexpr bool ends_with(const CharT* str) const;

    constexpr bool contains(StringView<CharT, Traits> str) const noexcept;
    constexpr bool contains(CharT chr) const noexcept;
    constexpr bool contains(const CharT* str) const;

    constexpr String& replace(SizeType pos, SizeType len, const String &str);
    constexpr String& replace(ConstIterator first, ConstIterator last, const String &str);
    constexpr String& replace(SizeType pos, SizeType len, const String &str, SizeType str_pos, SizeType str_len = npos);
    template<typename InputIt>
      constexpr String& replace(ConstIterator first, ConstIterator last, InputIt first2, InputIt last2);
    constexpr String& replace(SizeType pos, SizeType len, const CharT* str, SizeType str_len);
    constexpr String& replace(ConstIterator first, ConstIterator last, const CharT* str, SizeType str_len);
    constexpr String& replace(SizeType pos, SizeType len, const CharT* str);
    constexpr String& replace(ConstIterator first, ConstIterator last, const CharT* str);
    constexpr String& replace(SizeType pos, SizeType len, SizeType chr_count, CharT chr);
    constexpr String& replace(ConstIterator first, ConstIterator last, SizeType chr_count, CharT chr);
    constexpr String& replace(ConstIterator first, ConstIterator last, InitializerList<CharT> list);
    template<typename StringViewLike>
      constexpr String& replace(SizeType pos, SizeType len, const StringViewLike &str);
    template<typename StringViewLike>
      constexpr String& replace(ConstIterator first, ConstIterator last, const StringViewLike &str);
    template<typename StringViewLike>
      constexpr String& replace(SizeType pos, SizeType len, const StringViewLike &str, SizeType str_pos, SizeType str_len = npos);

    constexpr String substring(SizeType pos = 0, SizeType len = npos) const;

    constexpr SizeType copy(CharT* dest, SizeType len, SizeType pos = 0) const;

    constexpr void resize(SizeType len);
    constexpr void resize(SizeType len, CharT chr);

    template<typename Operation>
      constexpr void resize_and_overwrite(SizeType len, Operation opr);

    constexpr void swap(String &other)
      noexcept(AllocatorTraits<Allocator>::PropagateOnContainerSwap::value ||
	  AllocatorTraits<Allocator>::IsAlwaysEqual::value);

    /* --- Search --- */
    constexpr SizeType find(const String &str, SizeType pos = 0) const noexcept;
    constexpr SizeType find(const CharT* str, SizeType pos, SizeType len) const;
    constexpr SizeType find(const CharT* str, SizeType pos = 0) const;
    constexpr SizeType find(CharT chr, SizeType pos = 0) const noexcept;
    template<typename StringViewLike>
      constexpr SizeType find(const StringViewLike &str, SizeType pos = 0) const
      noexcept(is_nothrow_convertible_v<const StringViewLike&, StringView<CharT, Traits>>);

    constexpr SizeType rfind(const String &str, SizeType pos = npos) const noexcept;
    constexpr SizeType rfind(const CharT* str, SizeType pos, SizeType len) const;
    constexpr SizeType rfind(const CharT* str, SizeType pos = npos) const;
    constexpr SizeType rfind(CharT chr, SizeType pos = npos) const noexcept;
    template<typename StringViewLike>
      constexpr SizeType rfind(const StringViewLike &str, SizeType pos = npos) const
      noexcept(is_nothrow_convertible_v<const StringViewLike&, StringView<CharT, Traits>>);

    constexpr SizeType find_first_of(const String &str, SizeType pos = 0) const noexcept;
    constexpr SizeType find_first_of(const CharT* str, SizeType pos, SizeType len) const;
    constexpr SizeType find_first_of(const CharT* str, SizeType pos = 0) const;
    constexpr SizeType find_first_of(CharT chr, SizeType pos = 0) const noexcept;
    template<typename StringViewLike>
      constexpr SizeType find_first_of(const StringViewLike &str, SizeType pos = 0) const
      noexcept(is_nothrow_convertible_v<const StringViewLike&, StringView<CharT, Traits>>);

    constexpr SizeType find_first_not_of(const String &str, SizeType pos = 0) const noexcept;
    constexpr SizeType find_first_not_of(const CharT* str, SizeType pos, SizeType len) const;
    constexpr SizeType find_first_not_of(const CharT* str, SizeType pos = 0) const;
    constexpr SizeType find_first_not_of(CharT chr, SizeType pos = 0) const noexcept;
    template<typename StringViewLike>
      constexpr SizeType find_first_not_of(const StringViewLike &str, SizeType pos = 0) const
      noexcept(is_nothrow_convertible_v<const StringViewLike&, StringView<CharT, Traits>>);

    constexpr SizeType find_last_of(const String &str, SizeType pos = npos) const noexcept;
    constexpr SizeType find_last_of(const CharT* str, SizeType pos, SizeType len) const;
    constexpr SizeType find_last_of(const CharT* str, SizeType pos = npos) const;
    constexpr SizeType find_last_of(CharT chr, SizeType pos = npos) const noexcept;
    template<typename StringViewLike>
      constexpr SizeType find_last_of(const StringViewLike &str, SizeType pos = npos) const
      noexcept(is_nothrow_convertible_v<const StringViewLike&, StringView<CharT, Traits>>);

    constexpr SizeType find_last_not_of(const String &str, SizeType pos = npos) const noexcept;
    constexpr SizeType find_last_not_of(const CharT* str, SizeType pos, SizeType len) const;
    constexpr SizeType find_last_not_of(const CharT* str, SizeType pos = npos) const;
    constexpr SizeType find_last_not_of(CharT chr, SizeType pos = npos) const noexcept;
    template<typename StringViewLike>
      constexpr SizeType find_last_not_of(const StringViewLike &str, SizeType pos = npos) const
      noexcept(is_nothrow_convertible_v<const StringViewLike&, StringView<CharT, Traits>>);

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
constexpr me::detail::String<CharT, Traits, Allocator>::String(SizeType chr_count, CharT chr)
{
  m_capacity = chr_count + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = chr_count;
  for (SizeType i = 0; i != chr_count; i++)
    m_data[i] = chr;
  m_data[m_length] = CharT('\0');
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const String &str, SizeType str_pos, SizeType str_len)
{
  m_capacity = str_len + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = str_len;
  for (SizeType i = 0; i != str_len; i++)
    m_data[i] = str[str_pos++];
  m_data[m_length] = CharT('\0');
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const CharT* str, SizeType str_len)
{
  m_capacity = str_len + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  m_length = str_len;
  for (SizeType i = 0; i != str_len; i++)
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
constexpr me::detail::String<CharT, Traits, Allocator>::String(const String &str)
{
  m_length = str.m_length;
  m_capacity = m_length + 1;
  m_data = AllocatorTraits<Allocator>::allocate(m_capacity);
  for (SizeType i = 0; i != m_length; i++)
    m_data[i] = str.m_data[i];
  m_data[m_length] = CharT('\0');
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
constexpr me::detail::String<CharT, Traits, Allocator>::String(const StringViewLike &str)
  : String(str.data(), str.length())
{
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>::String(const StringViewLike &str, SizeType str_pos, SizeType str_len)
  : String(str.substring(str_pos, str_len))
{
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>::~String()
{
  if (m_data == nullptr)
    return;

  AllocatorTraits<Allocator>::deallocate(m_data);
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(const String &str)
{
#if LIBME_STRING_CHECK == 1
  if (str == *this)
    return;
#endif

  m_length = str.length();
  reserve(m_length + 1);

  for (SizeType i = 0; i != m_length; i++)
    m_data[i] = str[i];
  m_data[m_length] = CharT('\0');
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(String &&str)
  noexcept(AllocatorTraits<Allocator>::PropagateOnContainerMoveAssignment::value ||
      AllocatorTraits<Allocator>::IsAlwaysEqual::value)
{
  m_data = str.m_data;
  m_length = str.m_length;
  m_capacity = str.m_capacity;
  str.m_data = nullptr;
  str.m_length = str.m_capacity = 0;
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(const CharT* str)
{
  m_length = Traits::length(str);

  reserve(m_length + 1);

  for (SizeType i = 0; i != m_length; i++)
    m_data[i] = str[i];
  m_data[m_length] = CharT('\0');
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(CharT chr)
{
  m_length = 1;

  reserve(2);

  m_data[0] = chr;
  m_data[1] = CharT('\0');
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(InitializerList<CharT> list)
{
  m_length = list.length();

  reserve(m_length + 1);

  for (SizeType i = 0; i != m_length; i++)
    m_data[i] = list.begin()[i];
  m_data[m_length] = CharT('\0');
  return *this;
}

template<typename CharT, typename Traits, typename Allocator>
template<typename StringViewLike>
constexpr me::detail::String<CharT, Traits, Allocator>&
  me::detail::String<CharT, Traits, Allocator>::operator=(const StringViewLike &str)
{
  m_length = str.length();

  reserve(m_length + 1);

  for (SizeType i = 0; i != m_length; i++)
    m_data[i] = str[i];
  m_data[m_length] = CharT('\0');
  return *this;
}

/* end class me::detail::String */

#endif // LIBME_DETAIL_STRING_HPP
