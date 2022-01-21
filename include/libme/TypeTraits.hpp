#ifndef LIBME_TYPE_TRAITS_HPP
  #define LIBME_TYPE_TRAITS_HPP

#include "Type.hpp"

#include <type_traits> // Temporary

namespace me {

  template<typename T, T V> struct IntegralConstant;

  template<bool B>
    using BoolConstant = IntegralConstant<bool, B>;
  using TrueType = BoolConstant<true>;
  using FalseType = BoolConstant<false>;

  // primary type categories

  template<typename T> struct IsVoid;
  template<typename T> struct IsNullPointer;
  template<typename T> struct IsIntegral;
  template<typename T> struct IsFloatingPoint;
  template<typename T> struct IsArray;
  template<typename T> struct IsPointer;
  template<typename T> struct IsLValueReference;
  template<typename T> struct IsRValueReference;
  template<typename T> struct IsMemberObjectPointer;
  template<typename T> struct IsMemberFunctionPointer;
  template<typename T> struct IsEnum;
  template<typename T> struct IsUnion;
  template<typename T> struct IsClass;
  template<typename T> struct IsFunction;

  // composite type categories

  template<typename T> struct IsReference;
  template<typename T> struct IsArithmetic;
  template<typename T> struct IsFundamental;
  template<typename T> struct IsObject;
  template<typename T> struct IsScalar;
  template<typename T> struct IsCompound;
  template<typename T> struct IsMemberPointer;

  // type properties

  template<typename T> struct IsConst;
  template<typename T> struct IsVolatile;
  template<typename T> struct IsTrivial;
  template<typename T> struct IsTriviallyCopyable;
  template<typename T> struct IsStandardLayout;
  template<typename T> struct IsEmpty;
  template<typename T> struct IsPolymorphic;
  template<typename T> struct IsAbstract;
  template<typename T> struct IsFinal;
  template<typename T> struct IsAggregate;
  template<typename T> struct IsSigned;
  template<typename T> struct IsUnsigned;
  template<typename T> struct IsBoundedArray;
  template<typename T> struct IsUnboundedArray;
  template<typename T> struct IsScopedEnum;

  template<typename T, typename... Args> struct IsConstructible;
  template<typename T> struct IsDefaultConstructible;
  template<typename T> struct IsCopyConstructible;
  template<typename T> struct IsMoveConstructible;

  template<typename T, typename U> struct IsAssignable;
  template<typename T> struct IsCopyAssignable;
  template<typename T> struct IsMoveAssignable;

  template<typename T, typename U> struct IsSwappableWith;
  template<typename T> struct IsSwappable;

  template<typename T> struct IsDestructible;

  template<typename T, typename... Args> struct IsTriviallyConstructible;
  template<typename T> struct IsTriviallyDefaultConstructible;
  template<typename T> struct IsTriviallyCopyConstructible;
  template<typename T> struct IsTriviallyMoveConstructible;

  template<typename T, typename U> struct IsTriviallyAssignable;
  template<typename T> struct IsTriviallyCopyAssignable;
  template<typename T> struct IsTriviallyMoveAssignable;
  template<typename T> struct IsTriviallyDestructible;

  template<typename T, typename... Args> struct IsNothrowConstructible;
  template<typename T> struct IsNothrowDefaultConstructible;
  template<typename T> struct IsNothrowCopyConstructible;
  template<typename T> struct IsNothrowMoveConstructible;

  template<typename T, typename U> struct IsNothrowAssignable;
  template<typename T> struct IsNothrowCopyAssignable;
  template<typename T> struct IsNothrowMoveAssignable;

  template<typename T, typename U> struct IsNothrowSwappableWith;
  template<typename T> struct IsNothrowSwappable;

  template<typename T> struct IsNothrowDestructible;

  template<typename T> struct HasVirtualDestructor;

  template<typename T> struct HasUniqueObjectRepresentations;

  // type properties queries

  template<typename T> struct AlignmentOf;
  template<typename T> struct Rank;
  template<typename T, unsigned N = 0> struct Extent;

  // type relations

  template<typename T, typename U> struct IsSame;
  template<typename Base, typename Derived> struct IsBaseOf;
  template<typename From, typename To> struct IsConvertible;
  template<typename From, typename To> struct IsNothrowConvertible;
  template<typename T, typename U> struct IsLayoutCompatible;
  template<typename Base, typename Derived> struct IsPointerInterconvertibleBaseOf;

  template<typename Fn, typename... ArgTypes> struct IsInvocable;
  template<typename R, typename Fn, typename... ArgTypes> struct IsInvocableR;
  template<typename Fn, typename... ArgTypes> struct IsNothrowInvocable;
  template<typename R, typename Fn, typename... ArgTypes> struct IsNothrowInvocableR;

  // const-volatile modifcations

  template<typename T> struct RemoveConst;
  template<typename T> struct RemoveVolatile;
  template<typename T> struct RemoveCV;
  template<typename T> struct AddConst;
  template<typename T> struct AddVolatile;
  template<typename T> struct AddCV;

  template<typename T> using RemoveConst_T = typename RemoveConst<T>::Type;
  template<typename T> using RemoveVolatile_T = typename RemoveVolatile<T>::Type;
  template<typename T> using RemoveCV_T = typename RemoveCV<T>::Type;
  template<typename T> using AddConst_T = typename AddConst<T>::Type;
  template<typename T> using AddVolatile_T = typename AddVolatile<T>::Type;
  template<typename T> using AddCV_T = typename AddCV<T>::Type;

  // reference modifcations

  template<typename T> struct RemoveReference;
  template<typename T> struct AddLValueReference;
  template<typename T> struct AddRValueReference;

  template<typename T> using RemoveReference_T = typename RemoveReference<T>::Type;
  template<typename T> using AddLValueReference_T = typename AddLValueReference<T>::Type;
  template<typename T> using AddRValueReference_T = typename AddRValueReference<T>::Type;

  // sign modifcations

  template<typename T> struct MakeSigned;
  template<typename T> struct MakeUnsigned;

  template<typename T> using MakeSigned_T = typename MakeSigned<T>::Type;
  template<typename T> using MakeUnsigned_T = typename MakeUnsigned<T>::Type;

  // array mmodifcations

  template<typename T> struct RemoveExtent;
  template<typename T> struct RemoveAllExtents;

  template<typename T> using RemoveExtent_T = typename RemoveExtent<T>::Type;
  template<typename T> using RemoveAllExtents_T = typename RemoveAllExtents<T>::Type;

  // pointer modifcations

  template<typename T> struct RemovePointer;
  template<typename T> struct AddPointer;

  template<typename T> using RemovePointer_T = typename RemovePointer<T>::Type;
  template<typename T> using AddPointer_T = typename AddPointer<T>::Type;

  // other transformations

  constexpr inline size_t __DefaultAlignment = alignof(size_t); // TODO

  template<typename T> struct TypeIdentity;
  template<size_t Len, size_t Align = __DefaultAlignment> struct AlignedStorage;
  template<size_t Len, typename... Types> struct AlignedUnion;
  template<typename T> struct RemoveCVRef;
  template<typename T> struct Decay;
  template<bool, typename T = void> struct EnableIf;
  template<bool, typename T, typename F> struct Conditional;
  template<typename... Args> struct CommonType;
  template<typename T, typename U, template<typename> typename TQual, template<typename> typename UQual>
    struct BasicCommonReference { };
  template<typename... T> struct CommonReference;
  template<typename T> struct UnderlyingType;
  template<typename Fn, typename... ArgTypes> struct InvokeResult;
  template<typename T> struct UnwrapReference;
  template<typename T> struct UnwrapRefDecay;

  template<typename T> using TypeIdentity_T = typename TypeIdentity<T>::Type;
  template<size_t Len, size_t Align = __DefaultAlignment> using AlignedStorage_T = typename AlignedStorage<Len, Align>::Type;
  template<size_t Len, typename... Types> using AlignedUnion_T = typename AlignedUnion<Len, Types...>::Type;
  template<typename T> using RemoveCVRef_T = typename RemoveCVRef<T>::Type;
  template<typename T> using Decay_T = typename Decay<T>::Type;
  template<bool B, typename T = void> using EnableIf_T = typename EnableIf<B, T>::Type;
  template<bool B, typename T, typename F> using Conditional_T = typename Conditional<B, T, F>::Type;
  template<typename... Args> using CommonType_T = typename CommonType<Args...>::Type;
  template<typename... T> using CommonReference_T = typename CommonReference<T...>::Type;
  template<typename T> using UnderlyingType_T = typename UnderlyingType<T>::Type;
  template<typename Fn, typename... ArgTypes> using InvokeResult_T = typename InvokeResult<Fn, ArgTypes...>::Type;
  template<typename T> using UnwrapReference_T = typename UnwrapReference<T>::Type;
  template<typename T> using UnwrapRefDecay_T = typename UnwrapRefDecay<T>::Type;

  // logical operator traits

  template<typename... B> struct Conjunction;
  template<typename... B> struct Disjunction;
  template<typename B> struct Negation;

  // primary type categories

  template<typename T> inline constexpr bool is_void_v = IsVoid<T>::value;
  template<typename T> inline constexpr bool is_null_pointer_v = IsNullPointer<T>::value;
  template<typename T> inline constexpr bool is_integral_v = IsIntegral<T>::value;
  template<typename T> inline constexpr bool is_floating_point_v = IsFloatingPoint<T>::value;
  template<typename T> inline constexpr bool is_array_v = IsArray<T>::value;
  template<typename T> inline constexpr bool is_pointer_v = IsPointer<T>::value;
  template<typename T> inline constexpr bool is_lvalue_reference_v = IsLValueReference<T>::value;
  template<typename T> inline constexpr bool is_rvalue_reference_v = IsRValueReference<T>::value;
  template<typename T> inline constexpr bool is_member_object_pointer_v = IsMemberObjectPointer<T>::value;
  template<typename T> inline constexpr bool is_member_function_pointer_v = IsMemberFunctionPointer<T>::value;
  template<typename T> inline constexpr bool is_enum_v = IsEnum<T>::value;
  template<typename T> inline constexpr bool is_union_v = IsUnion<T>::value;
  template<typename T> inline constexpr bool is_class_v = IsClass<T>::value;
  template<typename T> inline constexpr bool is_function_v = IsFunction<T>::value;

  // composite type categories

  template<typename T> inline constexpr bool is_reference_v = IsReference<T>::value;
  template<typename T> inline constexpr bool is_arithmetic_v = IsArithmetic<T>::value;
  template<typename T> inline constexpr bool is_fundamental_v = IsFundamental<T>::value;
  template<typename T> inline constexpr bool is_object_v = IsObject<T>::value;
  template<typename T> inline constexpr bool is_scalar_v = IsScalar<T>::value;
  template<typename T> inline constexpr bool is_compound_v = IsCompound<T>::value;
  template<typename T> inline constexpr bool is_member_pointer_v = IsMemberPointer<T>::value;

  // type properties

  template<typename T> inline constexpr bool is_const_v = IsConst<T>::value;
  template<typename T> inline constexpr bool is_volatile_v = IsVolatile<T>::value;
  template<typename T> inline constexpr bool is_trivial_v = IsTrivial<T>::value;
  template<typename T> inline constexpr bool is_trivially_copyable_v = IsTriviallyCopyable<T>::value;
  template<typename T> inline constexpr bool is_standard_layout_v = IsStandardLayout<T>::value;
  template<typename T> inline constexpr bool is_empty_v = IsEmpty<T>::value;
  template<typename T> inline constexpr bool is_polymorphic_v = IsPolymorphic<T>::value;
  template<typename T> inline constexpr bool is_abstract_v = IsAbstract<T>::value;
  template<typename T> inline constexpr bool is_final_v = IsFinal<T>::value;
  template<typename T> inline constexpr bool is_aggregate_v = IsAggregate<T>::value;
  template<typename T> inline constexpr bool is_signed_v = IsSigned<T>::value;
  template<typename T> inline constexpr bool is_unsigned_v = IsUnsigned<T>::value;
  template<typename T> inline constexpr bool is_bounded_array_v = IsBoundedArray<T>::value;
  template<typename T> inline constexpr bool is_unbounded_array_v = IsUnboundedArray<T>::value;
  template<typename T> inline constexpr bool is_scoped_enum_v = IsScopedEnum<T>::value;
  template<typename T, typename... Args> inline constexpr bool is_constructible_v = IsConstructible<T, Args...>::value;
  template<typename T> inline constexpr bool is_default_constructible_v = IsDefaultConstructible<T>::value;
  template<typename T> inline constexpr bool is_copy_constructible_v = IsCopyConstructible<T>::value;
  template<typename T> inline constexpr bool is_move_constructible_v = IsMoveConstructible<T>::value;
  template<typename T, typename U> inline constexpr bool is_assignable_v = IsAssignable<T, U>::value;
  template<typename T> inline constexpr bool is_copy_assignable_v = IsCopyAssignable<T>::value;
  template<typename T> inline constexpr bool is_move_assignable_v = IsMoveAssignable<T>::value;
  template<typename T, typename U> inline constexpr bool is_swappable_with_v = IsSwappableWith<T, U>::value;
  template<typename T> inline constexpr bool is_swappable_v = IsSwappable<T>::value;
  template<typename T> inline constexpr bool is_destructible_v = IsDestructible<T>::value;
  template<typename T, typename... Args> inline constexpr bool is_trivially_constructible_v = IsTriviallyConstructible<T, Args...>::value;
  template<typename T> inline constexpr bool is_trivially_default_constructible_v = IsTriviallyDefaultConstructible<T>::value;
  template<typename T> inline constexpr bool is_trivially_copy_constructible_v = IsTriviallyCopyConstructible<T>::value;
  template<typename T> inline constexpr bool is_trivially_move_constructible_v = IsTriviallyMoveConstructible<T>::value;
  template<typename T, typename U> inline constexpr bool is_trivially_assignable_v = IsTriviallyAssignable<T, U>::value;
  template<typename T> inline constexpr bool is_trivially_copy_assignable_v = IsTriviallyCopyAssignable<T>::value;
  template<typename T> inline constexpr bool is_trivially_move_assignable_v = IsTriviallyMoveAssignable<T>::value;
  template<typename T> inline constexpr bool is_trivially_destructible_v = IsTriviallyDestructible<T>::value;
  template<typename T, typename... Args> inline constexpr bool is_nothrow_constructible_v = IsNothrowConstructible<T, Args...>::value;
  template<typename T> inline constexpr bool is_nothrow_default_constructible_v = IsNothrowDefaultConstructible<T>::value;
  template<typename T> inline constexpr bool is_nothrow_copy_constructible_v = IsNothrowCopyConstructible<T>::value;
  template<typename T> inline constexpr bool is_nothrow_move_constructible_v = IsNothrowMoveConstructible<T>::value;
  template<typename T, typename U> inline constexpr bool is_nothrow_assignable_v = IsNothrowAssignable<T, U>::value;
  template<typename T> inline constexpr bool is_nothrow_copy_assignable_v = IsNothrowCopyAssignable<T>::value;
  template<typename T> inline constexpr bool is_nothrow_move_assignable_v = IsNothrowMoveAssignable<T>::value;
  template<typename T, typename U> inline constexpr bool is_nothrow_swappable_with_v = IsNothrowSwappableWith<T, U>::value;
  template<typename T> inline constexpr bool is_nothrow_swappable_v = IsNothrowSwappable<T>::value;
  template<typename T> inline constexpr bool is_nothrow_destructible_v = IsNothrowDestructible<T>::value;
  template<typename T> inline constexpr bool has_virtual_destructor_v = HasVirtualDestructor<T>::value;
  template<typename T> inline constexpr bool has_unique_object_representations_v = HasUniqueObjectRepresentations<T>::value;

  // type properties queries

  template<typename T> inline constexpr size_t alignment_of_v = AlignmentOf<T>::value;
  template<typename T> inline constexpr size_t rank_v = Rank<T>::value;
  template<typename T, unsigned N = 0> inline constexpr size_t extent_v = Extent<T, N>::value;

  // type relations

  template<typename T, typename U> inline constexpr bool is_same_v = IsSame<T, U>::value;
  template<typename Base, typename Derived> inline constexpr bool is_base_of_v = IsBaseOf<Base, Derived>::value;
  template<typename From, typename To> inline constexpr bool is_convertible_v = IsConvertible<From, To>::value;
  template<typename From, typename To> inline constexpr bool is_nothrow_convertible_v = IsNothrowConvertible<From, To>::value;
  template<typename T, typename U> inline constexpr bool is_layout_compatible_v = IsLayoutCompatible<T, U>::value;
  template<typename Base, typename Derived> inline constexpr bool is_pointer_interconvertible_base_of_v = IsPointerInterconvertibleBaseOf<Base, Derived>::value;
  template<typename Fn, typename... ArgTypes> inline constexpr bool is_invocable_v = IsInvocable<Fn, ArgTypes...>::value;
  template<typename R, typename Fn, typename... ArgTypes> inline constexpr bool is_invocable_r_v = IsInvocableR<R, Fn, ArgTypes...>::value;
  template<typename Fn, typename... ArgTypes> inline constexpr bool is_nothrow_invocable_v = IsNothrowInvocable<Fn, ArgTypes...>::value;
  template<typename R, typename Fn, typename... ArgTypes> inline constexpr bool is_nothrow_invocable_r_v = IsNothrowInvocableR<R, Fn, ArgTypes...>::value;

  // logical operator traits

  template<typename... B> inline constexpr bool conjunction_v = Conjunction<B...>::value;
  template<typename... B> inline constexpr bool disjunction_v = Disjunction<B...>::value;
  template<typename B> inline constexpr bool negation_v = Negation<B>::value;

  // member relationships

  template<typename S, typename M> constexpr bool is_pointer_interconvertible_with_class(M S::*m) noexcept;
  template<typename S1, typename S2, typename M1, typename M2> constexpr bool is_corresponding_member(M1 S1::*m1, M2 S2::*m2) noexcept;

  // constant evaluation context

  constexpr bool is_constant_evaluated() noexcept;

  // is valid expression

  template<template<typename...> typename Template, typename... Args, typename = Template<Args...>>
  TrueType __sfinae_test_impl(int);
  template<template<typename...> typename, typename...>
  FalseType __sfinae_test_impl(...);

  template<template<typename...> typename Template, typename... Args>
  using __IsValidExpression = decltype(__sfinae_test_impl<Template, Args...>(0));

  // is primary template

  template<typename T>
  using __TestForPrimaryTemplate = EnableIf_T<IsSame<T, typename T::__primary_template>::value>;

  template<typename T>
  using __IsPrimaryTemplate = __IsValidExpression<__TestForPrimaryTemplate, T>;


  /* +------------------------------+ */
  /* |       Implementations        | */
  /* +------------------------------+ */

  template<typename T, T V>
  struct IntegralConstant {
    static constexpr T value = V;
    using ValueType = T;
    using Type = IntegralConstant<T, V>;

    constexpr operator ValueType() const noexcept { return value; }
    constexpr ValueType operator()() const noexcept { return value; }
  };

  /* IsVoid-Impl */
  template<typename T>
  struct IsVoid : IsSame<void, RemoveCV_T<T>> { };

  /* IsNullPointer-Impl */
  template<typename T>
  struct IsNullPointer : IsSame<nullptr_t, RemoveCV_T<T>> { };

  /* IsIntegral-Impl TODO: is bool integral? */
  template<typename T>
  struct IsIntegral : FalseType { };

  template<>
  struct IsIntegral<signed char> : TrueType { };

  template<>
  struct IsIntegral<short int> : TrueType { };

  template<>
  struct IsIntegral<int> : TrueType { };

  template<>
  struct IsIntegral<long int> : TrueType { };

  template<>
  struct IsIntegral<long long int> : TrueType { };

  template<>
  struct IsIntegral<unsigned char> : TrueType { };

  template<>
  struct IsIntegral<unsigned short int> : TrueType { };

  template<>
  struct IsIntegral<unsigned int> : TrueType { };

  template<>
  struct IsIntegral<unsigned long int> : TrueType { };

  template<>
  struct IsIntegral<unsigned long long int> : TrueType { };

  /* IsFloatingPoint-Impl */
  template<typename T>
  struct IsFloatingPoint : IntegralConstant<bool,
    is_same_v<float, RemoveCV_T<T>> ||
    is_same_v<double, RemoveCV_T<T>> ||
    is_same_v<long double, RemoveCV_T<T>>> { };

  /* IsArray-Impl */
  template<typename T>
  struct IsArray : FalseType { };

  template<typename T>
  struct IsArray<T[]> : TrueType { };

  template<typename T, size_t N>
  struct IsArray<T[N]> : TrueType { };

  /* IsPointer-Impl */
  template<typename T>
  struct IsPointer : FalseType { };

  template<typename T>
  struct IsPointer<T*> : FalseType { };

  template<typename T>
  struct IsPointer<T* const> : FalseType { };

  template<typename T>
  struct IsPointer<T* volatile> : FalseType { };

  template<typename T>
  struct IsPointer<T* const volatile> : FalseType { };

  /* IsLValueReference-Impl */
  template<typename T>
  struct IsLValueReference : FalseType { };

  template<typename T>
  struct IsLValueReference<T&> : TrueType { };

  /* IsRValueReference-Impl */
  template<typename T>
  struct IsRValueReference : FalseType { };

  template<typename T>
  struct IsRValueReference<T&&> : TrueType { };

  /* IsMemberObjectPointer-Impl */
  template<typename T>
  struct IsMemberObjectPointer : IntegralConstant<bool,
    is_member_pointer_v<T> && !is_member_function_pointer_v<T>> { };

  /* IsEnum-Impl */
  template<typename T>
  struct IsEnum : IntegralConstant<bool, __is_enum(T)> { };

  /* IsUnion-Impl */
  template<typename T>
  struct IsUnion : IntegralConstant<bool, __is_union(T)> { };

  /* IsClass-Impl */
  template<typename T>
  struct IsClass : IntegralConstant<bool, __is_class(T)> { };

  /* IsFunction-Impl */
  template<typename T>
  struct IsFunction : IntegralConstant<bool, __is_function(T)> { };

  /* IsReference-Impl */
  template<typename T>
  struct IsReference : FalseType { };

  template<typename T>
  struct IsReference<T&> : TrueType { };

  template<typename T>
  struct IsReference<T&&> : TrueType { };

  /* IsArithmetic-Impl */
  template<typename T>
  struct IsArithmetic : IntegralConstant<bool,
    is_integral_v<T> || is_floating_point_v<T>> { };

  /* IsFundamental-Impl */
  template<typename T>
  struct IsFundamental : IntegralConstant<bool,
    is_arithmetic_v<T> || is_void_v<T> || is_null_pointer_v<T>> { };

  /* IsObject-Impl */
  template<typename T>
  struct IsObject : IntegralConstant<bool,
    is_scalar_v<T> || is_array_v<T> || is_union_v<T> || is_class_v<T>> { };

  /* IsScalar-Impl */
  template<typename T>
  struct IsScalar : IntegralConstant<bool,
    is_arithmetic_v<T> || is_enum_v<T> || is_pointer_v<T> || is_member_pointer_v<T> || is_null_pointer_v<T>> { };

  /* IsCompound-Impl */
  template<typename T>
  struct IsCompound : IntegralConstant<bool, !is_fundamental_v<T>> { };

  /* IsMemberPointer-Impl */
  template<typename T>
  struct __IsMemberPointerHelper : FalseType { };

  template<typename T, typename U>
  struct __IsMemberPointerHelper<T U::*> : TrueType { };

  template<typename T>
  struct IsMemberPointer : __IsMemberPointerHelper<RemoveCV_T<T>> { };

  /* IsConst-Impl */
  template<typename T>
  struct IsConst : FalseType { };

  template<typename T>
  struct IsConst<const T> : TrueType { };

  /* IsVolatile-Impl */
  template<typename T>
  struct IsVolatile : FalseType { };

  template<typename T>
  struct IsVolatile<volatile T> : TrueType { };

  /* IsTrivial-Impl */
  template<typename T>
  struct IsTrivial : IntegralConstant<bool,
    is_trivially_copyable_v<T> && is_trivially_default_constructible_v<T>> { };

  /* IsTriviallyCopyable-Impl */
  template<typename T>
  struct IsTriviallyCopyable : IntegralConstant<bool, __is_trivially_copyable(T)> { };

  /* IsStandardLayout-Impl */
  template<typename T>
  struct IsStandardLayout : IntegralConstant<bool, __is_standard_layout(T)> { };

  /* IsEmpty-Impl */
  template<typename T>
  struct IsEmpty : IntegralConstant<bool, __is_empty(T)> { };

  /* IsPolymorphic-Impl */
  template<typename T>
  struct IsPolymorphic : IntegralConstant<bool, __is_polymorphic(T)> { };

  /* IsAbstract-Impl */
  template<typename T>
  struct IsAbstract : IntegralConstant<bool, __is_abstract(T)> { };

  /* IsFinal-Impl */
  template<typename T>
  struct IsFinal : IntegralConstant<bool, __is_final(T)> { };

  /* IsAggregate-Impl */
  template<typename T>
  struct IsAggregate : IntegralConstant<bool, __is_aggregate(T)> { };

  /* IsSigned-Impl */
  template<typename T, bool = is_arithmetic_v<T>>
  struct __IsSigned : IntegralConstant<bool, T(-1) < T(0)> { };

  template<typename T>
  struct __IsSigned<T, false> : FalseType { };

  template<typename T>
  struct IsSigned : __IsSigned<T>::type { };

  /* IsUnsigned-Impl */
  template<typename T, bool = is_arithmetic_v<T>>
  struct __IsUnsigned : IntegralConstant<bool, T(0) < T(-1)> { };

  template<typename T>
  struct __IsUnsigned<T, false> : FalseType { };

  template<typename T>
  struct IsUnsigned : __IsUnsigned<T>::type { };

  /* IsBoundedArray-Impl */
  template<typename T>
  struct IsBoundedArray : FalseType { };

  template<typename T, size_t N>
  struct IsBoundedArray<T[N]> : TrueType { };

  /* IsUnboundedArray-Impl */
  template<typename T>
  struct IsUnboundedArray : FalseType { };

  template<typename T>
  struct IsUnboundedArray<T[]> : TrueType { };

  /* IsScopedEnum-Impl */ /* TODO */

  /* IsConstructible-Impl */
  template<typename T, typename... Args>
  struct IsConstructible : IntegralConstant<bool, __is_constructible(T, Args...)> { };

  /* IsDefaultConstructible-Impl */
  template<typename T>
  struct IsDefaultConstructible : IsConstructible<T> { };

  /* IsCopyConstructible-Impl */
  template<typename T>
  struct IsCopyConstructible : IsConstructible<T, AddLValueReference_T<AddConst_T<T>>> { };

  /* IsMoveConstructible-Impl */
  template<typename T>
  struct IsMoveConstructible : IsConstructible<T, AddRValueReference_T<T>> { };

  /* IsAssignable-Impl */
  template<typename T, typename U>
  struct IsAssignable : IntegralConstant<bool, __is_assignable(T, U)> { };

  /* IsCopyAssignable-Impl */
  template<typename T>
  struct IsCopyAssignable : IsAssignable<AddLValueReference_T<T>, AddLValueReference_T<const T>> { };

  /* IsMoveAssignable-Impl */
  template<typename T>
  struct IsMoveAssignable : IsAssignable<AddLValueReference_T<T>, AddRValueReference_T<T>> { };

  /* IsSwappableWith-Impl TODO */
  template<typename T, typename U>
  struct IsSwappableWith : std::is_swappable_with<T, U> { };

  /* IsSwappable-Impl */
  template<typename T>
  struct IsSwappable : IsSwappableWith<T&, T&> { };

  /* IsDestructible-Impl TODO */
  template<typename T>
  struct IsDestructible : std::is_destructible<T> { };

  /* IsTriviallyConstructible-Impl */
  template<typename T, typename... Args>
  struct IsTriviallyConstructible : IntegralConstant<bool, __is_trivially_constructible(T, Args...)> { };

  /* IsTriviallyDefaultConstructible-Impl */
  template<typename T>
  struct IsTriviallyDefaultConstructible : IsTriviallyConstructible<T> { };

  /* IsTriviallyCopyConstructible-Impl */
  template<typename T>
  struct IsTriviallyCopyConstructible : IsTriviallyConstructible<T, AddLValueReference_T<AddConst_T<T>>> { };

  /* IsTriviallyMoveConstructible-Impl */
  template<typename T>
  struct IsTriviallyMoveConstructible : IsTriviallyConstructible<T, AddRValueReference_T<T>> { };

  /* IsTriviallyAssignable-Impl */
  template<typename T, typename U>
  struct IsTriviallyAssignable : IntegralConstant<bool, __is_trivially_assignable(T, U)> { };

  /* IsTriviallyCopyAssignable-Impl */
  template<typename T>
  struct IsTriviallyCopyAssignable : IsTriviallyAssignable<AddLValueReference_T<T>, AddLValueReference_T<const T>> { };

  /* IsTriviallyMoveAssignable-Impl */
  template<typename T>
  struct IsTriviallyMoveAssignable : IsTriviallyAssignable<AddLValueReference_T<T>, AddRValueReference_T<T>> { };

  /* IsTriviallyDestructible-Impl TODO */
  template<typename T>
  struct IsTriviallyDestructible : std::is_trivially_destructible<T> { };

  /* IsNothrowConstructible-Impl */
  template<typename T, typename... Args>
  struct IsNothrowConstructible : IntegralConstant<bool, __is_nothrow_constructible(T, Args...)> { };

  /* IsNothrowDefaultConstructible-Impl */
  template<typename T>
  struct IsNothrowDefaultConstructible : IsNothrowConstructible<T> { };

  /* IsNothrowCopyConstructible-Impl */
  template<typename T>
  struct IsNothrowCopyConstructible : IsNothrowConstructible<T, AddLValueReference_T<AddConst_T<T>>> { };

  /* IsNothrowMoveConstructible-Impl */
  template<typename T>
  struct IsNothrowMoveConstructible : IsNothrowConstructible<T, AddRValueReference_T<T>> { };

  /* IsNothrowAssignable-Impl */
  template<typename T, typename U>
  struct IsNothrowAssignable : IntegralConstant<bool, __is_nothrow_assignable(T, U)> { };

  /* IsNothrowCopyAssignable-Impl */
  template<typename T>
  struct IsNothrowCopyAssignable : IsNothrowAssignable<AddLValueReference_T<T>, AddLValueReference_T<const T>> { };

  /* IsNothrowMoveAssignable-Impl */
  template<typename T>
  struct IsNothrowMoveAssignable : IsNothrowAssignable<AddLValueReference_T<T>, AddRValueReference_T<T>> { };

  /* IsNothrowSwappableWith-Impl TODO */
  template<typename T, typename U>
  struct IsNothrowSwappableWith : std::is_nothrow_swappable_with<T, U> { };

  /* IsNothrowSwappable-Impl */
  template<typename T>
  struct IsNothrowSwappable : IsNothrowSwappableWith<T&, T&> { };

  /* IsNothrowDestructible-Impl TODO */
  template<typename T>
  struct IsNothrowDestructible : std::is_nothrow_destructible<T> { };

  /* HasVirtualDestructor-Impl */
  template<typename T>
  struct HasVirtualDestructor : IntegralConstant<bool, __has_virtual_destructor(T)> { };

  /* HasUniqueObjectRepresentations-Impl */
  template<typename T>
  struct HasUniqueObjectRepresentations : IntegralConstant<bool, __has_unique_object_representations(T)> { };

  /* AlignmentOf-Impl */
  template<typename T>
  struct AlignmentOf : IntegralConstant<size_t, alignof(T)> { };

  /* Rank-Impl */
  template<typename T>
  struct Rank : IntegralConstant<size_t, 0> { };

  template<typename T>
  struct Rank<T[]> : IntegralConstant<size_t, Rank<T>::value + 1> { };

  template<typename T, size_t N>
  struct Rank<T[N]> : IntegralConstant<size_t, Rank<T>::value + 1> { };

  /* Extent-Impl */
  template<typename T, unsigned N>
  struct Extent : IntegralConstant<size_t, 0> { };

  template<typename T>
  struct Extent<T[], 0> : IntegralConstant<size_t, 0> { };

  template<typename T, unsigned N>
  struct Extent<T[], N> : Extent<T, N - 1> { };

  template<typename T, size_t I>
  struct Extent<T[I], 0> : IntegralConstant<size_t, I> { };

  template<typename T, size_t I, unsigned N>
  struct Extent<T[I], N> : Extent<T, N - 1> { };

  /* IsSame-Impl */
  template<typename T, typename U>
  struct IsSame : FalseType { };

  template<typename T>
  struct IsSame<T, T> : TrueType { };

  /* IsBaseOf-Impl */
  template<typename B>
  TrueType __test_pre_ptr_convertible(const volatile B*);
  template<typename>
  FalseType __test_pre_ptr_convertible(const volatile void*);

  template<typename, typename>
  auto __test_pre_is_base_of(...) -> TrueType;
  template<typename B, typename D>
  auto __test_pre_is_base_of(int) -> decltype(__test_pre_ptr_convertible<B>(static_cast<D*>(nullptr)));

  template<typename Base, typename Derived>
  struct IsBaseOf : IntegralConstant<bool,
    is_class_v<Base> && is_class_v<Derived> && decltype(__test_pre_is_base_of<Base, Derived>(0))::value> { };

  /* IsConvertible-Impl */
  template<typename T>
  auto __test_returnable(int) -> decltype(void(static_cast<T(*)()>(nullptr)), TrueType { });
  template<typename>
  auto __test_returnable(...) -> FalseType;

  template<typename From, typename To>
  auto __test_implicitly_convertible(int) -> decltype(void(declval<void(&)(To)>()(declval<From>())), TrueType { });
  template<typename, typename>
  auto __test_implicitly_convertible(...) -> FalseType;

  template<typename From, typename To>
  struct IsConvertible : IntegralConstant<bool,
    (decltype(__test_returnable<To>(0))::value &&
     decltype(__test_implicitly_convertible<From, To>(0))::value) ||
    (is_void_v<From> && is_void_v<To>)> { };

  /* IsNothrowConvertible-Impl */
  template<typename From, typename To>
  struct IsNothrowConvertible : Conjunction<IsVoid<From>, IsVoid<To>> { };

  template<typename From, typename To>
    requires requires {
	static_cast<To(*)()>(nullptr);
	{ declval<void(&)(To) noexcept>()(declval<From>()) } noexcept;
      }
  struct IsNothrowConvertible<From, To> : TrueType { };

  /* IsLayoutCompatible-Impl TODO */
  template<typename T, typename U>
  struct IsLayoutCompatible { };

  /* IsPointerInterconvertibleBaseOf-Impl TODO */
  template<typename Base, typename Derived>
  struct IsPointerInterconvertibleBaseOf { };

  /* IsInvocable-Impl */
  template<typename Fn, typename... ArgTypes>
  struct IsInvocable : std::is_invocable<Fn, ArgTypes...> { };

  /* IsInvocableR-Impl */
  template<typename R, typename Fn, typename... ArgTypes>
  struct IsInvocableR : std::is_invocable_r<R, Fn, ArgTypes...> { };

  /* IsNothrowInvocable-Impl */
  template<typename Fn, typename... ArgTypes>
  struct IsNothrowInvocable : std::is_nothrow_invocable<Fn, ArgTypes...> { };

  /* IsNothrowInvocableR-Impl */
  template<typename R, typename Fn, typename... ArgTypes>
  struct IsNothrowInvocableR : std::is_nothrow_invocable_r<R, Fn, ArgTypes...> { };

  /* RemoveConst-Impl */
  template<typename T>
  struct RemoveConst { typedef T Type; };

  template<typename T>
  struct RemoveConst<const T> { typedef T Type; };

  /* RemoveVolatile-Impl */
  template<typename T>
  struct RemoveVolatile { typedef T Type; };

  template<typename T>
  struct RemoveVolatile<volatile T> { typedef T Type; };

  /* RemoveCV-Impl */
  template<typename T>
  struct RemoveCV { typedef T Type; };

  template<typename T>
  struct RemoveCV<const T> { typedef T Type; };

  template<typename T>
  struct RemoveCV<volatile T> { typedef T Type; };

  template<typename T>
  struct RemoveCV<const volatile T> { typedef T Type; };

  /* AddConst-Impl */
  template<typename T>
  struct AddConst { typedef const T Type; };

  /* AddVolatile-Impl */
  template<typename T>
  struct AddVolatile { typedef volatile T Type; };

  /* AddCV-Impl */
  template<typename T>
  struct AddCV { typedef const volatile T Type; };

  /* RemoveReference-Impl */
  template<typename T>
  struct RemoveReference { typedef T Type; };

  template<typename T>
  struct RemoveReference<T&> { typedef T Type; };

  template<typename T>
  struct RemoveReference<T&&> { typedef T Type; };

  /* AddLValueReference-Impl */
  template<typename T>
  auto __try_add_lvalue_reference(int) -> TypeIdentity<T&>;
  template<typename T>
  auto __try_add_lvalue_reference(...) -> TypeIdentity<T>;

  template<typename T>
  struct AddLValueReference : decltype(__try_add_lvalue_reference<T>(0)) { };

  /* AddRValueReference-Impl */
  template<typename T>
  auto __try_add_rvalue_reference(int) -> TypeIdentity<T&&>;
  template<typename T>
  auto __try_add_rvalue_reference(...) -> TypeIdentity<T>;

  template<typename T>
  struct AddRValueReference : decltype(__try_add_rvalue_reference<T>(0)) { };

  /* MakeSigned-Impl TODO */
  template<typename T>
  struct MakeSigned : std::make_signed<T> { };

  /* MakeUnsigned-Impl TODO */
  template<typename T>
  struct MakeUnsigned : std::make_unsigned<T> { };

  /* RemoveExtent-Impl */
  template<typename T>
  struct RemoveExtent { typedef T Type; };

  template<typename T>
  struct RemoveExtent<T[]> { typedef T Type; };

  template<typename T, size_t N>
  struct RemoveExtent<T[N]> { typedef T Type; };

  /* RemoveAllExtents-Impl */
  template<typename T>
  struct RemoveAllExtents { typedef T Type; };

  template<typename T>
  struct RemoveAllExtents<T[]> { typedef typename RemoveAllExtents<T>::Type Type; };

  template<typename T, size_t N>
  struct RemoveAllExtents<T[N]> { typedef typename RemoveAllExtents<T>::Type Type; };

  /* RemovePointer-Impl */
  template<typename T>
  struct RemovePointer { typedef T Type; };

  template<typename T>
  struct RemovePointer<T*> { typedef T Type; };

  template<typename T>
  struct RemovePointer<T* const> { typedef T Type; };

  template<typename T>
  struct RemovePointer<T* volatile> { typedef T Type; };

  template<typename T>
  struct RemovePointer<T* const volatile> { typedef T Type; };

  /* AddPointer-Impl */
  template<typename T>
  auto __try_add_pointer(int) -> TypeIdentity<RemoveReference_T<T>*>;
  template<typename T>
  auto __try_add_pointer(...) -> TypeIdentity<T>;

  template<typename T>
  struct AddPointer : decltype(__try_add_pointer<T>(0)) { };

  /* TypeIdentity-Impl */
  template<typename T>
  struct TypeIdentity { typedef T Type; };

  /* AlignedStorage-Impl */
  template<size_t Len, size_t Align>
  struct AlignedStorage {
    struct Type {
      alignas(Align) unsigned char data[Len];
    };
  };

  /* AlignedUnion-Impl */
  template<size_t Len, typename... Types>
  struct AlignedUnion {
    static constexpr size_t alignment_value = max({alignof(Types)...});
    struct Type {
      alignas(alignment_value) char _s[max({Len, sizeof(Types)...})];
    };
  };

  /* RemoveCVRef-Impl */
  template<typename T>
  struct RemoveCVRef { typedef RemoveCV_T<RemoveReference_T<T>> Type; };

  /* Decay-Impl */
  template<typename T>
  struct Decay {
  private:
    typedef RemoveReference_T<T> U;
  public:
    typedef Conditional_T<
      is_array_v<U>,
      RemoveExtent_T<U>,
      Conditional_T<
	is_function_v<U>,
	AddPointer_T<U>,
	RemoveCV_T<U>
      >
    > Type;
  };

  /* EnableIf-Impl */
  template<bool B, typename T>
  struct EnableIf { };

  template<typename T>
  struct EnableIf<true, T> { typedef T Type; };

  /* Conditional-Impl */
  template<bool B, typename T, typename F>
  struct Conditional { typedef T Type; };

  template<typename T, typename F>
  struct Conditional<false, T, F> { typedef F Type; };

  /* CommonType-Impl */
  template<typename...>
  struct CommonType { };

  template<typename T>
  struct CommonType<T> : CommonType<T, T> { };

  template<typename...>
  using __Void_T = void;

  template<typename T1, typename T2>
  using __ConditionalResult_T = decltype(false ? declval<T1>() : declval<T2>());

  template<typename, typename, typename = void>
  struct __DecayConditionalResult { };
  template<typename T1, typename T2>
  struct __DecayConditionalResult<T1, T2, __Void_T<__ConditionalResult_T<T1, T2>>>
    : Decay<__ConditionalResult_T<T1, T2>> { };

  template<typename T1, typename T2, typename = void>
  struct __CommonType2Impl : __DecayConditionalResult<const T1&, const T2&> { };
  template<typename T1, typename T2>
  struct __CommonType2Impl<T1, T2, __Void_T<__ConditionalResult_T<T1, T2>>>
    : __DecayConditionalResult<T1, T2> { };

  template<typename T1, typename T2>
  struct CommonType<T1, T2> : Conditional<
    is_same_v<T1, Decay_T<T1>> && is_same_v<T2, Decay_T<T2>>,
    __CommonType2Impl<T1, T2>, CommonType<Decay_T<T2>, Decay_T<T1>>>::Type { };

  template<typename AlwaysVoid, typename T1, typename T2, typename... R>
  struct __CommonTypeMultiImpl { };
  template<typename T1, typename T2, typename... R>
  struct __CommonTypeMultiImpl<__Void_T<typename CommonType<T1, T2>::Type>, T1, T2, R...>
    : CommonType<typename CommonType<T1, T2>::Type, R...> { };

  template<typename T1, typename T2, typename... R>
  struct CommonType<T1, T2, R...> : __CommonTypeMultiImpl<void, T1, T2, R...> { };

  /* CommonReference-Impl */
  template<typename A>
  using __CRef_T = AddLValueReference_T<const RemoveReference_T<A>>;

  /* copy T's cv qualifiers to U */
  template<typename T, typename U>
  struct __CopyCV { typedef U Type; };
  template<typename T, typename U>
  struct __CopyCV<const T, U> { typedef const U Type; };
  template<typename T, typename U>
  struct __CopyCV<volatile T, U> { typedef volatile U Type; };
  template<typename T, typename U>
  struct __CopyCV<const volatile T, U> { typedef const volatile U Type; };

  /* copy T's reference qualifier to U */
  template<typename T, typename U>
  struct __CopyRef { typedef U Type; };
  template<typename T, typename U>
  struct __CopyRef<T&, U> { typedef U& Type; };
  template<typename T, typename U>
  struct __CopyRef<T&&, U> { typedef U&& Type; };

  /* copy T's cv and reference qualifiers to U */
  template<typename T, typename U>
  struct __CopyCVRef {
    typedef typename __CopyCV<T, __CopyRef<T, U>>::Type Type;
  };

  template<typename T>
  struct __XRef {
    template<typename U>
    using Type = typename __CopyCVRef<T, U>::Type;
  };

  template<typename From, typename To>
  using __CopyCV_T = typename __CopyCV<From, To>::Type;

  template<typename X, typename Y>
  using __CondRes_T = decltype(false ? declval<X(&)()>()() : declval<Y(&)()>()());

  template<typename A, typename B>
  struct __CommonRef {
  };

  template<typename A, typename B>
  struct __CommonRef<A&, B&> {
    typedef RemoveReference_T<A> X;
    typedef RemoveReference_T<B> Y;
    typedef __CondRes_T<__CopyCV_T<X, Y>&, __CopyCV_T<Y, X>&> V;
    using Type = decltype(is_reference_v<V> ? declval<V()>()() : nullptr);
  };

  template<typename A, typename B>
  struct __CommonRef<A&&, B&&> {
    typedef RemoveReference_T<A> X;
    typedef RemoveReference_T<B> Y;
    typedef RemoveReference_T<__CommonRef<X&, Y&>>&& C;
    using Type = decltype(is_convertible_v<A, C> && is_convertible_v<B, C> ? declval<C()>()() : nullptr);
  };

  template<typename A, typename B>
  struct __CommonRef<A&&, B&> {
    typedef RemoveReference_T<A> X;
    typedef RemoveReference_T<B> Y;
    typedef typename __CommonRef<const X&, Y&>::Type D;
    using Type = decltype(is_convertible_v<A, D> ? declval<D()>()() : nullptr);
  };

  template<typename A, typename B>
  struct __CommonRef<A&, B&&> {
    typedef RemoveReference_T<A> X;
    typedef RemoveReference_T<B> Y;
    typedef typename __CommonRef<B, A>::Type Type;
  };

  template<typename... T>
  struct CommonReference { };

  /* CommonReference == 0 */
  template<>
  struct CommonReference<> { };

  /* CommonReference == 1 */
  template<typename T1>
  struct CommonReference<T1> { typedef T1 Type; };

  /* CommonReference == 2 */
  template<typename T1, typename T2>
  struct CommonReference<T1, T2> { };

  template<typename T1, typename T2>
    requires is_reference_v<T1> && is_reference_v<T2> && requires {
      typename __CommonRef<T1, T2>::Type;
    }
  struct CommonReference<T1, T2> {
    typedef typename __CommonRef<T1, T2>::Type Type;
  };

  template<typename T1, typename T2>
    requires requires {
      typename BasicCommonReference<RemoveCVRef_T<T1>, RemoveCVRef_T<T2>,
	__XRef<T1>::template Type, __XRef<T2>::template Type>::Type;
    }
  struct CommonReference<T1, T2> {
    typedef typename BasicCommonReference<RemoveCVRef_T<T1>, RemoveCVRef_T<T2>,
      __XRef<T1>::template Type, __XRef<T2>::template Type>::Type Type;
  };

  template<typename T1, typename T2>
    requires requires {
      typename __CondRes_T<T1, T2>;
    }
  struct CommonReference<T1, T2> {
    typedef __CondRes_T<T1, T2> Type;
  };

  template<typename T1, typename T2>
    requires requires {
      typename CommonType_T<T1, T2>;
    }
  struct CommonReference<T1, T2> {
    typedef CommonType_T<T1, T2> Type;
  };

  /* CommonReference > 2 */
  template<typename T1, typename T2, typename... Rest>
  struct CommonReference<T1, T2, Rest...> {
    typedef typename CommonReference<T1, T2>::Type C;
    using Type = typename CommonReference<C, Rest...>::Type;
  };

  /* Conjunction-Impl */
  template<typename...>
  struct Conjunction : TrueType { };

  template<typename B1>
  struct Conjunction<B1> : B1 { };

  template<typename B1, typename... Bn>
  struct Conjunction<B1, Bn...> : Conditional_T<bool(B1::value), Conjunction<Bn...>, B1> { };

  /* Disjunction-Impl */
  template<typename...>
  struct Disjunction : FalseType { };

  template<typename B1>
  struct Disjunction<B1> : B1 { };

  template<typename B1, typename... Bn>
  struct Disjunction<B1, Bn...> : Conditional_T<bool(B1::value), B1, Disjunction<Bn...>> { };

  /* Negation-Impl */
  template<typename B>
  struct Negation : BoolConstant<!bool(B::value)> { };

  /* is_pointer_interconvertible_with_class-Impl */
  template<typename S, typename M>
  constexpr bool is_pointer_interconvertible_with_class(M S::*m) noexcept
  {
    return __builtin_is_pointer_interconvertible_with_class(m);
  }

  /* is_corresponding_member-Impl */
  template<typename S1, typename S2, typename M1, typename M2>
  constexpr bool is_corresponding_member(M1 S1::*m1, M2 S2::*m2) noexcept
  {
    return __builtin_is_corresponding_member(m1, m2);
  }

  /* is_constant_evaluated-Impl */
  constexpr bool is_constant_evaluated() noexcept
  {
    return __builtin_is_constant_evaluated();
  }

  template<typename> struct __Void { typedef void Type; };

} // namespace me

#endif
