#ifndef LIBME_DETAIL_STRING_VIEW_HPP
  #define LIBME_DETAIL_STRING_VIEW_HPP

#include "libme/Algorithm.hpp"
#include "libme/Utility.hpp"
#include "libme/Iterator.hpp"
#include "libme/Ranges.hpp"

namespace me::detail {

  template<typename CharT, typename Traits>
  class StringView {

  public:

    typedef Traits TraitsType;
    typedef CharT ValueType;
    typedef CharT* Pointer;
    typedef const CharT* ConstPointer;
    typedef CharT& Reference;
    typedef const CharT& ConstReference;
    typedef ConstPointer Iterator;
    typedef Iterator ConstIterator;
    typedef ReverseIterator<ConstIterator> ConstReverseIterator;
    typedef ConstReverseIterator ReverseIterator;
    typedef size_t SizeType;
    typedef ptrdiff_t DifferenceType;

    static constexpr SizeType npos = SizeType(~0);

  private:

    ConstPointer m_begin;
    SizeType m_length;

  public:

    /* --- Constructors --- */
    constexpr StringView() noexcept;
    constexpr StringView(const StringView &other) noexcept = default;
    constexpr StringView(const CharT* str, SizeType count);
    constexpr StringView(const CharT* str);

    template<ContiguousIterator Iter, SizedSentinelFor<Iter> End>
    constexpr StringView(Iter first, End last)
      requires SameAs<IterValue_T<Iter>, CharT> && (!ConvertibleTo<End, size_t>);

    template<typename R>
    constexpr StringView(R &&range)
      requires (!SameAs<RemoveCVRef_T<R>, StringView>);

    constexpr StringView(nullptr_t) = delete;

    /* --- Assign operator --- */
    constexpr StringView& operator=(const StringView &&view) noexcept = default;

    /* --- Iterators --- */
    constexpr ConstIterator begin() const noexcept;
    constexpr ConstIterator end() const noexcept;
    constexpr ConstIterator rbegin() const noexcept;
    constexpr ConstIterator rend() const noexcept;

    /* --- Access --- */
    constexpr ConstReference operator[](SizeType pos) const;
    constexpr ConstReference at(SizeType pos) const;
    constexpr ConstReference front() const;
    constexpr ConstReference back() const;
    constexpr ConstPointer data() const noexcept;

    /* --- Capacity --- */
    constexpr SizeType length() const noexcept;
    constexpr SizeType max_length() const noexcept;
    constexpr SizeType is_empty() const noexcept;

    /* --- Modifiers --- */
    constexpr void remove_prefix(SizeType num);
    constexpr void remove_suffix(SizeType num);
    constexpr void swap(StringView &view);

    /* --- Operations --- */
    constexpr SizeType copy(CharT* dest, SizeType count, SizeType pos = 0) const;

    constexpr StringView substring(SizeType pos = 0, SizeType count = npos) const;

    constexpr int compare(StringView view) const noexcept;
    constexpr int compare(SizeType pos1, SizeType count1, StringView view) const;
    constexpr int compare(SizeType pos1, SizeType count1, StringView view, SizeType pos2, SizeType count2) const;
    constexpr int compare(const CharT* str) const;
    constexpr int compare(SizeType pos1, SizeType count1, const CharT* str) const;
    constexpr int compare(SizeType pos1, SizeType count1, const CharT* str, SizeType count2) const;

    constexpr bool starts_with(StringView view) const noexcept;
    constexpr bool starts_with(CharT c) const noexcept;
    constexpr bool starts_with(const CharT* str) const;

    constexpr bool ends_with(StringView view) const noexcept;
    constexpr bool ends_with(CharT c) const noexcept;
    constexpr bool ends_with(const CharT* str) const;

    constexpr bool contains(StringView view) const noexcept;
    constexpr bool contains(CharT c) const noexcept;
    constexpr bool contains(const CharT* str) const;

    constexpr SizeType find(StringView view, SizeType pos = 0) const noexcept;
    constexpr SizeType find(CharT c, SizeType pos = 0) const noexcept;
    constexpr SizeType find(const CharT* str, SizeType pos, SizeType count) const;
    constexpr SizeType find(const CharT* str, SizeType pos = 0) const;

    constexpr SizeType rfind(StringView view, SizeType pos = npos) const noexcept;
    constexpr SizeType rfind(CharT c, SizeType pos = npos) const noexcept;
    constexpr SizeType rfind(const CharT* str, SizeType pos, SizeType count) const;
    constexpr SizeType rfind(const CharT* str, SizeType pos = npos) const;

    constexpr SizeType find_first_of(StringView view, SizeType pos = 0) const noexcept;
    constexpr SizeType find_first_of(CharT c, SizeType pos = 0) const noexcept;
    constexpr SizeType find_first_of(const CharT* str, SizeType pos, SizeType count) const;
    constexpr SizeType find_first_of(const CharT* str, SizeType pos = 0) const;

    constexpr SizeType find_first_not_of(StringView view, SizeType pos = 0) const noexcept;
    constexpr SizeType find_first_not_of(CharT c, SizeType pos = 0) const noexcept;
    constexpr SizeType find_first_not_of(const CharT* str, SizeType pos, SizeType count) const;
    constexpr SizeType find_first_not_of(const CharT* str, SizeType pos = 0) const;

    constexpr SizeType find_last_of(StringView view, SizeType pos = npos) const noexcept;
    constexpr SizeType find_last_of(CharT c, SizeType pos = npos) const noexcept;
    constexpr SizeType find_last_of(const CharT* str, SizeType pos, SizeType count) const;
    constexpr SizeType find_last_of(const CharT* str, SizeType pos = npos) const;

    constexpr SizeType find_last_not_of(StringView view, SizeType pos = npos) const noexcept;
    constexpr SizeType find_last_not_of(CharT c, SizeType pos = npos) const noexcept;
    constexpr SizeType find_last_not_of(const CharT* str, SizeType pos, SizeType count) const;
    constexpr SizeType find_last_not_of(const CharT* str, SizeType pos = npos) const;

  };

} // namespace me::detail

namespace me {

  template<typename CharT, typename Traits>
  constexpr bool operator==(detail::StringView<CharT, Traits> lhs,
      detail::StringView<CharT, Traits> rhs) noexcept;

  template<typename CharT, typename Traits>
  constexpr CommonComparsionCategory_T<SynthThreeWayResult<detail::StringView<CharT, Traits>>>
    operator<=>(detail::StringView<CharT, Traits> lhs, detail::StringView<CharT, Traits> rhs) noexcept;

} // namespace me

/* ---------------------------- */
/* class me::detail::StringView */
/* ---------------------------- */
template<typename CharT, typename Traits>
constexpr me::detail::StringView<CharT, Traits>::StringView()
  noexcept
  : m_begin(nullptr), m_length(0)
{
}

template<typename CharT, typename Traits>
constexpr me::detail::StringView<CharT, Traits>::StringView(const CharT* str, SizeType count)
  : m_begin(str), m_length(count)
{
}

template<typename CharT, typename Traits>
constexpr me::detail::StringView<CharT, Traits>::StringView(const CharT* str)
  : m_begin(str), m_length(TraitsType::length(str))
{
}

template<typename CharT, typename Traits>
template<me::ContiguousIterator Iter, me::SizedSentinelFor<Iter> End>
constexpr me::detail::StringView<CharT, Traits>::StringView(Iter first, End last)
  requires SameAs<IterValue_T<Iter>, CharT> && (!ConvertibleTo<End, size_t>)
  : m_begin(first), m_length(last - first)
{
}

template<typename CharT, typename Traits>
template<typename R>
constexpr me::detail::StringView<CharT, Traits>::StringView(R &&range)
  requires (!SameAs<RemoveCVRef_T<R>, StringView>)
  : m_begin(ranges::data(range)), m_length(ranges::length(range))
{
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstIterator
  me::detail::StringView<CharT, Traits>::begin() const
  noexcept
{
  return m_begin;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstIterator
  me::detail::StringView<CharT, Traits>::end() const
  noexcept
{
  return m_begin + m_length;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstIterator
  me::detail::StringView<CharT, Traits>::rbegin() const
  noexcept
{
  return make_reverse_iterator(m_begin);
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstIterator
  me::detail::StringView<CharT, Traits>::rend() const
  noexcept
{
  return make_reverse_iterator(m_begin + m_length);
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstReference
  me::detail::StringView<CharT, Traits>::operator[](SizeType pos) const
{
  return m_begin[pos];
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstReference
  me::detail::StringView<CharT, Traits>::at(SizeType pos) const
{
  return m_begin[pos];
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstReference
  me::detail::StringView<CharT, Traits>::front() const
{
  return m_begin[0];
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstReference
  me::detail::StringView<CharT, Traits>::back() const
{
  return m_begin[m_length - 1];
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::ConstPointer
  me::detail::StringView<CharT, Traits>::data() const
  noexcept
{
  return m_begin;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::length() const
  noexcept
{
  return m_length;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::max_length() const
  noexcept
{
  return 123456; // TODO
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::is_empty() const
  noexcept
{
  return m_length == 0;
}

template<typename CharT, typename Traits>
constexpr void
  me::detail::StringView<CharT, Traits>::remove_prefix(SizeType num)
{
}

template<typename CharT, typename Traits>
constexpr void
  me::detail::StringView<CharT, Traits>::remove_suffix(SizeType num)
{
}

template<typename CharT, typename Traits>
constexpr void
  me::detail::StringView<CharT, Traits>::swap(StringView &view)
{
  ::me::swap(m_begin, view.m_begin);
  ::me::swap(m_length, view.m_length);
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::copy(CharT* dest, SizeType count, SizeType pos) const
{
  Traits::copy(dest, m_begin + pos, min(count, m_length - pos));
  return 0;
}

template<typename CharT, typename Traits>
constexpr me::detail::StringView<CharT, Traits>
  me::detail::StringView<CharT, Traits>::substring(SizeType pos, SizeType count) const
{
  return StringView<CharT, Traits>(m_begin + pos, pos + min(count, m_length - pos));
}

template<typename CharT, typename Traits>
constexpr int
  me::detail::StringView<CharT, Traits>::compare(StringView view) const
  noexcept
{
  return Traits::compare(m_begin, view.m_begin, min(m_length, view.m_length));
}

template<typename CharT, typename Traits>
constexpr int
  me::detail::StringView<CharT, Traits>::compare(SizeType pos1, SizeType count1, StringView view) const
{
  return substring(pos1, count1).compare(view);
}

template<typename CharT, typename Traits>
constexpr int
  me::detail::StringView<CharT, Traits>::compare(SizeType pos1, SizeType count1, StringView view, SizeType pos2, SizeType count2) const
{
  return substring(pos1, count1).compare(view.substring(pos2, count2));
}

template<typename CharT, typename Traits>
constexpr int
  me::detail::StringView<CharT, Traits>::compare(const CharT* str) const
{
  return compare(StringView(str));
}

template<typename CharT, typename Traits>
constexpr int
  me::detail::StringView<CharT, Traits>::compare(SizeType pos1, SizeType count1, const CharT* str) const
{
  return substring(pos1, count1).compare(StringView(str));
}

template<typename CharT, typename Traits>
constexpr int
  me::detail::StringView<CharT, Traits>::compare(SizeType pos1, SizeType count1, const CharT* str, SizeType count2) const
{
  return substring(pos1, count1).compare(StringView(str, count2));
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::starts_with(StringView view) const
  noexcept
{
  return true;
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::starts_with(CharT c) const
  noexcept
{
  return true;
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::starts_with(const CharT* str) const
{
  return true;
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::ends_with(StringView view) const
  noexcept
{
  return true;
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::ends_with(CharT c) const
  noexcept
{
  return true;
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::ends_with(const CharT* str) const
{
  return true;
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::contains(StringView view) const
  noexcept
{
  return find(view) != npos;
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::contains(CharT c) const
  noexcept
{
  return find(c) != npos;
}

template<typename CharT, typename Traits>
constexpr bool
  me::detail::StringView<CharT, Traits>::contains(const CharT* str) const
{
  return find(str) != npos;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::find(StringView view, SizeType pos) const
  noexcept
{
  return 0;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::find(CharT c, SizeType pos) const
  noexcept
{
  return 0;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::find(const CharT* str, SizeType pos, SizeType count) const
{
  return 0;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::find(const CharT* str, SizeType pos) const
{
  return 0;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::rfind(StringView view, SizeType pos) const
  noexcept
{
  return 0;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::rfind(CharT c, SizeType pos) const
  noexcept
{
  return 0;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::rfind(const CharT* str, SizeType pos, SizeType count) const
{
  return 0;
}

template<typename CharT, typename Traits>
constexpr typename me::detail::StringView<CharT, Traits>::SizeType
  me::detail::StringView<CharT, Traits>::rfind(const CharT* str, SizeType pos) const
{
  return 0;
}

/* end class me::detail::StringView */

template<typename CharT, typename Traits>
constexpr bool
  me::operator==(detail::StringView<CharT, Traits> lhs, detail::StringView<CharT, Traits> rhs)
  noexcept
{
  if (lhs.length() != rhs.length())
    return false;

  for (size_t i = 0; i != lhs.length(); i++)
  {
    if (lhs.at(i) != rhs.at(i))
      return false;
  }
  return true;
}

template<typename CharT, typename Traits>
constexpr me::CommonComparsionCategory_T<me::SynthThreeWayResult<me::detail::StringView<CharT, Traits>>>
  me::operator<=>(detail::StringView<CharT, Traits> lhs, detail::StringView<CharT, Traits> rhs)
  noexcept
{
  return static_cast<CommonComparsionCategory_T<SynthThreeWayResult<detail::StringView<CharT, Traits>>>>(lhs.compare(rhs) <=> 0);
}

#endif
