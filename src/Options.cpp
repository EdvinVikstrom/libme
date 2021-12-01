#include "libme/Options.hpp"

/* ------------------------------ */
/* class me::cl::OptionDescriptor */
/* ------------------------------ */
me::cl::OptionDescriptor::OptionDescriptor(char short_name, const StringView &long_name, const StringView &description, ExpectedValue expected_value)
  : m_short_name(short_name), m_long_name(long_name), m_description(description), m_expected_value(expected_value)
{
}

me::cl::OptionDescriptor::OptionDescriptor(char short_name, const StringView &description, ExpectedValue expected_value)
  : m_short_name(short_name), m_description(description), m_expected_value(expected_value)
{
}

me::cl::OptionDescriptor::OptionDescriptor(const StringView &long_name, const StringView &description, ExpectedValue expected_value)
  : m_short_name('\0'), m_long_name(long_name), m_description(description), m_expected_value(expected_value)
{
}

char me::cl::OptionDescriptor::get_short_name() const
{
  return m_short_name;
}

const me::StringView& me::cl::OptionDescriptor::get_long_name() const
{
  return m_long_name;
}

const me::StringView& me::cl::OptionDescriptor::get_description() const
{
  return m_description;
}

me::cl::ExpectedValue me::cl::OptionDescriptor::get_expected_value() const
{
  return m_expected_value;
}
/* end class me::cl::OptionDescriptor */

/* -------------------- */
/* class me::cl::Option */
/* -------------------- */
me::cl::Option::Option(const OptionDescriptor* descriptor, const StringView &value)
  : m_descriptor(descriptor), m_value(value)
{
}

me::cl::Option::Option(const OptionDescriptor* descriptor)
  : m_descriptor(descriptor)
{
}

const me::cl::OptionDescriptor* me::cl::Option::get_descriptor() const
{
  return m_descriptor;
}

const me::StringView& me::cl::Option::get_value() const
{
  return m_value;
}

bool me::cl::Option::has_value() const
{
  return !m_value.is_empty();
}
/* end class me::cl::Option */

/* -------------------- */
/* class me::cl::Parser */
/* -------------------- */
me::cl::ArgumentParser::ArgumentParser(const Vector<OptionDescriptor> &options, size_t arg_count, const StringView* args)
  : m_options(options), m_arg_count(arg_count), m_args(args), m_arg_index(0), m_short_index(0)
{
}

const me::cl::Option me::cl::ArgumentParser::next_option()
{
  if (m_short_index != 0)
    return parse_short();

  while (m_arg_index != m_arg_count)
  {
    if (m_args[m_arg_index].length() != 0 && m_args[m_arg_index].at(0) == '-')
      break;
    m_arg_index++;
  }

  if (m_arg_index == m_arg_count)
    return nullptr;

  bool long_opt = m_args[m_arg_index].length() > 1 && m_args[m_arg_index].at(1) == '-';

  if (long_opt)
    return parse_long();

  m_short_index = 1;
  return parse_short();
}

const me::cl::Option me::cl::ArgumentParser::parse_long()
{
  const StringView str = m_args[m_arg_index++].substring(2);
  size_t off = str.find('=');

  StringView opt_name;
  bool has_value;
  if (off != StringView::npos)
  {
    opt_name = str.substring(0, off);
    has_value = true;
  }else
  {
    opt_name = str;
    has_value = false;
  }

  const OptionDescriptor* desc = find_long_option(opt_name);

  if (desc == nullptr)
    throw LongNotFoundException(opt_name);

  if (desc->get_expected_value() != ExpectedValue::NONE)
  {
    if (desc->get_expected_value() == ExpectedValue::REQUIRED && !has_value)
      throw OptionValueNotFoundException(desc);
    return Option(desc, str.substring(off + 1));
  }else if (has_value)
    throw OptionValueFoundException(desc);
  return Option(desc);
}

const me::cl::Option me::cl::ArgumentParser::parse_short()
{
  char opt_name = m_args[m_arg_index].at(m_short_index++);
  const OptionDescriptor* desc = find_short_option(opt_name);

  if (desc == nullptr)
    throw ShortNotFoundException(opt_name);

  if (desc->get_expected_value() != ExpectedValue::NONE)
  {
    if (m_short_index < m_args[m_arg_index].length())
    {
      m_short_index = 0;
      return Option(desc, m_args[m_arg_index++].substring(m_short_index));
    }else if (m_arg_index + 1 != m_arg_count)
    {
      m_short_index = 0;
      m_arg_index++;
      return Option(desc, m_args[m_arg_index++ + 1].substring(m_short_index));
    }else if (desc->get_expected_value() == ExpectedValue::REQUIRED) // NOTE: cannot run 'next_option()' after this
      throw OptionValueNotFoundException(desc);
  }

  if (m_short_index == m_args[m_arg_index].length())
  {
    m_arg_index++;
    m_short_index = 0;
  }
  return Option(desc);
}

const me::cl::OptionDescriptor* me::cl::ArgumentParser::find_long_option(const StringView &l)
{
  for (const OptionDescriptor &opt : m_options)
  {
    if (!opt.get_long_name().is_empty() && opt.get_long_name() == l)
      return &opt;
  }
  return nullptr;
}

const me::cl::OptionDescriptor* me::cl::ArgumentParser::find_short_option(char s)
{
  for (const OptionDescriptor &opt : m_options)
  {
    if (opt.get_short_name() != '\0' && opt.get_short_name() == s)
      return &opt;
  }
  return nullptr;
}
/* end class me::cl::Parser */


/* ----------------------------------- */
/* class me::cl::LongNotFoundException */
/* ----------------------------------- */
me::cl::LongNotFoundException::LongNotFoundException(const StringView &name)
  : m_name(name)
{
}

const me::StringView& me::cl::LongNotFoundException::get_name() const
{
  return m_name;
}

const char* me::cl::LongNotFoundException::get_message() const
{
  return "unknown long option";
}
/* end class me::cl::LongNotFoundException */


/* ------------------------------------ */
/* class me::cl::ShortNotFoundException */
/* ------------------------------------ */
me::cl::ShortNotFoundException::ShortNotFoundException(char name)
  : m_name(name)
{
}

char me::cl::ShortNotFoundException::get_name() const
{
  return m_name;
}

const char* me::cl::ShortNotFoundException::get_message() const
{
  return "unknown short option";
}
/* end class me::cl::ShortNotFoundException */


/* ------------------------------------------ */
/* class me::cl::OptionValueNotFoundException */
/* ------------------------------------------ */
me::cl::OptionValueNotFoundException::OptionValueNotFoundException(const OptionDescriptor* option)
  : m_option(option)
{
}

const me::cl::OptionDescriptor* me::cl::OptionValueNotFoundException::get_option() const
{
  return m_option;
}

const char* me::cl::OptionValueNotFoundException::get_message() const
{
  return "required value not found";
}
/* end class me::cl::OptionValueNotFoundException */


/* --------------------------------------- */
/* class me::cl::OptionValueFoundException */
/* --------------------------------------- */
me::cl::OptionValueFoundException::OptionValueFoundException(const OptionDescriptor* option)
  : m_option(option)
{
}

const me::cl::OptionDescriptor* me::cl::OptionValueFoundException::get_option() const
{
  return m_option;
}

const char* me::cl::OptionValueFoundException::get_message() const
{
  return "value found";
}
/* end class me::cl::OptionValueFoundException */
