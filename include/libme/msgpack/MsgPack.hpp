#ifndef LIBME_MSG_PACK_HPP
  #define LIBME_MSG_PACK_HPP

#include "libme/TypeTraits.hpp"
#include "libme/Concepts.hpp"
#include "libme/String.hpp"
#include "libme/Vector.hpp"
#include "libme/Map.hpp"

namespace me {

  enum class MessagePackTypes {
    NIL,
    BOOL,
    UINT8, UINT16, UINT32, UINT64,
    INT8, INT16, INT32, INT64,
    FLOAT32, FLOAT64,
    STRING8, STRING16, STRING32,
    ARRAY8, ARRAY16, ARRAY32,
    MAP8, MAP16, MAP32,
    BIN8, BIN16, BIN32,
    EXT8, EXT16, EXT32,
    MISSING
  };

  template<typename Buffer>
  class MessagePack {

  public:

    typedef Buffer BufferType;
    using StringType = detail::StringView<char, detail::CharTraits<char>>;
    template<typename Type> using ArrayType = Vector<Type>;
    template<typename Key, typename Value> using MapType = Map<Key, Value>;

  private:

    BufferType m_buffer;

  public:

    constexpr MessagePack(const BufferType &buffer);
    constexpr MessagePack(BufferType &&buffer);

    constexpr void write(nullptr_t);
    constexpr void write(bool b);
    template<UnsignedInteger Type> constexpr void write(Type i);
    template<SignedInteger Type> constexpr void write(Type i);
    template<FloatingPoint Type> constexpr void write(Type f);
    constexpr void write(const StringType &str);
    template<typename Type> constexpr void write(const ArrayType<Type> &arr);
    template<typename Key, typename Value> constexpr void write(const MapType<Key, Value> &map);

    constexpr MessagePackTypes get_type();
    constexpr bool read_bool();
    template<typename Type = uint64_t> constexpr Type read_uint();
    template<typename Type = int64_t> constexpr Type read_int();
    template<typename Type = double> constexpr Type read_float();
    constexpr size_t read_string();
    constexpr size_t read_string(char* dest, size_t len);
    constexpr size_t read_array();
    constexpr size_t read_map();

  };

} // namespace me

/* --------------------- */
/* class me::MessagePack */
/* --------------------- */
template<typename Buffer>
constexpr me::MessagePack<Buffer>::MessagePack(const BufferType &buffer)
  : m_buffer(buffer)
{
}

template<typename Buffer>
constexpr me::MessagePack<Buffer>::MessagePack(BufferType &&buffer)
  : m_buffer(move(buffer))
{
}

/*** WRITING ***/

template<typename Buffer>
constexpr void
  me::MessagePack<Buffer>::write(nullptr_t)
{
  m_buffer << 0xC0;
}

template<typename Buffer>
constexpr void
  me::MessagePack<Buffer>::write(bool b)
{
  m_buffer << 0xC2 + b;
}

template<typename Buffer>
template<me::UnsignedInteger Type>
constexpr void
me::MessagePack<Buffer>::write(Type i)
{
  if (i <= 0x7F)
    m_buffer << static_cast<uint8_t>(i);
  if (i <= 0xFF)
    m_buffer << 0xCC << static_cast<uint8_t>(i);
  else if (i <= 0xFFFF)
    m_buffer << 0xCD << static_cast<uint16_t>(i);
  else if (i <= 0xFFFFFFFF)
    m_buffer << 0xCE << static_cast<uint32_t>(i);
  else
    m_buffer << 0xCF << static_cast<uint64_t>(i);
}

template<typename Buffer>
template<me::SignedInteger Type>
constexpr void
me::MessagePack<Buffer>::write(Type i)
{
  if (i >= 0x00 && i <= 0x7F)
    m_buffer << static_cast<int8_t>(i);
  else if (i <= 0xFF)
    m_buffer << 0xD0 << static_cast<int8_t>(i);
  else if (i <= 0xFFFF)
    m_buffer << 0xD1 << static_cast<int16_t>(i);
  else if (i <= 0xFFFFFFFF)
    m_buffer << 0xD2 << static_cast<int32_t>(i);
  else
    m_buffer << 0xD3 << static_cast<int64_t>(i);
}

template<typename Buffer>
template<me::FloatingPoint Type>
constexpr void
  me::MessagePack<Buffer>::write(Type f)
{
  // TODO:
  if (sizeof(Type) == 4)
    m_buffer << 0xCA << static_cast<float>(f);
  else
    m_buffer << 0xCB << static_cast<double>(f);
}

template<typename Buffer>
constexpr void me::MessagePack<Buffer>::write(const StringType &str)
{
  size_t len = str.length();
  if (len <= 0x1F)
    m_buffer << 0xA0 + static_cast<uint8_t>(len);
  else if (len <= 0xFF)
    m_buffer << 0xD9 << static_cast<uint8_t>(len);
  else if (len <= 0xFFFF)
    m_buffer << 0xDA << static_cast<uint16_t>(len);
  else if (len <= 0xFFFFFFFF)
    m_buffer << 0xDB << static_cast<uint32_t>(len);

  for (size_t i = 0; i != len; i++)
    m_buffer << str.at(i);
}

template<typename Buffer>
template<typename Type>
constexpr void me::MessagePack<Buffer>::write(const ArrayType<Type> &arr)
{
  size_t len = arr.length();
  if (len <= 0x0F)
    m_buffer << 0x90 + static_cast<uint8_t>(len);
  else if (len <= 0xFFFF)
    m_buffer << 0xDC << static_cast<uint16_t>(len);
  else if (len <= 0xFFFFFFFF)
    m_buffer << 0xDD << static_cast<uint32_t>(len);

  for (size_t i = 0; i != len; i++)
    write(arr.at(i));
}

template<typename Buffer>
template<typename Key, typename Value>
constexpr void me::MessagePack<Buffer>::write(const MapType<Key, Value> &map)
{
  size_t len = map.length();
  if (len <= 0x0F)
    m_buffer << 0x80 + static_cast<uint8_t>(len);
  else if (len <= 0xFFFF)
    m_buffer << 0xDE + static_cast<uint16_t>(len);
  else if (len <= 0xFFFFFFFF)
    m_buffer << 0xDF + static_cast<uint32_t>(len);

  for (const auto &[key, value] : map)
  {
    write(key);
    write(value);
  }
}

/*** READING ***/

template<typename Buffer>
constexpr me::MessagePackTypes
  me::MessagePack<Buffer>::get_type()
{
  uint8_t dat = m_buffer.read();

  if (dat <= 0x7F)
    return MessagePackTypes::UINT8;
  if (dat <= 0x8F)
    return MessagePackTypes::MAP8;
  if (dat <= 0x9F)
    return MessagePackTypes::ARRAY8;
  if (dat <= 0xBF)
    return MessagePackTypes::STRING8;
  if (dat >= 0xE0)
    return MessagePackTypes::INT8;

  switch (dat)
  {
    case 0xC0:
      return MessagePackTypes::NIL;
    case 0xC2:
    case 0xC3:
      return MessagePackTypes::BOOL;
    case 0xC4:
      return MessagePackTypes::BIN8;
    case 0xC5:
      return MessagePackTypes::BIN16;
    case 0xC6:
      return MessagePackTypes::BIN32;
    case 0xC7:
      return MessagePackTypes::EXT8;
    case 0xC8:
      return MessagePackTypes::EXT16;
    case 0xC9:
      return MessagePackTypes::EXT32;
    case 0xCA:
      return MessagePackTypes::FLOAT32;
    case 0xCB:
      return MessagePackTypes::FLOAT64;
    case 0xCC:
      return MessagePackTypes::UINT8;
    case 0xCD:
      return MessagePackTypes::UINT16;
    case 0xCE:
      return MessagePackTypes::UINT32;
    case 0xCF:
      return MessagePackTypes::UINT64;
    case 0xD0:
      return MessagePackTypes::INT8;
    case 0xD1:
      return MessagePackTypes::INT16;
    case 0xD2:
      return MessagePackTypes::INT32;
    case 0xD3:
      return MessagePackTypes::INT64;
    case 0xD9:
      return MessagePackTypes::STRING8;
    case 0xDA:
      return MessagePackTypes::STRING16;
    case 0xDB:
      return MessagePackTypes::STRING32;
    case 0xDC:
      return MessagePackTypes::ARRAY16;
    case 0xDD:
      return MessagePackTypes::ARRAY32;
    case 0xDE:
      return MessagePackTypes::MAP16;
    case 0xDF:
      return MessagePackTypes::MAP32;
    default:
      return MessagePackTypes::MISSING;
  }
}

template<typename Buffer>
constexpr bool
  me::MessagePack<Buffer>::read_bool()
{
  uint8_t dat = m_buffer.read();
  return dat == 0xC3;
}

template<typename Buffer>
template<typename Type>
constexpr Type
  me::MessagePack<Buffer>::read_uint()
{
  uint8_t type = m_buffer.read();
  if (type <= 0x7F)
    return type;

  switch (type)
  {
    case 0xCC:
      return static_cast<Type>(m_buffer.template read<uint8_t>());
    case 0xCD:
      return static_cast<Type>(m_buffer.template read<uint16_t>());
    case 0xCE:
      return static_cast<Type>(m_buffer.template read<uint32_t>());
    case 0xCF:
      return static_cast<Type>(m_buffer.template read<uint64_t>());
    default:
      return 0;
  }
}

template<typename Buffer>
template<typename Type>
constexpr Type
  me::MessagePack<Buffer>::read_int()
{
  uint8_t type = m_buffer.read();
  if (type >= 0xE0)
    return static_cast<Type>(static_cast<int8_t>(type));

  switch (type)
  {
    case 0xD0:
      return static_cast<Type>(m_buffer.template read<int8_t>());
    case 0xD1:
      return static_cast<Type>(m_buffer.template read<int16_t>());
    case 0xD2:
      return static_cast<Type>(m_buffer.template read<int32_t>());
    case 0xD3:
      return static_cast<Type>(m_buffer.template read<int64_t>());
    default:
      return Type(0);
  }
}

template<typename Buffer>
template<typename Type>
constexpr Type
  me::MessagePack<Buffer>::read_float()
{
  uint8_t type = m_buffer.read();
  if (type == 0xCA)
    return static_cast<Type>(m_buffer.template read<float>());
  if (type == 0xCB)
    return static_cast<Type>(m_buffer.template read<double>());
  return Type(0);
}

template<typename Buffer>
constexpr size_t
  me::MessagePack<Buffer>::read_string()
{
  uint8_t type = m_buffer.read();
  if (type >= 0xA0 && type <= 0xBF)
    return type - 0xA0;

  switch (type)
  {
    case 0xD9:
      return m_buffer.template read<uint8_t>();
    case 0xDA:
      return m_buffer.template read<uint16_t>();
    case 0xDB:
      return m_buffer.template read<uint32_t>();
    default:
      return 0;
  }
}

template<typename Buffer>
constexpr size_t
  me::MessagePack<Buffer>::read_string(char* dest, size_t len)
{
  for (size_t i = 0; i != len; i++)
    dest[i] = m_buffer.template read<char>();
  return len;
}

template<typename Buffer>
constexpr size_t
  me::MessagePack<Buffer>::read_array()
{
  uint8_t type = m_buffer.read();
  if (type >= 0x90 && type <= 0x9F)
    return type - 0x90;

  switch (type)
  {
    case 0xDC:
      return m_buffer.template read<uint16_t>();
    case 0xDD:
      return m_buffer.template read<uint32_t>();
    default:
      return 0;
  }
}

template<typename Buffer>
constexpr size_t
  me::MessagePack<Buffer>::read_map()
{
  uint8_t type = m_buffer.read();
  if (type >= 0x80 && type <= 0x8F)
    return type - 0x80;

  switch (type)
  {
    case 0xDE:
      return m_buffer.template read<uint16_t>();
    case 0xDF:
      return m_buffer.template read<uint32_t>();
    default:
      return 0;
  }
}
/* end class me::MessagePack */

#endif // LIBME_MSG_PACK_HPP
