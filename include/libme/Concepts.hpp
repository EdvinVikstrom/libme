#ifndef LIBME_CONCEPTS_HPP
  #define LIBME_CONCEPTS_HPP

#include "libme/TypeTraits.hpp"

namespace me {

  template<typename T, typename U>
    concept __SameAsImpl = is_same_v<T, U>;

  template<typename T, typename U>
    concept SameAs = __SameAsImpl<T, U> && __SameAsImpl<U, T>;

  template<typename Derived, typename Base>
    concept DerivedFrom =
      is_base_of_v<Base, Derived> &&
      is_convertible_v<const volatile Derived*, const volatile Base*>;

  template<typename From, typename To>
    concept ConvertibleTo =
      is_convertible_v<From, To> &&
      requires {
	static_cast<To>(declval<From>());
      };

  template<typename T, typename U>
    concept CommonReferenceWith =
      SameAs<CommonReference_T<T, U>, CommonReference_T<U, T>> &&
      ConvertibleTo<T, CommonReference_T<T, U>> &&
      ConvertibleTo<U, CommonReference_T<T, U>>;

  template<typename T, typename U>
    concept CommonWith =
      SameAs<CommonType_T<T, U>, CommonType_T<U, T>> &&
      requires {
	static_cast<CommonType_T<T, U>>(declval<T>());
	static_cast<CommonType_T<T, U>>(declval<U>());
      } &&
      CommonReferenceWith<AddLValueReference_T<const T>, AddLValueReference_T<const U>> &&
      CommonReferenceWith<AddLValueReference_T<CommonType_T<T, U>>, CommonReference_T<
	AddLValueReference_T<const T>,
	AddLValueReference_T<const U>>>;

  template<typename T>
    concept Integral = is_integral_v<T>;

  template<typename T>
    concept SignedIntegral = Integral<T> && is_signed_v<T>;

  template<typename T>
    concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;

  template<typename T>
    concept FloatingPoint = is_floating_point_v<T>;

  template<typename LHS, typename RHS>
    concept AssignableFrom =
      is_lvalue_reference_v<LHS> &&
      CommonReferenceWith<const RemoveReference_T<LHS>&, const RemoveReference_T<RHS>&> &&
      requires(LHS lhs, RHS &&rhs) {
	{ lhs = forward<RHS>(rhs) } -> SameAs<LHS>;
      };

  namespace ranges {

    inline namespace __cust {

      template<typename T>
      struct __SwapIsLVRA : FalseType { };

      template<typename T>
      struct __SwapIsLVRA<T(&)[]> : TrueType { };

      template<typename T, size_t N>
      struct __SwapIsLVRA<T(&)[N]> : TrueType { };

      struct __Swap { // TODO

        template<typename T, typename U>
          requires requires(T &&t, U &&u) {
            (void) swap(forward<T>(t), forward<U>(u));
          }
        constexpr void operator()(T &&t, U &&u) noexcept
        {
          (void) swap(forward<T>(t), forward<U>(u));
        }

      };

      inline namespace __func {
	inline constexpr __Swap swap = { };
      } // namespace __func

    } // namespace __cust

  } // namespace ranges

  template<typename T>
    concept Swappable = requires(T &a, T &b) { ranges::swap(a, b); };

  template<typename T, typename U>
    concept SwappableWith =
      CommonReferenceWith<T, U> &&
      requires(T &&t, U &&u) {
	ranges::swap(forward<T>(t), forward<T>(t));
	ranges::swap(forward<U>(u), forward<U>(u));
	ranges::swap(forward<T>(t), forward<U>(u));
	ranges::swap(forward<U>(u), forward<T>(t));
      };

  template<typename T>
    concept Destructible = is_nothrow_destructible_v<T>;

  template<typename T, typename... Args>
    concept ConstructibleFrom = Destructible<T> && is_constructible_v<T, Args...>;

  template<typename T>
    concept DefaultInitializable = ConstructibleFrom<T> && requires { T{}; (void) ::new T; }; // TODO: '(void) ::new T'

  template<typename T>
    concept MoveConstructible = ConstructibleFrom<T, T> && ConvertibleTo<T, T>;

  template<typename T>
    concept CopyConstructible =
      MoveConstructible<T> &&
      ConstructibleFrom<T, T&> && ConvertibleTo<T&, T> &&
      ConstructibleFrom<T, const T&> && ConvertibleTo<const T&, T> &&
      ConstructibleFrom<T, const T> && ConvertibleTo<const T, T>;

  // comparsion concepts

  template<typename T>
    concept __BooleanTestableImpl = ConvertibleTo<T, bool>;

  template<typename T>
    concept __BooleanTestable = __BooleanTestableImpl<T> && requires(T &&t) {
      { !forward<T>(t) } -> __BooleanTestableImpl;
    };

  template<typename T, typename U>
    concept __WeaklyEqualityComparableWith = requires(const RemoveReference_T<T> &t, const RemoveReference_T<U> &u) {
      { t == u } -> __BooleanTestable;
      { t != u } -> __BooleanTestable;
      { u == t } -> __BooleanTestable;
      { u != t } -> __BooleanTestable;
    };

  template<typename T>
    concept EqualityComparable = __WeaklyEqualityComparableWith<T, T>;

  template<typename T, typename U>
    concept EqualityComparableWith = EqualityComparable<T> && EqualityComparable<U> &&
      CommonReferenceWith<const RemoveReference_T<T>&, const RemoveReference_T<U>&> &&
      EqualityComparable<CommonReference_T<const RemoveReference_T<T>&, const RemoveReference_T<U>&>> &&
      __WeaklyEqualityComparableWith<T, U>;

  template<typename T, typename U>
    concept __PartiallyOrderedWith = true; // TODO

  template<typename T>
    concept TotallyOrdered = EqualityComparable<T> && __PartiallyOrderedWith<T, T>;

  template<typename T, typename U>
    concept TotallyOrderedWith = TotallyOrdered<T> && TotallyOrdered<U> &&
      EqualityComparableWith<T, U> &&
      TotallyOrdered<CommonReference_T<const RemoveReference_T<T>&, const RemoveReference_T<T>&>> &&
      __PartiallyOrderedWith<T, U>;

  // object concepts

  template<typename T>
    concept Movable = is_object_v<T> && MoveConstructible<T> &&
      AssignableFrom<T&, T> && Swappable<T>;

  template<typename T>
    concept Copyable = CopyConstructible<T> && Movable<T> && AssignableFrom<T&, T&> &&
      AssignableFrom<T&, const T&> && AssignableFrom<T&, const T>; 

  template<typename T>
    concept Semiregular = Copyable<T> && DefaultInitializable<T>;

  template<typename T>
    concept Regular = Semiregular<T> && EqualityComparable<T>;

  // callable concepts

  template<typename F, typename... Args>
    concept Invocable = requires(F &&f, Args&&... args) {
      invoke(forward<F>(f), forward<Args>(args)...);
    };

  template<typename F, typename... Args>
    concept RegularInvocable = Invocable<F, Args...>;

  template<typename F, typename... Args>
    concept Predicate = RegularInvocable<F, Args...> && __BooleanTestable<InvokeResult_T<F, Args...>>;

  template<typename R, typename T, typename U>
    concept Relation = Predicate<R, T, T> && Predicate<R, U, U> &&
      Predicate<R, T, U> && Predicate<R, U, T>;

  template<typename R, typename T, typename U>
    concept EquivalenceRelation = Relation<R, T, U>;

  template<typename R, typename T, typename U>
    concept StrictWeakOrder = Relation<R, T, U>;

  template<typename T>
  concept __IntegerLike = Integral<T> && !SameAs<T, bool>;

  template<typename T>
  concept __SignedIntegerLike = SignedIntegral<T>;

  template<typename T>
  concept __PtrToObject = is_pointer_v<T>; // TODO

} // namespace me

#endif // LIBME_CONCEPTS_HPP
