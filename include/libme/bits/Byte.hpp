#ifndef LIBME_BITS_BYTE_HPP
  #define LIBME_BITS_BYTE_HPP

namespace me {

  enum class Byte : unsigned char { };

  template<typename IntType>
  constexpr IntType to_integer(Byte val) noexcept;

  template<typename IntType> constexpr Byte& operator<<=(Byte &val, IntType shift) noexcept;
  template<typename IntType> constexpr Byte& operator>>=(Byte &val, IntType shift) noexcept;
  constexpr Byte& operator&=(Byte &lhs, Byte rhs) noexcept;
  constexpr Byte& operator|=(Byte &lhs, Byte rhs) noexcept;
  constexpr Byte& operator^=(Byte &lhs, Byte rhs) noexcept;

  template<typename IntType> constexpr Byte operator<<(Byte val, IntType shift) noexcept;
  template<typename IntType> constexpr Byte operator>>(Byte val, IntType shift) noexcept;
  constexpr Byte operator&(Byte lhs, Byte rhs) noexcept;
  constexpr Byte operator|(Byte lhs, Byte rhs) noexcept;
  constexpr Byte operator^(Byte lhs, Byte rhs) noexcept;
  constexpr Byte operator~(Byte val) noexcept;

} // namespace me
// Implementations:

template<typename IntType>
constexpr IntType
  me::to_integer(Byte val)
  noexcept
{
  return IntType(val);
}

template<typename IntType>
constexpr me::Byte&
  me::operator<<=(Byte &val, IntType shift)
  noexcept
{
  return val = val << shift;
}

template<typename IntType>
constexpr me::Byte&
  me::operator>>=(Byte &val, IntType shift)
  noexcept
{
  return val = val >> shift;
}

constexpr me::Byte&
  me::operator&=(Byte &lhs, Byte rhs)
  noexcept
{
  return lhs = lhs & rhs;
}

constexpr me::Byte&
  me::operator|=(Byte &lhs, Byte rhs)
  noexcept
{
  return lhs = lhs | rhs;
}

constexpr me::Byte&
  me::operator^=(Byte &lhs, Byte rhs)
  noexcept
{
  return lhs = lhs ^ rhs;
}

template<typename IntType>
constexpr me::Byte
  me::operator<<(Byte val, IntType shift)
  noexcept
{
  return Byte(static_cast<unsigned int>(val) << shift);
}

template<typename IntType>
constexpr me::Byte
  me::operator>>(Byte val, IntType shift)
  noexcept
{
  return Byte(static_cast<unsigned int>(val) >> shift);
}

constexpr me::Byte
  me::operator&(Byte lhs, Byte rhs)
  noexcept
{
  return Byte(static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs));
}

constexpr me::Byte
  me::operator|(Byte lhs, Byte rhs)
  noexcept
{
  return Byte(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
}

constexpr me::Byte
  me::operator^(Byte lhs, Byte rhs)
  noexcept
{
  return Byte(static_cast<unsigned int>(lhs) ^ static_cast<unsigned int>(rhs));
}

constexpr me::Byte
  me::operator~(Byte val)
  noexcept
{
  return Byte(~static_cast<unsigned int>(val));
}

#endif // LIBME_BITS_BYTE_HPP
