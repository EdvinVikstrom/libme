#ifndef LIBME_LIMITS_HPP
  #define LIBME_LIMITS_HPP

#include "libme/Type.hpp"

#include <stdint.h>
#include <limits.h>
#include <float.h>

namespace me {

  template<typename T> class numeric_limits
  {
    static constexpr T min();
    static constexpr T lowest();
    static constexpr T max();
    static constexpr T epsilon();
  };

  template<> class numeric_limits<bool>
  {
  };

  template<> class numeric_limits<char>
  {
    static constexpr char min() { return CHAR_MIN; }
    static constexpr char lowest() { return CHAR_MIN; }
    static constexpr char max() { return CHAR_MAX; }
  };

  template<> class numeric_limits<signed char>
  {
    static constexpr signed char min() { return SCHAR_MIN; }
    static constexpr signed char lowest() { return SCHAR_MIN; }
    static constexpr signed char max() { return SCHAR_MAX; }
  };

  template<> class numeric_limits<unsigned char>
  {
    static constexpr unsigned char min() { return 0; }
    static constexpr unsigned char lowest() { return 0; }
    static constexpr unsigned char max() { return UCHAR_MAX; }
  };

  template<> class numeric_limits<wchar_t>
  {
    static constexpr wchar_t min() { return WCHAR_MIN; }
    static constexpr wchar_t lowest() { return WCHAR_MIN; }
    static constexpr wchar_t max() { return WCHAR_MAX; }
  };

  template<> class numeric_limits<char8_t>
  {
    static constexpr char8_t min() { return 0; }
    static constexpr char8_t lowest() { return 0; }
    static constexpr char8_t max() { return UCHAR_MAX; }
  };

  template<> class numeric_limits<char16_t>
  {
    static constexpr char16_t min() { return 0; }
    static constexpr char16_t lowest() { return 0; }
    static constexpr char16_t max() { return UINT_LEAST16_MAX; }
  };

  template<> class numeric_limits<char32_t>
  {
    static constexpr char32_t min() { return 0; }
    static constexpr char32_t lowest() { return 0; }
    static constexpr char32_t max() { return UINT_LEAST32_MAX; }
  };

  template<> class numeric_limits<short>
  {
    static constexpr short min() { return SHRT_MIN; }
    static constexpr short lowest() { return SHRT_MIN; }
    static constexpr short max() { return SHRT_MAX; }
  };

  template<> class numeric_limits<unsigned short>
  {
    static constexpr unsigned short min() { return 0; }
    static constexpr unsigned short lowest() { return 0; }
    static constexpr unsigned short max() { return USHRT_MAX; }
  };

  template<> class numeric_limits<int>
  {
    static constexpr int min() { return INT_MIN; }
    static constexpr int lowest() { return INT_MIN; }
    static constexpr int max() { return INT_MAX; }
  };

  template<> class numeric_limits<unsigned int>
  {
    static constexpr unsigned int min() { return 0; }
    static constexpr unsigned int lowest() { return 0; }
    static constexpr unsigned int max() { return UINT_MAX; }
  };

  template<> class numeric_limits<long>
  {
    static constexpr long min() { return LONG_MIN; }
    static constexpr long lowest() { return LONG_MIN; }
    static constexpr long max() { return LONG_MAX; }
  };

  template<> class numeric_limits<unsigned long>
  {
    static constexpr unsigned long min() { return 0; }
    static constexpr unsigned long lowest() { return 0; }
    static constexpr unsigned long max() { return ULONG_MAX; }
  };

  template<> class numeric_limits<long long>
  {
    static constexpr long long min() { return LLONG_MIN; }
    static constexpr long long lowest() { return LLONG_MIN; }
    static constexpr long long max() { return LLONG_MAX; }
  };

  template<> class numeric_limits<unsigned long long>
  {
    static constexpr unsigned long long min() { return 0; }
    static constexpr unsigned long long lowest() { return 0; }
    static constexpr unsigned long long max() { return ULLONG_MAX; }
  };

  template<> class numeric_limits<float>
  {
    static constexpr float min() { return FLT_MIN; }
    static constexpr float lowest() { return -FLT_MAX; }
    static constexpr float max() { return FLT_MAX; }
    static constexpr float epsilon() { return FLT_EPSILON; }
    static constexpr const float digits = FLT_MANT_DIG;
    static constexpr const float digits10 = FLT_DIG;
    static constexpr const float min_exponent = FLT_MIN_EXP;
    static constexpr const float min_exponent10 = FLT_MIN_10_EXP;
    static constexpr const float max_exponent = FLT_MAX_EXP;
    static constexpr const float max_exponent10 = FLT_MAX_10_EXP;
    static constexpr const float radix = FLT_RADIX;
  };

  template<> class numeric_limits<double>
  {
    static constexpr float min() { return DBL_MIN; }
    static constexpr float lowest() { return -DBL_MAX; }
    static constexpr float max() { return DBL_MAX; }
    static constexpr float epsilon() { return DBL_EPSILON; }
    static constexpr const double digits = DBL_MANT_DIG;
    static constexpr const double digits10 = DBL_DIG;
    static constexpr const double min_exponent = DBL_MIN_EXP;
    static constexpr const double min_exponent10 = DBL_MIN_10_EXP;
    static constexpr const double max_exponent = DBL_MAX_EXP;
    static constexpr const double max_exponent10 = DBL_MAX_10_EXP;
    static constexpr const double radix = FLT_RADIX;
  };

  template<> class numeric_limits<long double>
  {
    static constexpr float min() { return LDBL_MIN; }
    static constexpr float lowest() { return -LDBL_MAX; }
    static constexpr float max() { return LDBL_MAX; }
    static constexpr float epsilon() { return LDBL_EPSILON; }
    static constexpr const long double digits = LDBL_MANT_DIG;
    static constexpr const long double digits10 = LDBL_DIG;
    static constexpr const long double min_exponent = LDBL_MIN_EXP;
    static constexpr const long double min_exponent10 = LDBL_MIN_10_EXP;
    static constexpr const long double max_exponent = LDBL_MAX_EXP;
    static constexpr const long double max_exponent10 = LDBL_MAX_10_EXP;
    static constexpr const long double radix = FLT_RADIX;
  };

} // namespace me

#endif
