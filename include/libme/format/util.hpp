#ifndef LIBME_FORMAT_UTIL_HPP
  #define LIBME_FORMAT_UTIL_HPP

#include "../type.hpp"
#include "../utility.hpp"
#include "../template/string_util.hpp"
#include "options.hpp"

namespace me::format {

  template<typename Sink, typename Type>
  struct Formatter {
    static void write(Sink &sink, const Options &options, const void* value)
    {
      sink.write('?');
      (void) options;
      (void) value;
    }
  };

  template<typename Char>
  constexpr int read_int(const Char* &iter)
  {
    int i = 0;
    while (is_digit(*iter))
      i = 10 * i + *iter++ - '0';
    return i;
  };

  template<typename Char>
  constexpr const Char* read_identifier(const Char* &iter)
  {
    const Char* end = iter;
    while (is_letter(*iter))
      end = iter++;
    return end + 1;
  };


  template<typename Char>
  constexpr bool read_if(const Char* &iter, Char chr)
  {
    if (*iter == chr)
    {
      iter++;
      return true;
    }
    return false;
  }

  template<typename Sink>
  void options_write(Sink &sink, const Options &options, const typename Sink::CharType* begin, const typename Sink::CharType* end)
  {
    size_t len = end - begin;

    auto write_case_fn = [&]() -> void
    {
      if (options.case_ == '_')
      {
        while (begin != end)
	  sink.write(lowercase(*begin++));
      }else if (options.case_ == '!')
      {
        while (begin != end)
          sink.write(uppercase(*begin++));
      }else
        sink.write(begin, end);
    };

    auto write_padding_fn = [&]() -> void
    {
      int pad = options.width_ - static_cast<int>(len);
      if (pad > 0)
      {
  	if (options.padding_ == '<')
  	{
	  while (pad--)
	    sink.write(options.padding_char_);
	  write_case_fn();
  	}else if (options.padding_ == '>')
  	{
	  write_case_fn();
	  while (pad--)
	    sink.write(options.padding_char_);
  	}else if (options.padding_ == '^')
  	{
	  int pad2 = pad / 2;
	  pad /= 2;
	  while (pad--)
	    sink.write(options.padding_char_);
          write_case_fn();
	  while (pad2--)
	    sink.write(options.padding_char_);
  	}
      }else
	write_case_fn();
    };

    write_padding_fn();
  }

}

#endif
