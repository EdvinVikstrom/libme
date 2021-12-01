#ifndef LIBME_NODE_HANDLE_HPP
  #define LIBME_NODE_HANDLE_HPP

#include "libme/PointerTraits.hpp"
#include "libme/Allocator.hpp"

namespace me {

  template<typename Type, typename Alloc>
  class __NodeHandle {

  public:

    typedef AllocatorTraits<Type, Alloc> Traits;
    typedef rebind_pointer<typename Traits::VoidPointer, Type> Pointer;

  private:

    Pointer m_pointer;

  public:

    constexpr __NodeHandle(__NodeHandle &&handle) noexcept;
    constexpr __NodeHandle(const __NodeHandle &handle) = delete;
    constexpr __NodeHandle& operator=(__NodeHandle &&handle);
    constexpr __NodeHandle& operator=(const __NodeHandle &handle) = delete;
    constexpr ~__NodeHandle();
    [[nodiscard]] constexpr bool is_empty() const noexcept;
    constexpr explicit operator bool() const noexcept;

  };

} // namespace me

#endif
