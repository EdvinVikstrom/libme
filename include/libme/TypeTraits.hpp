#ifndef LIBME_TYPE_TRAITS_HPP
  #define LIBME_TYPE_TRAITS_HPP

#include "Type.hpp"

#include <type_traits>

namespace me {

  template<typename Type, Type Value>
  struct integral_constant {
    static constexpr Type value = Value;
    using value_type = Type;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return Value; }
  };

  template<bool Value>
  struct bool_constant : integral_constant<bool, Value> { };

  struct false_type : bool_constant<false> { };
  struct true_type : bool_constant<true> { };

  template<typename T1, typename T2> struct is_same;
  template<typename T> struct add_lvalue_reference;
  template<typename T> struct add_rvalue_reference;
  template<typename T> struct remove_cv;
  template<typename T> struct add_const;
  template<bool Value, typename Type1, typename Type2> struct conditional;
  template<typename...> struct conjunction;

  namespace detail {

    template<typename T> struct type_identity { typedef T type; };
    template<typename T> auto try_add_lvalue_reference(int) -> type_identity<T&>;
    template<typename T> auto try_add_lvalue_reference(...) -> type_identity<T>;
    template<typename T> auto try_add_rvalue_reference(int) -> type_identity<T&&>;
    template<typename T> auto try_add_rvalue_reference(...) -> type_identity<T>;

    template<typename T> struct make_signed_helper { typedef signed type; };
    template<> struct make_signed_helper<int8_t> { typedef int8_t type; };
    template<> struct make_signed_helper<uint8_t> { typedef int8_t type; };
    template<> struct make_signed_helper<int16_t> { typedef int16_t type; };
    template<> struct make_signed_helper<uint16_t> { typedef int16_t type; };
    template<> struct make_signed_helper<int32_t> { typedef int32_t type; };
    template<> struct make_signed_helper<uint32_t> { typedef int32_t type; };
    template<> struct make_signed_helper<int64_t> { typedef int64_t type; };
    template<> struct make_signed_helper<uint64_t> { typedef int64_t type; };

    template<typename T> struct make_unsigned_helper { typedef unsigned type; };
    template<> struct make_unsigned_helper<int8_t> { typedef uint8_t type; };
    template<> struct make_unsigned_helper<uint8_t> { typedef uint8_t type; };
    template<> struct make_unsigned_helper<int16_t> { typedef uint16_t type; };
    template<> struct make_unsigned_helper<uint16_t> { typedef uint16_t type; };
    template<> struct make_unsigned_helper<int32_t> { typedef uint32_t type; };
    template<> struct make_unsigned_helper<uint32_t> { typedef uint32_t type; };
    template<> struct make_unsigned_helper<int64_t> { typedef uint64_t type; };
    template<> struct make_unsigned_helper<uint64_t> { typedef uint64_t type; };

    template<typename T> struct is_pointer_helper : false_type { };
    template<typename T> struct is_pointer_helper<T*> : true_type { };

    template<typename T> auto test_returnable(bool) -> decltype(
	void(static_cast<T(*)>(nullptr)), true_type{});
    template<typename> auto test_returnable(...) -> false_type;

    template<typename A, typename B> auto test_implicitly_convertible(bool) -> decltype(
	void(std::declval<void(&)(B)>()(std::declval<A>())), true_type{});
    template<typename, typename> auto test_implicitly_convertible(...) -> false_type;

  } // namespace detail


  /* -------------------------------- */
  /*     Primary type categories      */
  /* -------------------------------- */

  /* is_void */
  template<typename T> struct is_void : is_same<void, typename remove_cv<T>::type> { };

  /* is_null_pointer */
  template<typename T> struct is_null_pointer : is_same<nullptr_t, typename remove_cv<T>::type> { };

  /* is_integral */
  template<typename T> struct is_integral : bool_constant<__is_integral(T)> { };

  /* is_floating_point */
  template<typename T> struct is_floating_point : bool_constant<
						  is_same<float, typename remove_cv<T>::type>::type ||
						  is_same<double, typename remove_cv<T>::type>::type ||
						  is_same<long double, typename remove_cv<T>::type>::type> { };

  /* is_array */
  template<typename T> struct is_array : false_type { };
  template<typename T> struct is_array<T[]> : true_type { };
  template<typename T, size_t N> struct is_array<T[N]> : true_type { };

  /* is_enum */
  template<typename T> struct is_enum : bool_constant<__is_enum(T)> { };

  /* is_union */
  template<typename T> struct is_union : bool_constant<__is_union(T)> { };

  /* is_class */
  template<typename T> struct is_class : bool_constant<__is_class(T)> { };

  /* is_function */
  template<typename T> struct is_function : bool_constant<__is_function(T)> { };

  /* is_pointer */
  template<typename T> struct is_pointer : detail::is_pointer_helper<typename remove_cv<T>::type> { };

  /* is_lvalue_reference */
  template<typename T> struct is_lvalue_reference : false_type { };
  template<typename T> struct is_lvalue_reference<T&> : true_type { };

  /* is_rvalue_reference */
  template<typename T> struct is_rvalue_reference : false_type { };
  template<typename T> struct is_rvalue_reference<T&&> : true_type { };

  /* is_member_object_pointer */
  template<typename T> struct is_member_object_pointer { }; // TODO

  /* is_member_function_pointer */
  template<typename T> struct is_member_function_pointer { }; // TODO


  /* -------------------------------- */
  /*    Composite type categories     */
  /* -------------------------------- */
  
  /* is_fundamental */
  template<typename T> struct is_fundamental { }; // TODO

  /* is_arithmetic */
  template<typename T> struct is_arithmetic : bool_constant<
					      is_integral<T>::value ||
					      is_floating_point<T>::value> { };

  /* is_scalar */
  template<typename T> struct is_scalar { }; // TODO

  /* is_object */
  template<typename T> struct is_object { }; // TODO

  /* is_compound */
  template<typename T> struct is_compound : bool_constant<!is_fundamental<T>::value> { };

  /* is_reference */
  template<typename T> struct is_reference : bool_constant<
					     is_lvalue_reference<T>::value ||
					     is_rvalue_reference<T>::value> { };

  /* is_member_pointer */
  template<typename T> struct is_member_pointer { }; // TODO


  /* -------------------------------- */
  /*         Type properties          */
  /* -------------------------------- */

  /* is_const */
  template<typename T> struct is_const : false_type { };
  template<typename T> struct is_const<const T> : true_type { };

  /* is_volatile */
  template<typename T> struct is_volatile : false_type { };
  template<typename T> struct is_volatile<volatile T> : true_type { };

  /* is_trivial */
  template<typename T> struct is_trivial { }; // TODO

  /* is_trivially_copyable */
  template<typename T> struct is_trivially_copyable : bool_constant<__is_trivially_copyable(T)> { };

  /* is_standard_layout */
  template<typename T> struct is_standard_layout : bool_constant<__is_standard_layout(T)> { };

  /* is_pod */
  template<typename T> struct is_pod : bool_constant<__is_pod(T)> { };

  /* has_unique_object_representations */
  template<typename T> struct has_unique_object_representations : bool_constant<__has_unique_object_representations(T)> { };

  /* is_empty */
  template<typename T> struct is_empty : bool_constant<__is_empty(T)> { };

  /* is_polymorphic */
  template<typename T> struct is_polymorphic : bool_constant<__is_polymorphic(T)> { };

  /* is_abstract */
  template<typename T> struct is_abstract : bool_constant<__is_abstract(T)> { };

  /* is_final */
  template<typename T> struct is_final : bool_constant<__is_final(T)> { };

  /* is_aggregate */
  template<typename T> struct is_aggregate : bool_constant<__is_aggregate(T)> { };

  /* is_signed */
  template<typename T> struct is_signed : bool_constant<__is_signed(T)> { };

  /* is_unsigned */
  template<typename T> struct is_unsigned : bool_constant<__is_unsigned(T)> { };

  /* is_bounded_array */
  template<typename T> struct is_bounded_array : false_type { };
  template<typename T, size_t N> struct is_bounded_array<T[N]> : true_type { };

  /* is_unbounded_array */
  template<typename T> struct is_unbounded_array : false_type { };
  template<typename T> struct is_unbounded_array<T[]> : true_type { };

  /* is_scoped_enum */
  template<typename T> struct is_scoped_enum : bool_constant<__is_scoped_enum(declval<T>())> { }; // TODO: ?


  /* -------------------------------- */
  /*       Supported operations       */
  /* -------------------------------- */

  /* is_constructible */
  template<typename T, typename... A> struct is_constructible : bool_constant<__is_constructible(T, A...)> { };
  template<typename T, typename... A> struct is_trivially_constructible : bool_constant<__is_trivially_constructible(T, A...)> { };
  template<typename T, typename... A> struct is_nothrow_constructible : bool_constant<__is_nothrow_constructible(T, A...)> { };

  /* is_default_constructible */
  template<typename T> struct is_default_constructible : is_constructible<T> { };
  template<typename T> struct is_trivially_default_constructible : is_trivially_constructible<T> { };
  template<typename T> struct is_nothrow_default_constructible : is_nothrow_constructible<T> { };

  /* is_copy_constructible */
  template<typename T> struct is_copy_constructible : is_constructible<T, typename add_lvalue_reference<typename add_const<T>::type>::type> { };
  template<typename T> struct is_trivially_copy_constructible : is_trivially_constructible<T, typename add_lvalue_reference<typename add_const<T>::type>::type> { };
  template<typename T> struct is_nothrow_copy_constructible : is_nothrow_constructible<T, typename add_lvalue_reference<typename add_const<T>::type>::type> { };

  /* is_move_constructible */
  template<typename T> struct is_move_constructible : is_constructible<T, typename add_rvalue_reference<T>::type> { };
  template<typename T> struct is_trivially_move_constructible : is_trivially_constructible<T, typename add_rvalue_reference<T>::type> { };
  template<typename T> struct is_nothrow_move_constructible : is_nothrow_constructible<T, typename add_rvalue_reference<T>::type> { };

  /* is_assignable */
  template<typename T, typename U> struct is_assignable : bool_constant<__is_assignable(T, U)> { };
  template<typename T, typename U> struct is_trivially_assignable : bool_constant<__is_trivially_assignable(T, U)> { };
  template<typename T, typename U> struct is_nothrow_assignable : bool_constant<__is_nothrow_assignable(T, U)> { };

  /* is_copy_assignable */
  template<typename T> struct is_copy_assignable : is_assignable<
						   typename add_lvalue_reference<T>::type,
						   typename add_lvalue_reference<const T>::type> { };
  template<typename T> struct is_trivially_copy_assignable : is_trivially_assignable<
						   typename add_lvalue_reference<T>::type,
						   typename add_lvalue_reference<const T>::type> { };
  template<typename T> struct is_nothrow_copy_assignable : is_nothrow_assignable<
						   typename add_lvalue_reference<T>::type,
						   typename add_lvalue_reference<const T>::type> { };

  /* is_move_assignable */
  template<typename T> struct is_move_assignable : is_assignable<
						   typename add_lvalue_reference<T>::type,
						   typename add_rvalue_reference<T>::type> { };
  template<typename T> struct is_trivially_move_assignable : is_trivially_assignable<
						   typename add_lvalue_reference<T>::type,
						   typename add_rvalue_reference<T>::type> { };
  template<typename T> struct is_nothrow_move_assignable : is_nothrow_assignable<
						   typename add_lvalue_reference<T>::type,
						   typename add_rvalue_reference<T>::type> { };

  /* is_destructible */
  template<typename T> struct is_destructible : std::is_destructible<T> { };
  template<typename T> struct is_trivially_destructible : std::is_trivially_destructible<T> { };
  template<typename T> struct is_nothrow_destructible : std::is_nothrow_destructible<T> { };

  /* has_virtual_destructor */
  template<typename T> struct has_virtual_destructor : std::has_virtual_destructor<T> { }; // TODO

  /* is_swappable */
  template<typename T, typename U> struct is_swappable_with : std::is_swappable_with<T, U> { }; // TODO
  template<typename T> struct is_swappable : std::is_swappable<T> { }; // TODO
  template<typename T, typename U> struct is_nothrow_swappable_with : std::is_nothrow_swappable_with<T, U> { }; // TODO
  template<typename T> struct is_nothrow_swappable : std::is_nothrow_swappable<T> { }; // TODO


  /* -------------------------------- */
  /*         Property queries         */
  /* -------------------------------- */

  /* alignment_of */
  template<typename Type> struct alignment_of : integral_constant<size_t, alignof(Type)> { };

  /* rank */
  template<typename Type> struct rank : integral_constant<size_t, 0> { };
  template<typename Type> struct rank<Type[]> : integral_constant<size_t, rank<Type>::value + 1> { };
  template<typename Type, size_t Count> struct rank<Type[Count]> : integral_constant<size_t, rank<Type>::value + 1> { };

  /* extent */
  template<typename Type, unsigned Dimension = 0> struct extent : integral_constant<size_t, 0> { };
  template<typename Type> struct extent<Type[], 0> : integral_constant<size_t, 0> { };
  template<typename Type, unsigned Dimension> struct extent<Type[], Dimension> : extent<Type, Dimension - 1> { };
  template<typename Type, size_t Count> struct extent<Type[Count], 0> : integral_constant<size_t, Count> { };
  template<typename Type, size_t Count, unsigned Dimension> struct extent<Type[Count], Dimension> : extent<Type, Dimension - 1> { };


  /* -------------------------------- */
  /*        Type relationships        */
  /* -------------------------------- */

  /* is_same */
  template<typename T1, typename T2> struct is_same : bool_constant<__is_same(T1, T2)> { };

  /* is_base_of */
  template<typename T1, typename T2> struct is_base_of : bool_constant<__is_base_of(T1, T2)> { };


  /* is_convertible */
  template<typename A, typename B> struct is_convertible : bool_constant<
						    (decltype(detail::test_returnable<B>(0))::value &&
						    decltype(detail::test_implicitly_convertible<A, B>(0))::value) ||
						    (is_void<A>::value && is_void<B>::value)> { };
  template<typename From, typename To> struct is_nothrow_convertible : conjunction<is_void<From>, is_void<To>> { };
  template<typename From, typename To>
    requires
      requires {
	static_cast<To(*)()>(nullptr);
	{ declval<void(&)(To) noexcept>()(declval<From>()) } noexcept;
    }
  struct is_nothrow_convertible<From, To> : true_type { };


  /* -------------------------------- */
  /*    Const-volaility specifiers    */
  /* -------------------------------- */

  /* remove_cv */
  template<typename T> struct remove_cv { typedef T type; };
  template<typename T> struct remove_cv<const T> { typedef T type; };
  template<typename T> struct remove_cv<volatile T> { typedef T type; };
  template<typename T> struct remove_cv<const volatile T> { typedef T type; };

  /* remove_const */
  template<typename T> struct remove_const { typedef T type; };
  template<typename T> struct remove_const<const T> { typedef T type; };

  /* remove_volatile */
  template<typename T> struct remove_volatile { typedef T type; };
  template<typename T> struct remove_volatile<volatile T> { typedef T type; };

  /* add_cv */
  template<typename T> struct add_cv { typedef const volatile T type; };

  /* add_const */
  template<typename T> struct add_const { typedef const T type; };

  /* add_volatile */
  template<typename T> struct add_volatile { typedef volatile T type; };


  /* -------------------------------- */
  /*            References            */
  /* -------------------------------- */

  /* remove_reference */
  template<typename T> struct remove_reference { typedef T type; };
  template<typename T> struct remove_reference<T&> { typedef T type; };
  template<typename T> struct remove_reference<T&&> { typedef T type; };

  /* add_lvalue_reference */
  template<typename T> struct add_lvalue_reference : decltype(detail::try_add_lvalue_reference<T>(0)) { };

  /* add_rvalue_reference */
  template<typename T> struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) { };


  /* -------------------------------- */
  /*             Pointers             */
  /* -------------------------------- */

  /* remove_pointer */
  template<typename T> struct remove_pointer { typedef T type; };
  template<typename T> struct remove_pointer<T*> { typedef T type; };
  template<typename T> struct remove_pointer<T* const volatile> { typedef T type; };
  template<typename T> struct remove_pointer<T* const> { typedef T type; };
  template<typename T> struct remove_pointer<T* volatile> { typedef T type; };

  /* add_pointer */
  template<typename T> struct add_pointer { }; // TODO


  /* -------------------------------- */
  /*          Sign modifiers          */
  /* -------------------------------- */

  /* make_signed */
  template<typename T> struct make_signed : std::make_signed<T> { }; // TODO

  /* make_unsigned */
  template<typename T> struct make_unsigned : std::make_unsigned<T> { }; // TODO


  /* -------------------------------- */
  /*              Arrays              */
  /* -------------------------------- */

  /* remove_extent */
  template<typename T> struct remove_extent { typedef T type; };
  template<typename T> struct remove_extent<T[]> { typedef T type; };
  template<typename T, size_t N> struct remove_extent<T[N]> { typedef T type; };

  /* remove_all_extents */
  template<typename T> struct remove_all_extents { typedef T type; };
  template<typename T> struct remove_all_extents<T[]> { typedef typename remove_all_extents<T>::type type; };
  template<typename T, size_t N> struct remove_all_extents<T[N]> { typedef typename remove_all_extents<T>::type type; };


  /* -------------------------------- */
  /*  Miscellaneous transformations   */
  /* -------------------------------- */

  template<size_t L, size_t A> struct aligned_storage {
    struct type {
      alignas(A) unsigned char data[L];
    };
  };

  template<typename T>
  struct decay {
  private:
    typedef typename remove_reference<T>::type U;
  public:
    typedef typename conditional<
      is_array<U>::value,
      typename remove_extent<U>::type*,
      typename conditional<
	is_function<U>::value,
	typename add_pointer<U>::type,
	typename remove_cv<U>::type
      >::type
    >::type type;
  };

  /* conditional */
  template<bool Value, typename Type1, typename Type2> struct conditional;
  template<typename Type1, typename Type2> struct conditional<true, Type1, Type2> { using value = Type1; };
  template<typename Type1, typename Type2> struct conditional<false, Type1, Type2> { using value = Type2; };

  /* common_type */
  template<typename...> struct common_type { };
  template<typename Type> struct common_type<Type> : common_type<Type, Type> { };
  namespace detail {
    template<typename...>
    using void_t = void;
    template<typename Type1, typename Type2>
    using conditional_result_t = decltype(false ? declval<Type1>() : declval<Type2>());
    template<typename, typename, typename = void>
    struct decay_conditional_result { };
    template<typename Type1, typename Type2>
    struct decay_conditional_result<Type1, Type2, void_t<conditional_result_t<Type1, Type2>>>
      : decay<conditional_result_t<Type1, Type2>> { };
    template<typename Type1, typename Type2, typename = void>
    struct common_type_2_impl : decay_conditional_result<const Type1&, const Type2&> { };
    template<typename Type1, typename Type2>
    struct common_type_2_impl<Type1, Type2, void_t<conditional_result_t<Type1, Type2>>>
      : decay_conditional_result<Type1, Type2> { };
  }
  template<typename Type1, typename Type2> struct common_type<Type1, Type2>
    : conditional<is_same<Type1, typename decay<Type1>::type>::value &&
		  is_same<Type2, typename decay<Type2>::type>::value,
	          detail::common_type_2_impl<Type1, Type2>,
		  common_type<typename decay<Type2>::type,
		              typename decay<Type2>::type>>::type { };
  namespace detail {
    template<typename Void, typename Type1, typename Type2, typename... Rest>
    struct common_type_multi_impl { };
    template<typename Type1, typename Type2, typename... Rest>
    struct common_type_multi_impl<void_t<typename common_type<Type1, Type2>::type>, Type1, Type2, Rest...>
      : common_type<typename common_type<Type1, Type2>::type, Rest...> { };
  }
  template<typename Type1, typename Type2, typename... Rest>
  struct common_type<Type1, Type2, Rest...> : detail::common_type_multi_impl<void, Type1, Type2, Rest...> { };

  /* common_reference */
  // template<typename... Types>
  // struct common_reference 


  /* -------------------------------- */
  /*       Operations on traits       */
  /* -------------------------------- */

  /* conjunction */
  template<typename...> struct conjunction : true_type { };
  template<typename Base> struct conjunction<Base> : Base { };
  template<typename Base, typename... Bases> struct conjunction<Base, Bases...>
    : conditional<bool(Base::value), conjunction<Bases...>, Base>::type { };

  constexpr bool is_constant_evaluated() noexcept { return __builtin_is_constant_evaluated(); }

} // namespace me

#endif
