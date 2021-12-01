#ifndef LIBME_OPTIONS_HPP
  #define LIBME_OPTIONS_HPP

#include "libme/Exception.hpp"
#include "libme/String.hpp"
#include "libme/Vector.hpp"

namespace me::cl {

  enum class ExpectedValue {
    NONE = 0x00,
    OPTIONAL = 0x01,
    REQUIRED = 0x02
  };

  class OptionDescriptor {

  private:

    const char m_short_name;
    const StringView m_long_name;
    const StringView m_description;

    const ExpectedValue m_expected_value;

  public:

    OptionDescriptor(char short_name, const StringView &long_name, const StringView &description, ExpectedValue expected_value);
    OptionDescriptor(char short_name, const StringView &description, ExpectedValue expected_value);
    OptionDescriptor(const StringView &long_name, const StringView &description, ExpectedValue expected_value);

    char get_short_name() const;
    const StringView& get_long_name() const;
    const StringView& get_description() const;

    ExpectedValue get_expected_value() const;

  };

  class Option {

  private:

    const OptionDescriptor* m_descriptor;
    const StringView m_value;

  public:

    Option(const OptionDescriptor* descriptor, const StringView &value);
    Option(const OptionDescriptor* descriptor);

    const OptionDescriptor* get_descriptor() const;
    const StringView& get_value() const;
    bool has_value() const;

  };

  class ArgumentParser {

  private:

    const Vector<OptionDescriptor> m_options;
    const size_t m_arg_count;
    const StringView* m_args;
    size_t m_arg_index;
    size_t m_short_index;

  public:

    ArgumentParser(const Vector<OptionDescriptor> &options, size_t arg_count, const StringView* args);

    void for_each(auto fn);

  private:

    const Option next_option();
    const Option parse_long();
    const Option parse_short();

    const OptionDescriptor* find_long_option(const StringView &l);
    const OptionDescriptor* find_short_option(char s);

  };


  /* exceptions */
  class LongNotFoundException final : public Exception {

  private:

    const StringView m_name;

  public:

    LongNotFoundException(const StringView &name);

    const StringView& get_name() const;

    [[nodiscard]] const char* get_message() const override;

  };

  class ShortNotFoundException final : public Exception {

  private:

    const char m_name;

  public:

    ShortNotFoundException(char name);

    char get_name() const;

    [[nodiscard]] const char* get_message() const override;

  };

  class OptionValueNotFoundException final : public Exception {

  private:

    const OptionDescriptor* m_option;

  public:

    OptionValueNotFoundException(const OptionDescriptor* option);

    const OptionDescriptor* get_option() const;

    [[nodiscard]] const char* get_message() const override;

  };

  class OptionValueFoundException final : public Exception {

  private:

    const OptionDescriptor* m_option;

  public:

    OptionValueFoundException(const OptionDescriptor* option);

    const OptionDescriptor* get_option() const;

    [[nodiscard]] const char* get_message() const override;

  };

}

void me::cl::ArgumentParser::for_each(auto fn)
{
  while (true)
  {
    const Option option = next_option();
    if (option.get_descriptor() == nullptr)
      break;

    fn(option);
  }
}

#endif
