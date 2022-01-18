#ifndef LIBME_IO_DATA_STREAM_HPP
  #define LIBME_IO_DATA_STREAM_HPP

#include "libme/IOStream.hpp"
#include "libme/Allocator.hpp"

namespace me {

  template<bool Dynamic = false, typename Alloc = DefaultAllocator<uint8_t>>
  class IODataStream : public IOStream {

  private:

    uint8_t* m_buffer;
    size_t m_length;
    size_t m_pos;
    bool m_big_endian;
    Modes m_mode;

  public:

    constexpr IODataStream(uint8_t* buf, size_t len, bool big_endian = false, Modes mode = Modes::READ);
    constexpr IODataStream(size_t len, bool big_endian = false);
    constexpr IODataStream(bool big_endian = false)
      requires Dynamic;

    constexpr void require(size_t len);

    Modes get_mode() const override;
    bool is_big_endian() const override;
    size_t get_position() const override;

    constexpr void flip() override;
    constexpr void reserve(size_t len) override;

    constexpr void write(uint8_t dat) override;
    constexpr void write(uint16_t dat) override;
    constexpr void write(uint32_t dat) override;
    constexpr void write(uint64_t dat) override;
    constexpr void write(float dat) override;
    constexpr void write(double dat) override;

    constexpr uint8_t read() override;
    constexpr uint16_t read16() override;
    constexpr uint32_t read32() override;
    constexpr uint64_t read64() override;
    constexpr float readf32() override;
    constexpr double readf64() override;

  };

} // namespace me

/* ---------------------- */
/* class me::IODataStream */
/* ---------------------- */
template<bool Dynamic, typename Alloc>
constexpr me::IODataStream<Dynamic, Alloc>::IODataStream(uint8_t* buf, size_t len, bool big_endian, Modes mode)
  : m_buffer(buf), m_length(len), m_pos(0), m_big_endian(big_endian), m_mode(mode)
{
}

template<bool Dynamic, typename Alloc>
constexpr me::IODataStream<Dynamic, Alloc>::IODataStream(size_t len, bool big_endian)
{
  m_buffer = Alloc::allocate(len);
  m_length = len;
  m_pos = 0;
  m_big_endian = big_endian;
  m_mode = Modes::WRITE;
}

template<bool Dynamic, typename Alloc>
constexpr me::IODataStream<Dynamic, Alloc>::IODataStream(bool big_endian)
  requires Dynamic
{
  m_buffer = nullptr;
  m_length = 0;
  m_pos = 0;
  m_big_endian = big_endian;
  m_mode = Modes::WRITE;
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::require(size_t len)
{
  if (m_pos + len <= m_length)
    return;

  if constexpr (Dynamic)
    reserve(m_length + len);
  else {}
    // TODO: throw an error
}

template<bool Dynamic, typename Alloc>
me::IOStream::Modes
  me::IODataStream<Dynamic, Alloc>::get_mode() const
{
  return m_mode;
}

template<bool Dynamic, typename Alloc>
bool
  me::IODataStream<Dynamic, Alloc>::is_big_endian() const
{
  return m_big_endian;
}

template<bool Dynamic, typename Alloc>
me::size_t
  me::IODataStream<Dynamic, Alloc>::get_position() const
{
  return m_pos;
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::flip()
{
  m_mode = (m_mode == Modes::WRITE ? Modes::READ : Modes::WRITE);
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::reserve(size_t len)
{
  LIBME_ASSERT(Dynamic, "me::IODataStream::reserve(): cannot reserve on a non-dynamic data stream");

  if (len > m_length)
  {
    uint8_t* new_buffer = Alloc::allocate(len);
    for (size_t i = 0; i != m_pos; i++)
      new_buffer[i] = m_buffer[i];
    Alloc::deallocate(m_buffer);
    m_buffer = new_buffer;
    m_length = len;
  }
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::write(uint8_t dat)
{
  require(1);
  m_buffer[m_pos++] = dat;
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::write(uint16_t dat)
{
  require(2);
  if (m_big_endian)
  {
  }else
  {
    m_buffer[m_pos] = (dat >> 8) & 0xFF;
    m_buffer[m_pos + 1] = dat & 0xFF;
    m_pos += 2;
  }
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::write(uint32_t dat)
{
  require(4);
  if (m_big_endian)
  {
  }else
  {
    m_buffer[m_pos] = (dat >> 24) & 0xFF;
    m_buffer[m_pos + 1] = (dat >> 16) & 0xFF;
    m_buffer[m_pos + 2] = (dat >> 8) & 0xFF;
    m_buffer[m_pos + 3] = dat & 0xFF;
    m_pos += 4;
  }
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::write(uint64_t dat)
{
  require(8);
  if (m_big_endian)
  {
  }else
  {
    m_buffer[m_pos] = (dat >> 56) & 0xFF;
    m_buffer[m_pos + 1] = (dat >> 48) & 0xFF;
    m_buffer[m_pos + 2] = (dat >> 40) & 0xFF;
    m_buffer[m_pos + 3] = (dat >> 32) & 0xFF;
    m_buffer[m_pos + 4] = (dat >> 24) & 0xFF;
    m_buffer[m_pos + 5] = (dat >> 16) & 0xFF;
    m_buffer[m_pos + 6] = (dat >> 8) & 0xFF;
    m_buffer[m_pos + 7] = dat & 0xFF;
    m_pos += 8;
  }
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::write(float dat)
{
  require(4);
  m_pos += 4; // TODO
}

template<bool Dynamic, typename Alloc>
constexpr void
  me::IODataStream<Dynamic, Alloc>::write(double dat)
{
  require(8);
  m_pos += 8; // TODO
}
/* end class me::IODataStream */

#endif // LIBME_IO_DATA_STREAM_HPP
