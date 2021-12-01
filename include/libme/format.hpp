#ifndef LIBME_FORMAT_HPP
  #define LIBME_FORMAT_HPP

#include "format/util.hpp"
#include "format/sink.hpp"
#include "format/param.hpp"

#include "cstring.hpp"
#include "exception.hpp"
#include "utility.hpp"
#include "string.hpp"

#include <type_traits>

namespace me::format {

  template<typename Char>
  constexpr void parse_standard_options(Options &options,
      const Char* &iter, const Char* end);

  template<typename Sink, size_t ParamCount>
  constexpr void parse_options(const Param<Sink>* &param, Options &options,
      const typename Sink::CharType* &iter, const typename Sink::CharType* end,
      const Param<Sink>* params);

  template<typename Sink, typename... Args>
  constexpr void print_to_sink(Sink &sink, const StringView_T<typename Sink::CharType> &format, const Args&... args);

  template<typename Char, typename... Args>
  constexpr void print(Char* buffer, const StringView_T<Char> &format, const Args&... args);

  template<typename Char, typename... Args>
  constexpr void print(FILE* file, const StringView_T<Char> &format, const Args&... args);


  template<typename... Args>
  constexpr void print(StringView::CharType* buffer, const StringView &format, const Args&... args)
  { print<StringView::CharType>(buffer, format, args...); }

  template<typename... Args>
  constexpr void print(FILE* file, const StringView &format, const Args&... args)
  { print<StringView::CharType>(file, format, args...); }

  template<typename... Args>
  constexpr void print(WStringView::CharType* buffer, const WStringView &format, const Args&... args)
  { print<WStringView::CharType>(buffer, format, args...); }

  template<typename... Args>
  constexpr void print(FILE* file, const WStringView &format, const Args&... args)
  { print<WStringView::CharType>(file, format, args...); }

}

template<typename Char>
constexpr void me::format::parse_standard_options(Options &options,
    const Char* &iter, const Char* end)
{
  while (iter != end)
  {
    if (*iter == Char('}'))
      break;

    if (is_digit(*iter))
      options.width_ = read_int(iter);
    else if (read_if(iter, '<'))
      options.padding_ = '<';
    else if (read_if(iter, '^'))
      options.padding_ = '^';
    else if (read_if(iter, '>'))
      options.padding_ = '>';
    else if (read_if(iter, '+'))
      options.sign_ = '+';
    else if (read_if(iter, ' '))
      options.sign_ = ' ';
    else if (read_if(iter, '_'))
      options.case_ = '_';
    else if (read_if(iter, '!'))
      options.case_ = '!';
  }
}

template<typename Sink, size_t ParamCount>
constexpr void me::format::parse_options(const Param<Sink>* &param, Options &options,
    const typename Sink::CharType* &iter, const typename Sink::CharType* end,
    const Param<Sink>* params)
{
  using Char = typename Sink::CharType;

  while (iter != end)
  {
    if (*iter == Char('}'))
      break;

    if (is_digit(*iter))
      param = &params[read_int(iter)];
    else if (is_letter(*iter))
    {
      const StringView_T identifier(iter, read_identifier(iter));
      for (size_t i = 0; i != ParamCount; i++)
      {
	if (params[i].value_.is_named() && identifier == params[i].value_.get_name())
	{
	  param = &params[i];
	  break;
	}
      }
    }else if (read_if(iter, Char(':')))
    {
      parse_standard_options(options, iter, end);
      break;
    }
    else
      throw RuntimeError("me::format::parse_options(...) unknown option '%c'", *iter);
  }
  iter++;
}

template<typename Sink, typename... Args>
constexpr void me::format::print_to_sink(Sink &sink, const StringView_T<typename Sink::CharType> &format, const Args&... args)
{
  using Char = typename Sink::CharType;

  constexpr size_t param_count = sizeof...(Args);
  Param<Sink> params[param_count] {args...};
  size_t param_index = 0;
  const Char* iter = format.begin();

  while (iter != format.end())
  {
    const Char* loc = reinterpret_cast<const Char*>(::memchr(iter, Char('{'), format.end() - iter));
    if (!loc)
      return sink.write(iter, format.end());
    sink.write(iter, loc);

    iter = loc + 1;

    const Param<Sink>* param = &params[param_index++];
    Options options;
    parse_options<Sink, param_count>(param, options, iter, format.end(), params);
    param->value_.execute(sink, options);
  }
}

template<typename Char, typename... Args>
constexpr void me::format::print(Char* buffer, const StringView_T<Char> &format, const Args&... args)
{
  StringSink<Char> sink(buffer);
  print_to_sink(sink, format, args...);
  sink.write(Char('\0'));
  sink.flush();
}

template<typename Char, typename... Args>
constexpr void me::format::print(FILE* file, const StringView_T<Char> &format, const Args&... args)
{
  FileSink<Char> sink(file);
  print_to_sink(sink, format, args...);
  sink.write(Char('\0'));
  sink.flush();
}

#endif
