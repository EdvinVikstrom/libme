#ifndef LIBME_ARRAY_PROXY_HPP
  #define LIBME_ARRAY_PROXY_HPP

#include "array.hpp"
#include "container.hpp"

namespace me {

  template<typename T>
  struct ArrayProxy : public Container<T> {

  public:

    using Size = typename Container<T>::Size;
    using Type = typename Container<T>::Type;
    using Iterator = typename Container<T>::Iterator;
    using ConstIterator = typename Container<T>::ConstIterator;

    static constexpr Size npos = Container<T>::npos;

  protected:

    constexpr ConstIterator __begin() const override;
    constexpr ConstIterator __end() const override;
    constexpr const Type& __at(Size pos) const override;
    constexpr Size __size() const override;

  public:

    constexpr void reserve(Size cap);

    constexpr Type& at(Size pos);
    constexpr const Type& at(Size pos) const;

    constexpr Size size() const;
    constexpr bool is_empty() const;

  };

}

template<typename T>
constexpr typename me::ArrayProxy<T>::ConstIterator me::ArrayProxy<T>::__begin() const
{
}

template<typename T>
constexpr typename me::ArrayProxy<T>::ConstIterator me::ArrayProxy<T>::__end() const
{
}

template<typename T>
constexpr const typename me::ArrayProxy<T>::Type& me::ArrayProxy<T>::__at(Size pos) const
{
}

template<typename T>
constexpr typename me::ArrayProxy<T>::Size me::ArrayProxy<T>::__size() const
{
}

#endif
