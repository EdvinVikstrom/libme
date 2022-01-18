#ifndef LIBME_ITERATOR_HPP
  #define LIBME_ITERATOR_HPP

#include "libme/bits/iterator/Access.hpp"

namespace me {

} // namespace me

//
//
//  namespace ranges {
//
//    namespace __cpos {
//
//      struct __IterMove {
//        template<typename T>
//        constexpr decltype(auto) operator()(T &&t)
//          requires is_class<typename remove_cvref<T>::type>::value || is_enum<typename remove_cvref<T>::type>::value
//        {
//          iter_move(forward<T>(t));
//        }
//
//        template<typename T>
//        constexpr decltype(auto) operator()(T &&t)
//          requires is_lvalue_reference<decltype(*forward<T>(t))>::value
//        {
//          move(*forward<T>(t));
//        }
//
//        template<typename T>
//        constexpr decltype(auto) operator()(T &&t)
//          requires is_rvalue_reference<decltype(*forward<T>(t))>::value
//        {
//          *forward<T>(t);
//        }
//      };
//
//      struct __IterSwap {
//      };
//
//    }
//
//    inline namespace __iter_func {
//      inline constexpr __cpos::__IterMove iter_move = { };
//      inline constexpr __cpos::__IterSwap iter_swap = { };
//    }
//
//  }
//
//  template<typename I>
//  struct IncrementableTraits { };
//
//  template<typename T> requires is_object<T>::value
//  struct IncrementableTraits<T*>;
//
//  template<typename T>
//  struct IncrementableTraits<const T> : IncrementableTraits<T> { };
//
//  template<typename T> requires requires { typename T::DifferenceType; }
//  struct IncrementableTraits<T>;
//
//  template<typename T> requires (!requires { typename T::DifferenceType; }) && requires(const T &a, const T &b) { { a - b } -> Integral; }
//  struct IncrementableTraits<T>;
//
//  template<typename I>
//  struct IndirectlyReadableTraits { };
//
//  template<typename T>
//  struct IndirectlyReadableTraits<T*>;
//
//  template<typename I> requires is_array<I>::value
//  struct IndirectlyReadableTraits<I>;
//
//  template<typename T>
//  struct IndirectlyReadableTraits<const T> : IndirectlyReadableTraits<T> { };
//
//  template<helper::__HasValueType T>
//  struct IndirectlyReadableTraits<T>;
//
//  template<helper::__HasElementType T>
//  struct IndirectlyReadableTraits<T>;
//
//  template<helper::__HasValueType T> requires helper::__HasElementType<T>
//  struct IndirectlyReadableTraits<T> { };
//
//  template<helper::__HasValueType T> requires helper::__HasElementType<T> &&
//    SameAs<typename remove_cv<typename T::ElementType>::type, typename remove_cv<typename T::ValueType>::type>
//  struct IndirectlyReadableTraits<T>;
//
//  template<typename Iter>
//  struct IteratorTraits;
//
//  template<typename T>
//  struct IteratorTraits<T*>;
//
//  struct InputIteratorTag { };
//
//  struct OutputIteratorTag { };
//
//  struct ForwardIteratorTag : public InputIteratorTag { };
//
//  struct BidirectionalIteratorTag : public ForwardIteratorTag { };
//
//  struct RandomAccessIteratorTag : public BidirectionalIteratorTag { };
//
//  struct ContiguousIteratorTag : public RandomAccessIteratorTag { };
//
//  namespace helper {
//
//    template<typename>
//    struct __PointerVoid {
//      using type = void;
//    };
//
//    template<__HasPointer T>
//    struct __PointerVoid<T> {
//      using type = typename T::Pointer;
//    };
//
//    template<typename T>
//    struct __ReferenceOther {
//      using type = iter_reference_t<T>;
//    };
//
//    template<__HasReference T>
//    struct __ReferenceOther<T> {
//      using type = typename T::Reference;
//    };
//
//    template<typename>
//    struct __PointerOperatorVoid {
//      using type = void;
//    };
//
//    template<__HasPointer T>
//    struct __PointerOperatorVoid<T> {
//      using type = typename T::Pointer;
//    };
//
//    template<__HasOperator T>
//    struct __PointerOperatorVoid<T> {
//      using type = decltype(declval<T&>().operator->());
//    };
//
//    template<typename>
//    struct __IterCategoryRaitBitFitIit {
//      using type = InputIteratorTag;
//    };
//
//    template<__HasIteratorCategory T>
//    struct __IterCategoryRaitBitFitIit<T> {
//      using type = typename T::IteratorCategory;
//    };
//    
//    template<__LegacyRandomAccessIterator T>
//    struct __IterCategoryRaitBitFitIit<T> {
//      using type = RandomAccessIteratorTag;
//    };
//
//    template<__LegacyBidirectionalIterator T>
//    struct __IterCategoryRaitBitFitIit<T> {
//      using type = BidirectionalIteratorTag;
//    };
//
//    template<__LegacyForwardIterator T>
//    struct __IterCategoryRaitBitFitIit<T> {
//      using type = ForwardIteratorTag;
//    };
//
//    template<typename>
//    struct __RaitBit {
//      using type = BidirectionalIteratorTag;
//    };
//
//    template<RandomAccessIterator T>
//    struct __RaitBit<T> {
//      using type = RandomAccessIteratorTag;
//    };
//
//    template<typename T>
//    struct __RaitIteratorCategory {
//      using type = typename T::IteratorCategory;
//    };
//
//    template<typename T>
//      requires DerivedFrom<typename IteratorTraits<T>::IteratorCategory, RandomAccessIteratorTag>
//    struct __RaitIteratorCategory<T> {
//      using type = RandomAccessIteratorTag;
//    };
//
//  }
//
//  /* -------------------------------- */
//  /*             Classes              */
//  /* -------------------------------- */
//
//  template<typename Iter>
//  struct IteratorTraits {
//    using DifferenceType = typename Iter::DifferenceType;
//    using ValueType = typename Iter::ValueType;
//    using Pointer = typename helper::__PointerVoid<Iter>::type;
//    using Reference = typename Iter::Reference;
//    using IteratorCategory = typename Iter::IteratorCategory;
//  };
//
//  template<__LegacyInputIterator Iter>
//  struct IteratorTraits<Iter> {
//    using DifferenceType = typename IncrementableTraits<Iter>::DifferenceType;
//    using ValueType = typename IndirectlyReadableTraits<Iter>::ValueType;
//    using Pointer = typename helper::__PointerOperatorVoid<Iter>::type;
//    using Reference = typename helper::__ReferenceOther<Iter>::type;
//    using IteratorCategory = typename helper::__IterCategoryRaitBitFitIit<Iter>::type;
//  };
//
//  template<__LegacyIterator Iter>
//  struct IteratorTraits<Iter> {
//    using DifferenceType = typename IncrementableTraits<Iter>::DifferenceType;
//    using ValueType = void;
//    using Pointer = void;
//    using Reference = void;
//    using IteratorCategory = OutputIteratorTag;
//  };
//
//  template<typename Type> requires is_object<Type>::value
//  struct IteratorTraits<Type*> {
//    using DifferenceType = ptrdiff_t;
//    using ValueType = typename remove_cv<Type>::type;
//    using Pointer = Type*;
//    using Reference = Type&;
//    using IteratorCategory = RandomAccessIteratorTag;
//    using IteratorConcept = ContiguousIteratorTag;
//  };
//
//  template<typename Iter>
//  class ReverseIterator {
//
//  public:
//
//    using IteratorType = Iter;
//    using IteratorConcept = typename helper::__RaitBit<Iter>::type;
//    using IteratorCategory = typename helper::__RaitIteratorCategory<Iter>::type;
//    using ValueType = iter_value_t<Iter>;
//    using DifferenceType = iter_difference_t<Iter>;
//    using Pointer = typename IteratorTraits<Iter>::Pointer;
//    using Reference = iter_reference_t<Iter>;
//
//  protected:
//
//    IteratorType m_current;
//
//  public:
//
//    constexpr ReverseIterator();
//    constexpr explicit ReverseIterator(IteratorType iter);
//    template<typename U> constexpr ReverseIterator(const ReverseIterator<U> &other)
//      requires (!is_same<Iter, U>::value) && ConvertibleTo<const U&, Iter>;
//
//    template<typename U> constexpr ReverseIterator& operator=(const ReverseIterator<U> &other)
//      requires (!is_same<Iter, U>::value) && ConvertibleTo<const U&, Iter> && AssignableFrom<Iter&, const U&>;
//
//    constexpr IteratorType base() const;
//
//    constexpr Reference operator*() const;
//    constexpr Pointer operator->() const
//      requires (is_pointer<Iter>::value || requires(const Iter i) { i.operator->(); });
//
//    constexpr /*unspecified*/ auto operator[](DifferenceType n) const;
//
//    constexpr ReverseIterator& operator++();
//    constexpr ReverseIterator& operator--();
//    constexpr ReverseIterator operator++(int);
//    constexpr ReverseIterator operator--(int);
//    constexpr ReverseIterator operator+(DifferenceType n) const;
//    constexpr ReverseIterator operator-(DifferenceType n) const;
//    constexpr ReverseIterator& operator+=(DifferenceType n);
//    constexpr ReverseIterator& operator-=(DifferenceType n);
//
//    friend constexpr iter_rvalue_reference_t<Iter> iter_move(const ReverseIterator &iter)
//      noexcept(
//	is_nothrow_copy_constructible<Iter>::value &&
//	noexcept(ranges::iter_move(--declval<Iter&>())))
//    {
//      auto tmp = iter.base();
//      return ranges::iter_move(--tmp);
//    }
//
//    template<IndirectlySwappable<Iter> Iter2>
//    friend constexpr void iter_swap(const ReverseIterator &iter1, const ReverseIterator<Iter2> &iter2)
//      noexcept(
//	is_nothrow_copy_constructible<Iter>::value &&
//	is_nothrow_copy_constructible<Iter2>::value &&
//	noexcept(ranges::iter_swap(--declval<Iter&>(), --declval<Iter2&>())))
//    {
//      auto tmp1 = iter1.base();
//      auto tmp2 = iter2.base();
//      ranges::iter_swap(--tmp1, --tmp2);
//    }
//    
//  };
//
//  template<typename Iter1, typename Iter2>
//  constexpr bool operator==(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs);
//
//  template<typename Iter1, typename Iter2>
//  constexpr bool operator!=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs);
//
//  template<typename Iter1, typename Iter2>
//  constexpr bool operator<(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs);
//
//  template<typename Iter1, typename Iter2>
//  constexpr bool operator<=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs);
//
//  template<typename Iter1, typename Iter2>
//  constexpr bool operator>(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs);
//
//  template<typename Iter1, typename Iter2>
//  constexpr bool operator>=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs);
//
//  template<typename Iter1, typename Iter2>
//  constexpr compare_three_way_result_t<Iter1, Iter2> operator<=>(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs);
//
//  template<typename Iter>
//  constexpr ReverseIterator<Iter> operator+(typename ReverseIterator<Iter>::DifferenceType n, const ReverseIterator<Iter> &iter);
//
//  template<typename Iter1, typename Iter2>
//  constexpr auto operator-(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//    -> decltype(rhs.base() - lhs.base());
//
//  template<typename Iter>
//  constexpr ReverseIterator<Iter> make_reverse_iterator(Iter iter);
//
//
//  /* -------------------------------- */
//  /*            Functions             */
//  /* -------------------------------- */
//
//  // make_reverse_iterator
//  // make_move_iterator
//  // front_inserter
//  // back_inserter
//  // inserter
//
//  // operators...
//
//  template<typename InputIt, typename Distance>
//  constexpr void advance(InputIt &it, Distance n);
//
//  // distance
//  // next
//
//  template<typename BidirIt>
//  constexpr BidirIt prev(BidirIt it, typename IteratorTraits<BidirIt>::DifferenceType n = 1);
//
//  // ranges::advance
//  // ranges::distance
//  // ranges::next
//  // ranges::prev
//
//  // begin
//  // cbegin
//  // end
//  // cend
//  // rbegin
//  // crbegin
//  // rend
//  // crend
//  // size
//  // ssize
//  // empty
//  // data
//
//} // namespace me
//
///* ------------------------- */
///* class me::ReverseIterator */
///* ------------------------- */
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>::ReverseIterator()
//{
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>::ReverseIterator(IteratorType iter)
//  : m_current(iter)
//{
//}
//
//template<typename Iter>
//template<typename U>
//constexpr me::ReverseIterator<Iter>::ReverseIterator(const ReverseIterator<U> &other)
//  requires (!is_same<Iter, U>::value) && ConvertibleTo<const U&, Iter>
//  : m_current(other)
//{
//}
//
//template<typename Iter>
//template<typename U>
//constexpr me::ReverseIterator<Iter>&
//  me::ReverseIterator<Iter>::operator=(const ReverseIterator<U> &other)
//  requires (!is_same<Iter, U>::value) && ConvertibleTo<const U&, Iter> && AssignableFrom<Iter&, const U&>
//{
//  m_current = other.base();
//  return *this;
//}
//
//template<typename Iter>
//constexpr typename me::ReverseIterator<Iter>::IteratorType
//  me::ReverseIterator<Iter>::base() const
//{
//  return m_current;
//}
//
//template<typename Iter>
//constexpr typename me::ReverseIterator<Iter>::Reference
//  me::ReverseIterator<Iter>::operator*() const
//{
//  Iter tmp = m_current;
//  return *--tmp;
//}
//
//template<typename Iter>
//constexpr typename me::ReverseIterator<Iter>::Pointer
//  me::ReverseIterator<Iter>::operator->() const
//  requires (is_pointer<Iter>::value || requires(const Iter i) { i.operator->(); })
//{
//  if constexpr (is_pointer<Iter>::value)
//    return m_current - 1;
//  else
//    prev(m_current).operator->();
//}
//
//template<typename Iter>
//constexpr auto
//  me::ReverseIterator<Iter>::operator[](DifferenceType n) const
//{
//  return base()[-n - 1];
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>&
//  me::ReverseIterator<Iter>::operator++()
//{
//  m_current--;
//  return *this;
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>&
//  me::ReverseIterator<Iter>::operator--()
//{
//  m_current++;
//  return *this;
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>
//  me::ReverseIterator<Iter>::operator++(int)
//{
//  ReverseIterator old = *this;
//  m_current--;
//  return old;
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>
//  me::ReverseIterator<Iter>::operator--(int)
//{
//  ReverseIterator old = *this;
//  m_current++;
//  return old;
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>
//  me::ReverseIterator<Iter>::operator+(DifferenceType n) const
//{
//  ReverseIterator iter = *this;
//  iter += n;
//  return iter;
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>
//  me::ReverseIterator<Iter>::operator-(DifferenceType n) const
//{
//  ReverseIterator iter = *this;
//  iter -= n;
//  return iter;
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>&
//  me::ReverseIterator<Iter>::operator+=(DifferenceType n)
//{
//  m_current -= n;
//  return *this;
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>&
//  me::ReverseIterator<Iter>::operator-=(DifferenceType n)
//{
//  m_current += n;
//  return *this;
//}
///* end class me::ReverseIterator */
//
///* ----------------------------- */
///* me::ReverseIterator functions */
///* ----------------------------- */
//template<typename Iter1, typename Iter2>
//constexpr bool
//  me::operator==(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//{
//  return lhs.base() == rhs.base();
//}
//
//template<typename Iter1, typename Iter2>
//constexpr bool
//  me::operator!=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//{
//  return lhs.base() != rhs.base();
//}
//
//template<typename Iter1, typename Iter2>
//constexpr bool
//  me::operator<(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//{
//  return lhs.base() < rhs.base();
//}
//
//template<typename Iter1, typename Iter2>
//constexpr bool
//  me::operator<=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//{
//  return lhs.base() <= rhs.base();
//}
//
//template<typename Iter1, typename Iter2>
//constexpr bool
//  me::operator>(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//{
//  return lhs.base() > rhs.base();
//}
//
//template<typename Iter1, typename Iter2>
//constexpr bool
//  me::operator>=(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//{
//  return lhs.base() >= rhs.base();
//}
//
//template<typename Iter1, typename Iter2>
//constexpr me::compare_three_way_result_t<Iter1, Iter2>
//  me::operator<=>(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//{
//  return lhs.base() <=> rhs.base();
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>
//  me::operator+(typename ReverseIterator<Iter>::DifferenceType n, const ReverseIterator<Iter> &iter)
//{
//  return ReverseIterator<Iter>(iter.base() - n);
//}
//
//template<typename Iter1, typename Iter2>
//constexpr auto
//  me::operator-(const ReverseIterator<Iter1> &lhs, const ReverseIterator<Iter2> &rhs)
//  -> decltype(rhs.base() - lhs.base())
//{
//  return rhs.base() - lhs.base();
//}
//
//template<typename Iter>
//constexpr me::ReverseIterator<Iter>
//  me::make_reverse_iterator(Iter iter)
//{
//  return ReverseIterator<Iter>(iter);
//}
///* end me::ReverseIterator functions */
//
///* --------------- */
///* Other functions */
///* --------------- */
//template<typename InputIt, typename Distance>
//constexpr void
//  me::advance(InputIt &it, Distance n)
//{
//  using Category = typename IteratorTraits<InputIt>::IteratorCategory;
//  static_assert(is_base_of<InputIteratorTag, Category>::value);
//
//  auto dist = typename IteratorTraits<InputIt>::DifferenceType(n);
//  if constexpr (is_base_of<RandomAccessIteratorTag, Category>::value)
//  {
//    it += dist;
//  }else
//  {
//    while (dist > 0)
//    {
//      --dist;
//      ++it;
//    }
//
//    if constexpr (is_base_of<BidirectionalIteratorTag, Category>::value)
//    {
//      while (dist < 0)
//      {
//	++dist;
//	--it;
//      }
//    }
//  }
//}
//
//template<typename BidirIt>
//constexpr BidirIt
//  me::prev(BidirIt it, typename IteratorTraits<BidirIt>::DifferenceType n)
//{
//  advance(it, -n);
//  return it;
//}
///* end Other functions */

#endif // LIBME_ITERATOR_HPP
