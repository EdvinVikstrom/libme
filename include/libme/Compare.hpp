#ifndef LIBME_COMPARE_HPP
  #define LIBME_COMPARE_HPP

#include "libme/TypeTraits.hpp"
#include "libme/Concepts.hpp"

namespace me {

  namespace cmp_cat {

    /* -2: unordered, -1: less, 0: equivalent, 1: greater */
    using Type = int8_t;

    enum class Ordered {
      LESS = -1, EQUIVALENT = 0, GREATER = 1
    };

    enum class Unordered {
      UNORDERED = -2
    };

    struct UnspecifiedParam {
      constexpr UnspecifiedParam(UnspecifiedParam*) noexcept { };
    };

  } // namespace cmp_cat

  class PartialOrdering {

  private:

    cmp_cat::Type m_value;

    constexpr explicit PartialOrdering(cmp_cat::Ordered value) noexcept
      : m_value(static_cast<cmp_cat::Type>(value))
    { }

    constexpr explicit PartialOrdering(cmp_cat::Unordered value) noexcept
      : m_value(static_cast<cmp_cat::Type>(value))
    { }

    friend class WeakOrdering;
    friend class StrongOrdering;

  public:

    static const PartialOrdering less;
    static const PartialOrdering equivalent;
    static const PartialOrdering greater;
    static const PartialOrdering unordered;

    [[nodiscard]] friend constexpr bool operator==(PartialOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == 0; }
    [[nodiscard]] friend constexpr bool operator==(PartialOrdering lhs, PartialOrdering rhs) noexcept = default;

    [[nodiscard]] friend constexpr bool operator<(PartialOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == -1; }
    [[nodiscard]] friend constexpr bool operator<(cmp_cat::UnspecifiedParam, PartialOrdering rhs) noexcept
    { return rhs.m_value == 1; }

    [[nodiscard]] friend constexpr bool operator>(PartialOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == 1; }
    [[nodiscard]] friend constexpr bool operator>(cmp_cat::UnspecifiedParam, PartialOrdering rhs) noexcept
    { return rhs.m_value == -1; }

    [[nodiscard]] friend constexpr bool operator<=(PartialOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value <= 0; }
    [[nodiscard]] friend constexpr bool operator<=(cmp_cat::UnspecifiedParam, PartialOrdering rhs) noexcept
    { return cmp_cat::Type(rhs.m_value & 1) == rhs.m_value; }

    [[nodiscard]] friend constexpr bool operator>=(PartialOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return cmp_cat::Type(lhs.m_value & 1) == lhs.m_value; }
    [[nodiscard]] friend constexpr bool operator>=(cmp_cat::UnspecifiedParam, PartialOrdering rhs) noexcept
    { return rhs.m_value <= 0; }

    [[nodiscard]] friend constexpr PartialOrdering operator<=>(PartialOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs; }

    [[nodiscard]] friend constexpr PartialOrdering operator<=>(cmp_cat::UnspecifiedParam, PartialOrdering rhs) noexcept
    {
      /* if rhs.m_value is 1 or -1 */
      if (rhs.m_value & 1)
	return PartialOrdering(cmp_cat::Ordered(-rhs.m_value));
      return rhs;
    }

  };

  class WeakOrdering {

  private:

    cmp_cat::Type m_value;

    constexpr WeakOrdering(cmp_cat::Ordered value)
      : m_value(static_cast<cmp_cat::Type>(value))
    { }

    friend class StrongOrdering;

  public:

    static const WeakOrdering less;
    static const WeakOrdering equivalent;
    static const WeakOrdering greater;

    [[nodiscard]] friend constexpr bool operator==(WeakOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == 0; }
    [[nodiscard]] friend constexpr bool operator==(WeakOrdering lhs, WeakOrdering rhs) noexcept = default;

    [[nodiscard]] friend constexpr bool operator<(WeakOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == -1; }
    [[nodiscard]] friend constexpr bool operator<(cmp_cat::UnspecifiedParam, WeakOrdering rhs) noexcept
    { return rhs.m_value == 1; }

    [[nodiscard]] friend constexpr bool operator>(WeakOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == 1; }
    [[nodiscard]] friend constexpr bool operator>(cmp_cat::UnspecifiedParam, WeakOrdering rhs) noexcept
    { return rhs.m_value == -1; }

    [[nodiscard]] friend constexpr bool operator<=(WeakOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value <= 0; }
    [[nodiscard]] friend constexpr bool operator<=(cmp_cat::UnspecifiedParam, WeakOrdering rhs) noexcept
    { return rhs.m_value >= 0; }

    [[nodiscard]] friend constexpr bool operator>=(WeakOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value >= 0; }
    [[nodiscard]] friend constexpr bool operator>=(cmp_cat::UnspecifiedParam, WeakOrdering rhs) noexcept
    { return rhs.m_value <= 0; }

    [[nodiscard]] friend constexpr WeakOrdering operator<=>(WeakOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs; }

    [[nodiscard]] friend constexpr WeakOrdering operator<=>(cmp_cat::UnspecifiedParam, WeakOrdering rhs) noexcept
    {
      /* if rhs.m_value is 1 or -1 */
      if (rhs.m_value & 1)
	return WeakOrdering(cmp_cat::Ordered(-rhs.m_value));
      return rhs;
    }

    constexpr operator PartialOrdering() const noexcept
    { return PartialOrdering(cmp_cat::Ordered(m_value)); }

  };

  class StrongOrdering {

  private:

    cmp_cat::Type m_value;

    constexpr StrongOrdering(cmp_cat::Ordered value)
      : m_value(static_cast<cmp_cat::Type>(value))
    { }

  public:

    static const StrongOrdering less;
    static const StrongOrdering equivalent;
    static const StrongOrdering equal;
    static const StrongOrdering greater;

    [[nodiscard]] friend constexpr bool operator==(StrongOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == 0; }
    [[nodiscard]] friend constexpr bool operator==(StrongOrdering lhs, StrongOrdering rhs) noexcept = default;

    [[nodiscard]] friend constexpr bool operator<(StrongOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == -1; }
    [[nodiscard]] friend constexpr bool operator<(cmp_cat::UnspecifiedParam, StrongOrdering rhs) noexcept
    { return rhs.m_value == 1; }

    [[nodiscard]] friend constexpr bool operator>(StrongOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value == 1; }
    [[nodiscard]] friend constexpr bool operator>(cmp_cat::UnspecifiedParam, StrongOrdering rhs) noexcept
    { return rhs.m_value == -1; }

    [[nodiscard]] friend constexpr bool operator<=(StrongOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value <= 0; }
    [[nodiscard]] friend constexpr bool operator<=(cmp_cat::UnspecifiedParam, StrongOrdering rhs) noexcept
    { return rhs.m_value >= 0; }

    [[nodiscard]] friend constexpr bool operator>=(StrongOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs.m_value >= 0; }
    [[nodiscard]] friend constexpr bool operator>=(cmp_cat::UnspecifiedParam, StrongOrdering rhs) noexcept
    { return rhs.m_value <= 0; }

    [[nodiscard]] friend constexpr WeakOrdering operator<=>(StrongOrdering lhs, cmp_cat::UnspecifiedParam) noexcept
    { return lhs; }

    [[nodiscard]] friend constexpr WeakOrdering operator<=>(cmp_cat::UnspecifiedParam, StrongOrdering rhs) noexcept
    {
      /* if rhs.m_value is 1 or -1 */
      if (rhs.m_value & 1)
	return WeakOrdering(cmp_cat::Ordered(-rhs.m_value));
      return rhs;
    }

    constexpr operator PartialOrdering() const noexcept
    { return PartialOrdering(cmp_cat::Ordered(m_value)); }

    constexpr operator WeakOrdering() const noexcept
    { return WeakOrdering(cmp_cat::Ordered(m_value)); }

  };

  namespace detail {
    template<uint32_t> struct CommonCmpCat { using Type = void; };
    template<> struct CommonCmpCat<0U> { using Type = StrongOrdering; };
    template<> struct CommonCmpCat<2U> { using Type = PartialOrdering; };
    template<> struct CommonCmpCat<4U> { using Type = WeakOrdering; };
    template<> struct CommonCmpCat<6U> { using Type = PartialOrdering; };
  }

  template<typename... Types>
  struct CommonComparsionCategory : detail::CommonCmpCat<(0U | ... | (
      is_same_v<Types, StrongOrdering> ? 0U :
      is_same_v<Types, WeakOrdering> ? 4U :
      is_same_v<Types, PartialOrdering> ? 2U : 1U))> { };

  template<typename... Types>
  using CommonComparsionCategory_T = typename CommonComparsionCategory<Types...>::Type;

  template<typename T, typename U = T>
  using CompareThreeWayResult_T = decltype(
    declval<const RemoveReference_T<T>&>() <=>
    declval<const RemoveReference_T<U>&>());

  template<typename T, typename U = T>
  struct CompareThreeWayResult { };

  template<typename T, typename U>
    requires requires { typename CompareThreeWayResult_T<T, U>; }
  struct CompareThreeWayResult<T, U> {
    using Type = CompareThreeWayResult_T<T, U>;
  };

  template<typename T, typename Cat>
  concept __CompareAs = SameAs<CommonComparsionCategory_T<T, Cat>, Cat>;

  template<typename T, typename Cat = PartialOrdering>
  concept ThreeWayComparable = __WeaklyEqualityComparableWith<T, T> &&
    __PartiallyOrderedWith<T, T> && requires(const RemoveReference_T<T> &a, const RemoveReference_T<T> &b) {
      { a <=> b } -> __CompareAs<Cat>;
    };

  template<typename T, typename U, typename Cat = PartialOrdering>
  concept ThreeWayComparableWith = ThreeWayComparable<T, Cat> &&
    ThreeWayComparable<U, Cat> &&
    CommonReferenceWith<const RemoveReference_T<T>&, const RemoveReference_T<U>&> &&
    ThreeWayComparable<CommonReference_T<const RemoveReference_T<T>&, const RemoveReference_T<U>&>, Cat> &&
    __WeaklyEqualityComparableWith<T, U> &&
    __PartiallyOrderedWith<T, U> &&
    requires(const RemoveReference_T<T> &t, const RemoveReference_T<U> &u) {
      { t <=> u } -> __CompareAs<Cat>;
      { u <=> t } -> __CompareAs<Cat>;
    };

  template<typename Type1, typename Type2>
  constexpr auto synth_three_way(const Type1 &lhs, const Type2 &rhs);

  template<typename Type>
  using SynthThreeWayResult = decltype(synth_three_way(declval<Type&>(), declval<Type&>()));

} // namespace me
// Implementations:

/* -------------------------- */
/* class me::PartialOrdering */
/* -------------------------- */
constexpr inline me::PartialOrdering me::PartialOrdering::less(cmp_cat::Ordered::LESS);
constexpr inline me::PartialOrdering me::PartialOrdering::equivalent(cmp_cat::Ordered::EQUIVALENT);
constexpr inline me::PartialOrdering me::PartialOrdering::greater(cmp_cat::Ordered::GREATER);
constexpr inline me::PartialOrdering me::PartialOrdering::unordered(cmp_cat::Unordered::UNORDERED);
/* end class me::PartialOrdering */

/* ---------------------- */
/* class me::WeakOrdering */
/* ---------------------- */
constexpr inline me::WeakOrdering me::WeakOrdering::less(cmp_cat::Ordered::LESS);
constexpr inline me::WeakOrdering me::WeakOrdering::equivalent(cmp_cat::Ordered::EQUIVALENT);
constexpr inline me::WeakOrdering me::WeakOrdering::greater(cmp_cat::Ordered::GREATER);
/* end class me::WeakOrdering */

/* ------------------------ */
/* class me::StrongOrdering */
/* ------------------------ */
constexpr inline me::StrongOrdering me::StrongOrdering::less(cmp_cat::Ordered::LESS);
constexpr inline me::StrongOrdering me::StrongOrdering::equivalent(cmp_cat::Ordered::EQUIVALENT);
constexpr inline me::StrongOrdering me::StrongOrdering::equal(cmp_cat::Ordered::EQUIVALENT);
constexpr inline me::StrongOrdering me::StrongOrdering::greater(cmp_cat::Ordered::GREATER);
/* end class me::StrongOrdering */

template<typename Type1, typename Type2>
constexpr auto
  me::synth_three_way(const Type1 &lhs, const Type2 &rhs)
{
  if constexpr (ThreeWayComparableWith<Type1, Type2>)
    return lhs <=> rhs;
  if (lhs < rhs)
    return WeakOrdering::less;
  if (lhs > rhs)
    return WeakOrdering::greater;
  else
    return WeakOrdering::equivalent;
}

#endif // LIBME_COMPARE_HPP
