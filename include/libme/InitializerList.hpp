#ifndef LIBME_INITIALIZER_LIST_HPP
  #define LIBME_INITIALIZER_LIST_HPP

#include "libme/Type.hpp"

namespace me {

  template<typename E>
  class InitializerList {

  /* Types */
  public:

    using ValueType = E;
    using Reference = const E&;
    using ConstReference = const E&;
    using SizeType = size_t;

    using Iterator = const E*;
    using ConstIterator = const E*;

  /* Variables */
  private:

    ValueType* m_data;
    SizeType m_length;

  /* Functions */
  public:

    constexpr InitializerList() noexcept;

    constexpr SizeType length() const noexcept;
    constexpr Iterator begin() const noexcept;
    constexpr Iterator end() const noexcept;

  };

  template<typename E>
  constexpr typename InitializerList<E>::Iterator begin(InitializerList<E> list) noexcept;

  template<typename E>
  constexpr typename InitializerList<E>::Iterator end(InitializerList<E> list) noexcept;

} // namespace me
// Implementations:

/* class me::InitializerList */

template<typename E>
constexpr me::InitializerList<E>::InitializerList()
  noexcept
{
}

template<typename E>
constexpr typename me::InitializerList<E>::SizeType
  me::InitializerList<E>::length() const
  noexcept
{
  return m_length;
}

template<typename E>
constexpr typename me::InitializerList<E>::Iterator
  me::InitializerList<E>::begin() const
  noexcept
{
  return m_data;
}

template<typename E>
constexpr typename me::InitializerList<E>::Iterator
  me::InitializerList<E>::end() const
  noexcept
{
  return m_data + m_length;
}

/* end class me::InitializerList */

template<typename E>
constexpr typename me::InitializerList<E>::Iterator
  me::begin(InitializerList<E> list)
  noexcept
{
  return list.begin();
}

template<typename E>
constexpr typename me::InitializerList<E>::Iterator
  me::end(InitializerList<E> list)
  noexcept
{
  return list.end();
}

#endif // LIBME_INITIALIZER_LIST_HPP
