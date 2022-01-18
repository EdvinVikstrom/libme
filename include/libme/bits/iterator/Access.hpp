#ifndef LIBME_BITS_ITERATOR_ACCESS_HPP
  #define LIBME_BITS_ITERATOR_ACCESS_HPP

#include "libme/Compare.hpp"
#include "libme/InitializerList.hpp"
#include "libme/detail/CharTraits.hpp"

/* iterator */
#include "libme/bits/iterator/Ranges.hpp"

/* ranges */
#include "libme/bits/ranges/Access.hpp"

namespace me {

  template<__Dereferenceable T>
    requires requires(T &t) {
      { ranges::iter_move(t) } -> __CanReference;
    }
  using iter_rvalue_reference_t = decltype(ranges::iter_move(declval<T&>()));

  /* classes */

  struct InputIteratorTag { };
  struct OutputIteratorTag { };
  struct ForwardIteratorTag : public InputIteratorTag { };
  struct BidirectionalIteratorTag : public ForwardIteratorTag { };
  struct RandomAccessIteratorTag : public BidirectionalIteratorTag { };
  struct ContiguousIteratorTag : public RandomAccessIteratorTag { };

  // iterator operations

  template<typename InputIterator, typename Distance>
    constexpr void advance(InputIterator &i, Distance n);

  template<typename InputIterator>
    constexpr typename IteratorTraits<InputIterator>::DifferenceType
      distance(InputIterator first, InputIterator last);

  template<typename InputIterator>
    constexpr InputIterator next(InputIterator x, typename IteratorTraits<InputIterator>::DifferenceType n = 1);

  template<typename BidirectionalIterator>
    constexpr BidirectionalIterator prev(BidirectionalIterator x, typename IteratorTraits<BidirectionalIterator>::DifferenceType n = 1);

  /* reverse iterator */

  template<typename Iterator>
  class ReverseIterator;

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator==(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator!=(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator<(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator>(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator<=(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator>=(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs);

  template<typename Iterator1, ThreeWayComparableWith<Iterator1> Iterator2>
  constexpr CompareThreeWayResult_T<Iterator1, Iterator2>
    operator<=>(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr auto operator-(const ReverseIterator<Iterator1> &lhs, const ReverseIterator<Iterator2> &rhs)
    -> decltype(rhs.base() - lhs.base());

  template<typename Iterator>
  constexpr ReverseIterator<Iterator> operator+(IterDifference_T<Iterator> n, const ReverseIterator<Iterator> &iter);

  template<typename Iterator>
  constexpr ReverseIterator<Iterator> make_reverse_iterator(Iterator i);

  template<typename Iterator1, typename Iterator2>
    requires (!SizedSentinelFor<Iterator1, Iterator2>)
  inline constexpr bool disable_sized_sentinel_for<ReverseIterator<Iterator1>, ReverseIterator<Iterator2>> = true;

  /* insert iterator */

  template<typename Container>
  class BackInsertIterator;

  template<typename Container>
  constexpr BackInsertIterator<Container> back_inserter(Container &val);

  template<typename Container>
  class FrontInsertIterator;

  template<typename Container>
  constexpr FrontInsertIterator<Container> front_inserter(Container &val);

  template<typename Container>
  class InsertIterator;

  template<typename Container>
  constexpr InsertIterator<Container> inserter(Container &val, ranges::Iterator_T<Container> i);

  template<typename Iterator>
  class MoveIterator;

  /* move iterator */

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator==(const MoveIterator<Iterator1> &lhs, const MoveIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator<(const MoveIterator<Iterator1> &lhs, const MoveIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator>(const MoveIterator<Iterator1> &lhs, const MoveIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator<=(const MoveIterator<Iterator1> &lhs, const MoveIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr bool operator>=(const MoveIterator<Iterator1> &lhs, const MoveIterator<Iterator2> &rhs);

  template<typename Iterator1, ThreeWayComparableWith<Iterator1> Iterator2>
  constexpr CompareThreeWayResult_T<Iterator1, Iterator2>
    operator<=>(const MoveIterator<Iterator1> &lhs, const MoveIterator<Iterator2> &rhs);

  template<typename Iterator1, typename Iterator2>
  constexpr auto operator-(const MoveIterator<Iterator1> &lhs, const MoveIterator<Iterator2> &rhs)
    -> decltype(lhs.base() - rhs.base());

  template<typename Iterator>
  constexpr MoveIterator<Iterator> operator+(IterDifference_T<Iterator> n, const MoveIterator<Iterator> &val);

  template<typename Iterator>
  constexpr MoveIterator<Iterator> make_move_iterator(Iterator iter);

  template<Semiregular S>
  class MoveSentinel;

  /* common iterator */

  template<InputOrOutputIterator I, SentinelFor<I> S>
    requires (!SameAs<I, S> && Copyable<I>)
  class CommonIterator;

  template<typename I, typename S>
  struct IncrementableTraits<CommonIterator<I, S>>;

  template<InputIterator I, typename S>
  struct IteratorTraits<CommonIterator<I, S>>;

  struct DefaultSentinel_T { };
  inline constexpr DefaultSentinel_T default_sentinel { };

  /* counted iterator */

  template<InputOrOutputIterator I>
  class CountedIterator;

  template<InputIterator I>
    requires true // TODO
  struct IteratorTraits<CountedIterator<I>>;

  struct UnreachableSentinel_T {
    template<WeaklyIncrementable I>
    friend constexpr bool operator==(UnreachableSentinel_T, const I&) noexcept
    { return false; }
  };
  inline constexpr UnreachableSentinel_T unreachable_sentinel { };

  /* stream iterator */

  template<typename T, typename CharT = char, typename Traits = detail::CharTraits<CharT>, typename Distance = ptrdiff_t>
  class IStreamIterator;

  template<typename T, typename CharT, typename Traits, typename Distance>
  bool operator==(const IStreamIterator<T, CharT, Traits, Distance> &lhs, const IStreamIterator<T, CharT, Traits, Distance> &rhs);

  template<typename T, typename CharT = char, typename Traits = detail::CharTraits<CharT>>
  class OStreamIterator;

  template<typename CharT, typename Traits = detail::CharTraits<CharT>>
  class IStreamBufIterator;

  template<typename CharT, typename Traits>
  bool operator==(const IStreamBufIterator<CharT, Traits> &lhs, const IStreamBufIterator<CharT, Traits> &rhs);

  template<typename CharT, typename Traits = detail::CharTraits<CharT>>
  class OStreamBufIterator;

  /* range access */

  template<typename C> constexpr auto begin(C &c) -> decltype(c.begin());
  template<typename C> constexpr auto begin(const C &c) -> decltype(c.begin());
  template<typename C> constexpr auto end(C &c) -> decltype(c.begin());
  template<typename C> constexpr auto end(const C &c) -> decltype(c.begin());

  template<typename T, size_t N> constexpr T* begin(T (&arr)[N]) noexcept;
  template<typename T, size_t N> constexpr T* end(T (&arr)[N]) noexcept;

  template<typename C> constexpr auto cbegin(const C &c) noexcept(noexcept(begin(c)))
    -> decltype(begin(c));
  template<typename C> constexpr auto cend(const C &c) noexcept(noexcept(end(c)))
    -> decltype(end(c));

  template<typename C> constexpr auto rbegin(C &c) -> decltype(c.rbegin());
  template<typename C> constexpr auto rbegin(const C &c) -> decltype(c.rbegin());
  template<typename C> constexpr auto rend(C &c) -> decltype(c.rend());
  template<typename C> constexpr auto rend(const C &c) -> decltype(c.rend());

  template<typename T, size_t N> constexpr ReverseIterator<T*> rbegin(T (&arr)[N]);
  template<typename T, size_t N> constexpr ReverseIterator<T*> rend(T (&arr)[N]);

  template<typename E> constexpr ReverseIterator<const E*> rbegin(InitializerList<E> list);
  template<typename E> constexpr ReverseIterator<const E*> rend(InitializerList<E> list);

  template<typename C> constexpr auto crbegin(const C &c) -> decltype(rbegin(c));
  template<typename C> constexpr auto crend(const C &c) -> decltype(rend(c));

  template<typename C> constexpr auto length(const C &c) -> decltype(c.length());
  template<typename T, size_t N> constexpr size_t length(const T (&arr)[N]) noexcept;

  template<typename C> constexpr auto slength(const C &c) -> CommonType_T<ptrdiff_t, MakeSigned_T<decltype(c.length())>>;
  template<typename T, ptrdiff_t N> constexpr ptrdiff_t slength(const T (&arr)[N]) noexcept;

  template<typename C> [[nodiscard]] constexpr auto is_empty(const C &c) -> decltype(c.is_empty());
  template<typename T, size_t N> [[nodiscard]] constexpr bool is_empty(const T (&arr)[N]) noexcept;

  template<typename E> [[nodiscard]] constexpr bool is_empty(InitializerList<E> list) noexcept;

  template<typename C> constexpr auto data(C &c) -> decltype(c.data());
  template<typename C> constexpr auto data(const C &c) -> decltype(c.data());
  template<typename T, size_t N> constexpr T* data(T (&arr)[N]) noexcept;
  template<typename E> constexpr const E* data(InitializerList<E> list) noexcept;

} // namespace me
// Implementations:

#endif // LIBME_BITS_ITERATOR_ACCESS_HPP
