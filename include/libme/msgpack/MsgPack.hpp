#ifndef LIBME_MSG_PACK_HPP
  #define LIBME_MSG_PACK_HPP

#include "libme/TypeTraits.hpp"
#include "libme/String.hpp"
#include "libme/Vector.hpp"
#include "libme/Map.hpp"

namespace me {

  template<typename Buffer>
  class MessagePack {

  public:

    typedef Buffer BufferType;
    template<typename Type> using StringType = detail::StringView<Type, detail::CharTraits<Type>>;
    template<typename Type> using ArrayType = Vector<Type>;
    template<typename Key, typename Value> using MapType = Map<Key, Value>;

  private:

    BufferType m_buffer;

  public:

    constexpr MessagePack(const BufferType &buffer);
    constexpr MessagePack(BufferType &&buffer);

    constexpr void write(bool b);
    template<typename Type> constexpr void write(Type i)
      requires is_integral<Type>::value && is_unsigned<Type>::value;
    template<typename Type> constexpr void write(Type i)
      requires is_integral<Type>::value && is_signed<Type>::value;
    template<typename Type> constexpr void write(Type f)
      requires is_floating_point<Type>::value;
    template<typename Type> constexpr void write(const StringType<Type> &str);
    template<typename Type> constexpr void write(const ArrayType<Type> &arr);
    template<typename Key, typename Value> constexpr void write(const MapType<Key, Value> &map);

    constexpr bool read_bool();
    constexpr uint8_t read_uint8();
    constexpr uint16_t read_uint16();
    constexpr uint32_t read_uint32();
    constexpr uint64_t read_uint64();
    constexpr uint8_t read_int8();
    constexpr uint16_t read_int16();
    constexpr uint32_t read_int32();
    constexpr uint64_t read_int64();
    constexpr float read_float32();
    constexpr double read_float64();
    template<typename Type> constexpr void read_data(Type* dest);

    constexpr size_t len_string();
    constexpr size_t len_array();
    constexpr size_t len_map();

  };

}

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

template<typename Buffer>
constexpr void
  me::MessagePack<Buffer>::write(bool b)
{
  m_buffer << 0xC2 + b;
}

template<typename Buffer>
template<typename Type>
constexpr void
me::MessagePack<Buffer>::write(Type i)
  requires is_integral<Type>::value && is_unsigned<Type>::value
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
template<typename Type>
constexpr void
me::MessagePack<Buffer>::write(Type i)
  requires is_integral<Type>::value && is_signed<Type>::value
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
template<typename Type>
constexpr void me::MessagePack<Buffer>::write(Type f)
  requires is_floating_point<Type>::value
{
  // TODO:
  if (sizeof(Type) == 4)
    m_buffer << 0xCA << static_cast<float>(f);
  else
    m_buffer << 0xCB << static_cast<double>(f);
}

template<typename Buffer>
template<typename Type>
constexpr void me::MessagePack<Buffer>::write(const StringType<Type> &str)
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

#endif
