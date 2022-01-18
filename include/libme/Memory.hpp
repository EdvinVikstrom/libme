#ifndef LIBME_MEMORY_HPP
  #define LIBME_MEMORY_HPP

#include "libme/TypeTraits.hpp"
#include "libme/Utility.hpp"
#include "libme/Iterator.hpp"

namespace me {

  template<typename Ptr> struct PointerTraits;
  template<typename T> struct PointerTraits<T*>;

  template<typename T>
  constexpr T* to_address(T* ptr) noexcept;

  template<typename Ptr>
  constexpr auto to_address(const Ptr &ptr) noexcept;

  void* align(size_t alignment, size_t size, void* &ptr, size_t &space);

  template<size_t N, typename T>
  [[nodiscard]] constexpr T* assume_aligned(T* ptr);

  template<typename T>
  constexpr T* addressof(T &val) noexcept;

  template<typename T>
  const T* addressof(T &&val) = delete;

  template<typename I>
  concept NothrowInputIterator = true; // TODO

  template<typename I>
  concept NothrowForwardIterator = true; // TODO

  template<typename S, typename I>
  concept NothrowSentinelFor = true; // TODO

  template<typename R>
  concept NothrowInputRange = true; // TODO

  template<typename R>
  concept NothrowForwardRange = true; // TODO

  template<typename NoThrowForwardIterator>
  void uninitialized_default_construct(NoThrowForwardIterator first, NoThrowForwardIterator last);

  template<typename ExecutionPolicy, typename NoThrowForwardIterator>
  void uninitialized_default_construct(ExecutionPolicy &&exec, NoThrowForwardIterator first, NoThrowForwardIterator last);

  template<typename NoThrowForwardIterator, typename Size>
  NoThrowForwardIterator uninitialized_default_construct_n(NoThrowForwardIterator first, Size num);

  template<typename ExecutionPolicy, typename NoThrowForwardIterator, typename Size>
  NoThrowForwardIterator uninitialized_default_construct_n(ExecutionPolicy &&exec, NoThrowForwardIterator first, Size num);

  namespace ranges {

    template<NothrowForwardIterator I, NothrowSentinelFor<I> S>
      requires DefaultInitializable<IterValue_T<I>>
    I uninitialized_default_construct(I first, S last);

    template<NothrowForwardRange R>
      requires DefaultInitializable<RangeValue_T<R>>
    I uninitialized_default_construct(I first, S last);

  }

} // namespace me
// Implementations:

#endif // LIBME_MEMORY_HPP
