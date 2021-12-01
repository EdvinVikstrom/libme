#ifndef LIBME_CONTAINER_HPP
  #define LIBME_CONTAINER_HPP

#include "type.hpp"

namespace me {

  template<typename T>
  class Container {

  public:

    typedef size_t Size;
    typedef T Type;
    typedef Type* Iterator;
    typedef const Type* ConstIterator;

    static constexpr Size npos = ~0;

  protected:

    [[nodiscard]] virtual constexpr ConstIterator __begin() const = 0;
    [[nodiscard]] virtual constexpr ConstIterator __end() const = 0;
    [[nodiscard]] virtual constexpr const Type& __at(Size pos) const = 0;
    [[nodiscard]] virtual constexpr Size __size() const = 0;

  public:

    [[nodiscard]] constexpr bool contains(const Type &value) const;
    [[nodiscard]] constexpr Size count(const Type &value) const;
    [[nodiscard]] constexpr Size find(const Type &value) const;
    [[nodiscard]] constexpr Size rfind(const Type &value) const;

  };

}

template<typename T>
constexpr bool me::Container<T>::contains(const Type &value) const
{
  for (ConstIterator i = __begin(); i != __end(); i++)
  {
    if (*i == value)
      return true;
  }
  return false;
}

template<typename T>
constexpr me::size_t me::Container<T>::count(const Type &value) const
{
  Size count = 0;
  for (ConstIterator i = __begin(); i != __end(); i++)
  {
    if (*i == value)
      count++;
  }
  return count;
}

template<typename T>
constexpr me::size_t me::Container<T>::find(const Type &value) const
{
  for (Size i = 0; i != __size(); i++)
  {
    if (__at(i) == value)
      return i;
  }
  return npos;
}

template<typename T>
constexpr me::size_t me::Container<T>::rfind(const Type &value) const
{
  Size i = __size();
  while (i)
  {
    if (__at(i-- - 1) == value)
      return i;
  }
  return npos;
}

#endif
