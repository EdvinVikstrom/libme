#ifndef LIBME_IO_STREAM_HPP
  #define LIBME_IO_STREAM_HPP

#include "libme/Type.hpp"

namespace me {

  enum class IOStreamModes {
    READ, WRITE
  };

  class IOStream {

  public:

    using Modes = IOStreamModes;

  public:

    virtual Modes get_mode() const = 0;
    virtual bool is_big_endian() const = 0;
    virtual size_t get_position() const = 0;

    virtual void flip() = 0;
    virtual void reserve(size_t len) = 0;

    virtual void write(uint8_t dat) = 0;
    virtual void write(uint16_t dat) = 0;
    virtual void write(uint32_t dat) = 0;
    virtual void write(uint64_t dat) = 0;
    virtual void write(float dat) = 0;
    virtual void write(double dat) = 0;

    virtual uint8_t read() = 0;
    virtual uint16_t read16() = 0;
    virtual uint32_t read32() = 0;
    virtual uint64_t read64() = 0;
    virtual float readf32() = 0;
    virtual double readf64() = 0;

    IOStream& operator<<(auto dat);
    IOStream& operator>>(uint8_t &dat);
    IOStream& operator>>(uint16_t &dat);
    IOStream& operator>>(uint32_t &dat);
    IOStream& operator>>(uint64_t &dat);
    IOStream& operator>>(float &dat);
    IOStream& operator>>(double &dat);

  };

} // namespace me

/* ------------------ */
/* class me::IOStream */
/* ------------------ */
inline me::IOStream&
  me::IOStream::operator<<(auto dat)
{
  write(dat);
  return *this;
}

inline me::IOStream&
  me::IOStream::operator>>(uint8_t &dat)
{
  dat = read();
  return *this;
}

inline me::IOStream&
  me::IOStream::operator>>(uint16_t &dat)
{
  dat = read16();
  return *this;
}

inline me::IOStream&
  me::IOStream::operator>>(uint32_t &dat)
{
  dat = read32();
  return *this;
}

inline me::IOStream&
  me::IOStream::operator>>(uint64_t &dat)
{
  dat = read64();
  return *this;
}

inline me::IOStream&
  me::IOStream::operator>>(float &dat)
{
  dat = readf32();
  return *this;
}

inline me::IOStream&
  me::IOStream::operator>>(double &dat)
{
  dat = readf64();
  return *this;
}
/* end class me::IOStream */

#endif // LIBME_IO_STREAM_HPP
