#ifndef LIBME_FORMAT_PARAM_HPP
  #define LIBME_FORMAT_PARAM_HPP

#include "util.hpp"
#include "../cstring.hpp"

namespace me::format {

  template<typename Type>
  struct NamedParam {

    const char* name_;
    const Type value_;

    NamedParam(const char* name, const Type &value)
      : name_(name), value_(value)
    {
    }

  };

  template<typename Sink>
  class ParamValue {

  public:

    using Char = typename Sink::CharType;

    enum class Type {
      INT8,
      INT16,
      INT32,
      INT64,
      UINT8,
      UINT16,
      UINT32,
      UINT64,
      STRING,
      CUSTOM
    };

    struct CustomValue {
      typedef void (*Function) (Sink &sink, const Options &options, const void* value);

      Function function_;
      const void* value_;

      template<typename T>
      constexpr CustomValue(const T &value)
	: function_(Formatter<Sink, T>::write), value_(&value)
      {
      }
    };

  private:

    Type type_;
    union {
      const int8_t int8_;
      const int16_t int16_;
      const int32_t int32_;
      const int64_t int64_;
      const uint8_t uint8_;
      const uint16_t uint16_;
      const uint32_t uint32_;
      const uint64_t uint64_;
      const Char* string_;
      const CustomValue custom_;
    };
    const Char* name_ = nullptr;

  public:

    constexpr ParamValue(int8_t value) : type_(Type::INT8), int8_(value), name_(nullptr) { }
    constexpr ParamValue(int16_t value) : type_(Type::INT16), int16_(value), name_(nullptr) { }
    constexpr ParamValue(int32_t value) : type_(Type::INT32), int32_(value), name_(nullptr) { }
    constexpr ParamValue(int64_t value) : type_(Type::INT64), int64_(value), name_(nullptr) { }
    constexpr ParamValue(uint8_t value) : type_(Type::UINT8), uint8_(value), name_(nullptr) { }
    constexpr ParamValue(uint16_t value) : type_(Type::UINT16), uint16_(value), name_(nullptr) { }
    constexpr ParamValue(uint32_t value) : type_(Type::UINT32), uint32_(value), name_(nullptr) { }
    constexpr ParamValue(uint64_t value) : type_(Type::UINT64), uint64_(value), name_(nullptr) { }
    constexpr ParamValue(const Char* value) : type_(Type::STRING), string_(value), name_(nullptr) { }

    constexpr ParamValue(const NamedParam<int8_t> &value) : type_(Type::INT8), int8_(value.value_), name_(value.name_) { }
    constexpr ParamValue(const NamedParam<int16_t> &value) : type_(Type::INT16), int16_(value.value_), name_(value.name_) { }
    constexpr ParamValue(const NamedParam<int32_t> &value) : type_(Type::INT32), int32_(value.value_), name_(value.name_) { }
    constexpr ParamValue(const NamedParam<int64_t> &value) : type_(Type::INT64), int64_(value.value_), name_(value.name_) { }
    constexpr ParamValue(const NamedParam<uint8_t> &value) : type_(Type::UINT8), uint8_(value.value_), name_(value.name_) { }
    constexpr ParamValue(const NamedParam<uint16_t> &value) : type_(Type::UINT16), uint16_(value.value_), name_(value.name_) { }
    constexpr ParamValue(const NamedParam<uint32_t> &value) : type_(Type::UINT32), uint32_(value.value_), name_(value.name_) { }
    constexpr ParamValue(const NamedParam<uint64_t> &value) : type_(Type::UINT64), uint64_(value.value_), name_(value.name_) { }
    constexpr ParamValue(const NamedParam<const Char*> &value) : type_(Type::STRING), string_(value.value_), name_(value.name_) { }

    template<typename T>
    constexpr ParamValue(const T &value) : type_(Type::CUSTOM), custom_(value) { }

    template<typename T>
    constexpr ParamValue(const NamedParam<T> &value) : type_(Type::CUSTOM), custom_(value.value_), name_(value.name_) { }

    constexpr bool is_named() const
    {
      return name_ != nullptr;
    }

    constexpr const char* get_name() const
    {
      return name_;
    }

    template<typename Type>
    constexpr void write_int(Sink &sink, Options &options, Type value) const
    {
      const Char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      Char temp[48];
      size_t index = 0;

      Char sign;
      if (value == Type(0))
      {
	temp[index++] = Char('0');
	sign = 0;
      }else if (value < Type(0))
      {
	value = -value;
	sign = Char('-');
      }else
      {
	if (options.sign_ == '+')
	  sign = Char('+');
	else if (options.sign_ == ' ')
	  sign = Char(' ');
	else
	  sign = 0;
      }

      while (value)
      {
	Type r = value % options.base_;
	value = value / options.base_;

	temp[index++] = chars[r];
      }

      if (sign)
	sink.write(sign);

      if (options.width_ != 0)
      {
	size_t len = options.width_ - index;
	if (options.padding_ == '<')
	{
	  while (len--)
	    sink.write(options.padding_char_);
	  while (index)
	    sink.write(temp[(index--) - 1]);
	}else if (options.padding_ == '>')
	{
	  while (index)
	    sink.write(temp[(index--) - 1]);
	  while (len--)
	    sink.write(options.padding_char_);
	}
      }else
      {
	while (index)
	  sink.write(temp[(index--) - 1]);
      }

    };

    constexpr void execute(Sink &sink, Options &options) const
    {
      switch (type_)
      {
	case Type::INT8:
	  sink.write(int8_);
	  break;

	case Type::UINT8:
	  write_int<uint8_t>(sink, options, uint8_);
	  break;

	case Type::INT16:
	  write_int<int16_t>(sink, options, int16_);
	  break;

	case Type::UINT16:
	  write_int<uint16_t>(sink, options, uint16_);
	  break;

	case Type::INT32:
	  write_int<int32_t>(sink, options, int32_);
	  break;

	case Type::UINT32:
	  write_int<uint32_t>(sink, options, uint32_);
	  break;

	case Type::INT64:
	  write_int<int64_t>(sink, options, int64_);
	  break;

	case Type::UINT64:
	  write_int<uint64_t>(sink, options, uint64_);
	  break;

	case Type::STRING:
	  options_write(sink, options, string_, string_ + strlen(string_));
	  break;

	case Type::CUSTOM:
	  custom_.function_(sink, options, custom_.value_);
	  break;
      }
    }

  };

  template<typename Sink>
  struct Param {

    ParamValue<Sink> value_;

    template<typename T>
    constexpr Param(const T &value)
      : value_(value)
    {
    }

  };

  template<typename Type>
  struct is_named_param : public std::false_type { };

  template<typename ValueType>
  struct is_named_param<NamedParam<ValueType>> : public std::true_type { };

}

#endif
