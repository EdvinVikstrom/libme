#ifndef LIBME_ITERATOR_HPP
  #define LIBME_ITERATOR_HPP

#include "type.hpp"

namespace me {

  template<typename T>
  class Iterator {

  public:

    typedef size_t Size;
    typedef T Type;
    typedef T* Position;

  private:

    Position m_pos;
    Position m_end;

  public:

    constexpr Iterator(Position begin, Position end);

    constexpr Type& next();
    constexpr Type& next(Type &condition);

    constexpr Type& get() const;

    constexpr Type& operator++();
    constexpr Type& operator+=(Size count);

    constexpr operator bool() const;
    constexpr Type& operator->() const;

  };

}

template<typename T>
constexpr me::Iterator<T>::Iterator(Position begin, Position end)
  : m_pos(begin), m_end(end)
{
}

template<typename T>
constexpr typename me::Iterator<T>::Type& me::Iterator<T>::operator++()
{
  m_pos++;
}

template<typename T>
constexpr typename me::Iterator<T>::Type& me::Iterator<T>::operator+=(Size count)
{
  m_pos += count;
}

template<typename T>
constexpr me::Iterator<T>::operator bool() const
{
  return m_pos < m_end;
}

template<typename T>
constexpr bool me::Iterator<T>::operator==(const Type &val) const
{
  return *m_pos == val;
}

template<typename T>
constexpr bool me::Iterator<T>::operator!=(const Type &val) const
{
  return *m_pos != val;
}

template<typename T>
constexpr typename me::Iterator<T>::Type& me::Iterator<T>::operator+(Size off) const
{
  return *(m_pos + off);
}

template<typename T>
constexpr typename me::Iterator<T>::Type& me::Iterator<T>::operator->() const
{
  return *m_pos;
}

#endif
