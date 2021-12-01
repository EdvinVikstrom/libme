#ifndef LIBME_FORMAT_SINK_HPP
  #define LIBME_FORMAT_SINK_HPP

#include <stdio.h>

namespace me::format {

  template<typename Char>
  class Sink {

  public:

    using CharType = Char;

    virtual void write(Char chr) = 0;
    virtual void write(const Char* str) = 0;
    virtual void write(const Char* begin, const Char* end) = 0;
    virtual void flush() = 0;

  };

  template<typename Char>
  class StringSink final : public Sink<Char> {

  private:

    Char* buffer_;

  public:

    using CharType = Char;

    StringSink(Char* buffer)
      : buffer_(buffer)
    {
    }

    void write(Char chr) override
    {
      *buffer_++ = chr;
    }

    void write(const Char* str) override
    {
      while (*str != Char('\0'))
	*buffer_++ = *str++;
    }

    void write(const Char* begin, const Char* end) override
    {
      while (begin != end)
	*buffer_++ = *begin++;
    }

    void flush() override
    {
    }

  };

  template<typename Char>
  class FileSink final : public Sink<Char> {

  private:

    FILE* file_;

  public:

    using CharType = Char;

    FileSink(FILE* file)
      : file_(file)
    {
    }

    void write(Char chr) override
    {
      fputc(chr, file_);
    }

    void write(const Char* str) override
    {
      fputs(str, file_);
    }

    void write(const Char* begin, const Char* end) override
    {
      fwrite(begin, sizeof(Char), end - begin, file_);
    }

    void flush() override
    {
      fflush(file_);
    }

  };

}

#endif
