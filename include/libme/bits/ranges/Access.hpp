#ifndef LIBME_BITS_RANGES_ACCESS_HPP
  #define LIBME_BITS_RANGES_ACCESS_HPP

#include "libme/TypeTraits.hpp"

/* ranges */
#include "libme/bits/ranges/Concepts.hpp"

/* iterator */
#include "libme/bits/iterator/Concepts.hpp"

namespace me::ranges {

  template<typename T>
  inline constexpr bool enable_borrowed_range = false;

  template<typename T>
  inline constexpr bool disable_sized_range = false;

  struct ViewBase { };

  template<typename T>
  inline constexpr bool __is_derived_from_view_interface = DerivedFrom<T, ViewBase>;

  template<typename T>
  inline constexpr bool enable_view = DerivedFrom<T, ViewBase> || __is_derived_from_view_interface<T>;


  template<typename T>
  concept __CanBorrow = is_lvalue_reference_v<T> || enable_borrowed_range<T>;

  /* begin() function */
  inline namespace __cust {

    template<typename T>
    concept __HasMemberBegin = requires(T &&t) {
      { __decay_copy(t.begin()) } -> InputOrOutputIterator;
    };

    template<typename T>
    concept __UnspecifiedBegin = InputOrOutputIterator<T> && (is_class_v<T> || is_enum_v<T>) && requires(T &&t) {
      { __decay_copy(begin(t)) } -> InputOrOutputIterator;
    };

    struct __Begin {
      template<typename T>
	requires is_array_v<T>
      constexpr auto operator()(T &t)
      {
	return t + 0;
      }

      template<typename T>
	requires __HasMemberBegin<T>
      constexpr auto operator()(T &&t)
      {
	return forward<T>(t).begin();
      }

      template<typename T>
	requires __UnspecifiedBegin<T>
      constexpr auto operator()(T &&t)
      {
	return begin(forward<T>(t));
      }
    };

    inline namespace __func {
      inline constexpr __Begin begin = { };
    }

  } // namespace __cust

  template<typename T>
  using Iterator_T = decltype(ranges::begin(declval<T&>()));

  /* end() function */
  inline namespace __cust {

    template<typename T>
    concept __HasMemberEnd = requires(T &&t) {
      { __decay_copy(t.end()) } -> SentinelFor<Iterator_T<T>>;
    };

    template<typename T>
    concept __UnspecifiedEnd = (is_class_v<T> || is_enum_v<T>) && requires(T &&t) {
      { __decay_copy(end(t)) } -> SentinelFor<Iterator_T<T>>;
    };

    struct __End {
      template<typename T>
      constexpr auto operator()(T &t)
      {
	return t + extent_v<T>;
      }

      template<typename T>
	requires __HasMemberEnd<T>
      constexpr auto operator()(T &&t)
      {
	return forward<T>(t).end();
      }

      template<typename T>
	requires __UnspecifiedEnd<T>
      constexpr auto operator()(T &&t)
      {
	return end(forward<T>(t));
      }
    };

    inline namespace __func {
      inline constexpr __End end = { };
    }

  } // namespace __cust

  /* length() function */
  inline namespace __cust {

    template<typename T>
    concept __HasMemberLength = requires(T &&t) {
      { __decay_copy(t.length()) } -> __IntegerLike;
    };

    template<typename T>
    concept __UnspecifiedLength = requires(T &&t) {
      { __decay_copy(length(t)) } -> __IntegerLike;
    };

    struct __Length {
      template<typename T>
	requires is_array_v<T>
      constexpr auto operator()(T&&)
      {
	return extent_v<T>;
      }

      template<typename T>
	requires (!ranges::disable_sized_range<RemoveCV_T<T>>) &&
	__HasMemberLength<T>
      constexpr auto operator()(T &&t)
      {
	return forward<T>(t).length();
      }

      template<typename T>
	requires (!ranges::disable_sized_range<RemoveCV_T<T>>) &&
	__UnspecifiedLength<T>
      constexpr auto operator()(T &&t)
      {
	return length(forward<T>(t));
      }
    };

    inline namespace __func {
      inline constexpr __Length length = { };
    }

  } // namespace __cust

  template<typename R>
  using RangeDifference_T = IterDifference_T<Iterator_T<R>>;

  /* data() function */
  inline namespace __cust {

    template<typename T>
    concept __MemberData = __CanBorrow<T> ||
    requires(T &&t) {
      { forward<T>(t) } -> __CanBorrow;
      { t.data() } -> __PtrToObject;
    };

    template<typename T>
    concept __UnspecifiedData = requires(T &&t) {
      { ranges::begin(forward<T>(t)) } -> ContiguousIterator;
    };

    struct __Data {
      template<__MemberData T>
      constexpr RemoveReference_T<ranges::RangeDifference_T<T>>* operator()(T &t)
      {
	return forward<T>(t).data();
      }

      template<__UnspecifiedData T>
      constexpr RemoveReference_T<ranges::RangeDifference_T<T>>* operator()(T &&t)
      {
	return to_address(ranges::begin(forward<T>(t)));
      }
    };

    inline namespace __func {
      inline constexpr __Data data = { };
    }

  } // namespace __cust

  template<typename T>
  concept Range = requires(T &t) {
    ranges::begin(t);
    ranges::end(t);
  };

  template<typename T>
  concept BorrowedRange = Range<T> && (is_lvalue_reference_v<T> || enable_borrowed_range<RemoveCVRef_T<T>>);

  template<typename T>
  concept SizedRange = Range<T> && requires(T &t) { ranges::length(t); };

  template<typename T>
  concept View = Range<T> && Movable<T> && enable_view<T>;

  template<typename R, typename T>
  concept OutputRange = Range<R> && OutputIterator<Iterator_T<R>, T>;

  template<typename T>
  concept InputRange = Range<T> && InputIterator<Iterator_T<T>>;

  template<typename T>
  concept ForwardRange = InputRange<T> && ForwardIterator<Iterator_T<T>>;

  template<typename T>
  concept BidirectionalRange = ForwardRange<T> && BidirectionalIterator<Iterator_T<T>>;

  template<typename T>
  concept RandomAccessRange = BidirectionalRange<T> && RandomAccessIterator<Iterator_T<T>>;

  template<typename T>
  concept ContiguousRange = RandomAccessRange<T> && ContiguousIterator<Iterator_T<T>> &&
    requires(T &t) {
      { ranges::data(t) } -> SameAs<AddPointer_T<RangeDifference_T<T>>>;
    };

  template<Range R>
  using Sentinel_T = decltype(ranges::end(declval<R&>()));

  template<typename T>
  concept CommonRange = Range<T> && SameAs<Iterator_T<T>, Sentinel_T<T>>;

  template<typename R>
  inline constexpr bool __is_initializer_list = true; // TODO

  template<typename T>
  concept ViewableRange = Range<T> &&
    ((View<RemoveCVRef_T<T>> && ConstructibleFrom<RemoveCVRef_T<T>, T>) ||
     (!View<RemoveCVRef_T<T>> &&
      (is_lvalue_reference_v<T> || (Movable<RemoveReference_T<T>> && !__is_initializer_list<T>))));

  template<typename D>
    requires is_class_v<D> && SameAs<D, RemoveCV_T<D>>
  class ViewInterface;

  enum class SubrangeKinds : bool {
    UNSIZED, SIZED
  };

  template<InputOrOutputIterator I, SentinelFor<I> S = I, SubrangeKinds K = /* TODO */ SubrangeKinds::SIZED>
    requires (K == SubrangeKinds::SIZED || !SizedSentinelFor<S, I>)
  class Subrange;

  template<typename I, typename S, SubrangeKinds K>
  inline constexpr bool enable_borrowed_range<Subrange<I, S, K>> = true;

  struct Dangling;

  template<Range R>
  using BorrowedIterator_T = bool; // TODO

  template<Range R>
  using BorrowedSubrange_T = bool; // TODO

  template<typename T>
    requires is_object_v<T>
  class EmptyView;

  template<typename T>
  inline constexpr bool enable_borrowed_range<EmptyView<T>> = true;

  namespace views {

    template<typename T>
    inline constexpr EmptyView<T> empty  { };

  } // namespace views

  template<CopyConstructible T>
    requires is_object_v<T>
  class SingleView;

  namespace views {

    inline constexpr bool single = false; // TODO

  } // namespace views

  template<bool Const, typename T>
  using __MaybeConst = Conditional_T<Const, const T, T>;

  //template<WeaklyIncrementable W, Semiregular Bound = Unreachable

} // namespace me::ranges

#endif // LIBME_BITS_RANGES_ACCESS_HPP
