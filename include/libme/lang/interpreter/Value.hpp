#ifndef LIBME_LANG_INTERPRETER_VALUE_HPP
  #define LIBME_LANG_INTERPRETER_VALUE_HPP

#include "libme/SharedPtr.hpp"
#include "libme/String.hpp"
#include "libme/Exception.hpp"

namespace me::lang {

  enum class ValueTypes {
    INTEGER,
    STRING
  };

  class Value {

  private:

    const ValueTypes m_type;

  public:

    Value(const ValueTypes &type)
      : m_type(type) { }
    virtual ~Value() { }

    ValueTypes get_type() const { return m_type; }

    virtual void operator_assign(const SharedPtr<Value> value) = 0;
    virtual void operator_add(const SharedPtr<Value> value) = 0;

    virtual SharedPtr<Value> clone() const = 0;
    virtual void to_string(String &output) const = 0;

  };

  class IntegerVal : public Value {

  private:

    int m_integer;

  public:

    IntegerVal(int integer)
      : Value(ValueTypes::INTEGER), m_integer(integer) { }
    ~IntegerVal() override = default;

    int get_value() const { return m_integer; }
    int& get_value() { return m_integer; }

    void operator_assign(const SharedPtr<Value> value) override
    {
      if (value->get_type() != ValueTypes::INTEGER)
	throw RuntimeError("not same type");
      m_integer = reinterpret_cast<const IntegerVal*>(value.get())->m_integer;
    }

    void operator_add(const SharedPtr<Value> value) override
    {
      if (value->get_type() != ValueTypes::INTEGER)
	throw RuntimeError("not same type");
      m_integer += reinterpret_cast<const IntegerVal*>(value.get())->m_integer;
    }

    SharedPtr<Value> clone() const override
    {
      return make_shared<IntegerVal>(m_integer);
    }

    void to_string(String &output) const override
    {
      output.append("int");
    }

  };

  class StringVal : public Value {

  private:

    String m_string;

  public:

    StringVal(String string)
      : Value(ValueTypes::STRING), m_string(string) { }
    ~StringVal() override = default;

    String get_value() const { return m_string; }
    String& get_value() { return m_string; }

    void operator_assign(const SharedPtr<Value> value) override
    {
      if (value->get_type() != ValueTypes::STRING)
	throw RuntimeError("not same type");
      m_string = reinterpret_cast<const StringVal*>(value.get())->get_value();
    }

    void operator_add(const SharedPtr<Value> value) override
    {
      if (value->get_type() != ValueTypes::STRING)
	throw RuntimeError("not same type");
      m_string.append(reinterpret_cast<const StringVal*>(value.get())->get_value());
    }

    SharedPtr<Value> clone() const override
    {
      return make_shared<StringVal>(m_string);
    }

    void to_string(String &output) const override
    {
      output.append(m_string);
    }

  };

}

#endif
