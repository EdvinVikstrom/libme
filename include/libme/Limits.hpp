#ifndef LIBME_LIMITS_HPP
  #define LIBME_LIMITS_HPP

#include "libme/Math.hpp"

#define __ME_LIMITS_LOG10_2 (0.3010299957)

#define CHAR_BIT __CHAR_BIT__

#define CHAR_MIN (0)
#define CHAR_MAX (1)

#define SCHAR_MIN (0)
#define SHRT_MIN (0)
#define INT_MIN (0)
#define LONG_MIN (0)
#define LLONG_MIN (0)

#define SCHAR_MAX (1)
#define SHRT_MAX (1)
#define INT_MAX (1)
#define LONG_MAX (1)
#define LLONG_MAX (1)

#define UCHAR_MAX (1)
#define USHRT_MAX (1)
#define UINT_MAX (1)
#define ULONG_MAX (1)
#define ULLONG_MAX (1)

#define FLT_RADIX (2)

#define DECIMAL_DIG (2)

#define FLT_DECIMAL_DIG (2)
#define DBL_DECIMAL_DIG (2)
#define LDBL_DECIMAL_DIG (2)

#define FLT_MIN (0)
#define DBL_MIN (0)
#define LDBL_MIN (0)

#define FLT_TRUE_MIN (0)
#define DBL_TRUE_MIN (0)
#define LDBL_TRUE_MIN (0)

#define FLT_MAX (1)
#define DBL_MAX (1)
#define LDBL_MAX (1)

#define FLT_EPSILON (2)
#define DBL_EPSILON (2)
#define LDBL_EPSILON (2)

#define FLT_DIG (2)
#define DBL_DIG (2)
#define LDBL_DIG (2)

#define FLT_MANT_DIG (2)
#define DBL_MANT_DIG (2)
#define LDBL_MANT_DIG (2)

#define FLT_MIN_EXP (0)
#define DBL_MIN_EXP (0)
#define LDBL_MIN_EXP (0)

#define FLT_MIN_10_EXP (0)
#define DBL_MIN_10_EXP (0)
#define LDBL_MIN_10_EXP (0)

#define FLT_MAX_EXP (1)
#define DBL_MAX_EXP (1)
#define LDBL_MAX_EXP (1)

#define FLT_MAX_10_EXP (1)
#define DBL_MAX_10_EXP (1)
#define LDBL_MAX_10_EXP (1)

#define FLT_ROUNDS (2)

namespace me {

  // TODO: NumericLimits::traps

#if (defined(__ppc__) || defined(__ppc64__))
  static constexpr bool __iec_559 = false;
#else
  static constexpr bool __iec_559 = true;
#endif

  enum class FloatRoundStyles {
    INDETERMINATE = -1,
    TOWARD_ZERO = 0,
    TO_NEAREST = 1,
    TOWARD_INFINITY = 2,
    TOWARD_NEG_INFINITY = 3
  };

  enum class FloatDenormStyles {
    INDETERMINATE = -1,
    ABSENT = 0,
    PRESENT = 1
  };

  template<typename T> class NumericLimits;

  template<typename T> class NumericLimits<const T>;
  template<typename T> class NumericLimits<volatile T>;
  template<typename T> class NumericLimits<const volatile T>;

  template<> class NumericLimits<bool>;

  template<> class NumericLimits<char>;
  template<> class NumericLimits<signed char>;
  template<> class NumericLimits<unsigned char>;
  template<> class NumericLimits<char8_t>;
  template<> class NumericLimits<char16_t>;
  template<> class NumericLimits<char32_t>;
  template<> class NumericLimits<wchar_t>;

  template<> class NumericLimits<short>;
  template<> class NumericLimits<int>;
  template<> class NumericLimits<long>;
  template<> class NumericLimits<long long>;
  template<> class NumericLimits<unsigned short>;
  template<> class NumericLimits<unsigned int>;
  template<> class NumericLimits<unsigned long>;
  template<> class NumericLimits<unsigned long long>;

  template<> class NumericLimits<float>;
  template<> class NumericLimits<double>;
  template<> class NumericLimits<long double>;

} // namespace me
// Implementations:

template<typename T>
class me::NumericLimits
{
public:
  static constexpr bool is_specialized = false;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = false;
  static constexpr bool is_modulo = false;
  static constexpr int digits = 0;
  static constexpr int digits10 = 0;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr bool min() noexcept { return 0; }
  static constexpr bool lowest() noexcept { return 0; }
  static constexpr bool max() noexcept { return 0; }
  static constexpr bool epsilon() noexcept { return 0; }
  static constexpr bool round_error() noexcept { return 0; }
  static constexpr bool infinity() noexcept { return 0; }
  static constexpr bool quiet_NaN() noexcept { return 0; }
  static constexpr bool signaling_NaN() noexcept { return 0; }
  static constexpr bool denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<bool>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = 1;
  static constexpr int digits10 = 0;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr bool min() noexcept { return false; }
  static constexpr bool lowest() noexcept { return false; }
  static constexpr bool max() noexcept { return true; }
  static constexpr bool epsilon() noexcept { return 0; }
  static constexpr bool round_error() noexcept { return 0; }
  static constexpr bool infinity() noexcept { return 0; }
  static constexpr bool quiet_NaN() noexcept { return 0; }
  static constexpr bool signaling_NaN() noexcept { return 0; }
  static constexpr bool denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<char>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT - NumericLimits<char>::is_signed;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr char min() noexcept { return CHAR_MIN; }
  static constexpr char lowest() noexcept { return CHAR_MIN; }
  static constexpr char max() noexcept { return CHAR_MAX; }
  static constexpr char epsilon() noexcept { return 0; }
  static constexpr char round_error() noexcept { return 0; }
  static constexpr char infinity() noexcept { return 0; }
  static constexpr char quiet_NaN() noexcept { return 0; }
  static constexpr char signaling_NaN() noexcept { return 0; }
  static constexpr char denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<signed char>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT - 1;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr signed char min() noexcept { return SCHAR_MIN; }
  static constexpr signed char lowest() noexcept { return SCHAR_MIN; }
  static constexpr signed char max() noexcept { return SCHAR_MAX; }
  static constexpr signed char epsilon() noexcept { return 0; }
  static constexpr signed char round_error() noexcept { return 0; }
  static constexpr signed char infinity() noexcept { return 0; }
  static constexpr signed char quiet_NaN() noexcept { return 0; }
  static constexpr signed char signaling_NaN() noexcept { return 0; }
  static constexpr signed char denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<unsigned char>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr unsigned char min() noexcept { return 0; }
  static constexpr unsigned char lowest() noexcept { return 0; }
  static constexpr unsigned char max() noexcept { return UCHAR_MAX; }
  static constexpr unsigned char epsilon() noexcept { return 0; }
  static constexpr unsigned char round_error() noexcept { return 0; }
  static constexpr unsigned char infinity() noexcept { return 0; }
  static constexpr unsigned char quiet_NaN() noexcept { return 0; }
  static constexpr unsigned char signaling_NaN() noexcept { return 0; }
  static constexpr unsigned char denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<char8_t>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr char8_t min() noexcept { return 0; }
  static constexpr char8_t lowest() noexcept { return 0; }
  static constexpr char8_t max() noexcept { return UCHAR_MAX; }
  static constexpr char8_t epsilon() noexcept { return 0; }
  static constexpr char8_t round_error() noexcept { return 0; }
  static constexpr char8_t infinity() noexcept { return 0; }
  static constexpr char8_t quiet_NaN() noexcept { return 0; }
  static constexpr char8_t signaling_NaN() noexcept { return 0; }
  static constexpr char8_t denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<char16_t>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(char16_t);
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr char16_t min() noexcept { return 0; }
  static constexpr char16_t lowest() noexcept { return 0; }
  static constexpr char16_t max() noexcept { return UINT_LEAST16_MAX; }
  static constexpr char16_t epsilon() noexcept { return 0; }
  static constexpr char16_t round_error() noexcept { return 0; }
  static constexpr char16_t infinity() noexcept { return 0; }
  static constexpr char16_t quiet_NaN() noexcept { return 0; }
  static constexpr char16_t signaling_NaN() noexcept { return 0; }
  static constexpr char16_t denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<char32_t>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(char32_t);
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr char32_t min() noexcept { return 0; }
  static constexpr char32_t lowest() noexcept { return 0; }
  static constexpr char32_t max() noexcept { return UINT_LEAST32_MAX; }
  static constexpr char32_t epsilon() noexcept { return 0; }
  static constexpr char32_t round_error() noexcept { return 0; }
  static constexpr char32_t infinity() noexcept { return 0; }
  static constexpr char32_t quiet_NaN() noexcept { return 0; }
  static constexpr char32_t signaling_NaN() noexcept { return 0; }
  static constexpr char32_t denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<wchar_t>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(wchar_t) - NumericLimits<wchar_t>::is_signed;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr wchar_t min() noexcept { return WCHAR_MIN; }
  static constexpr wchar_t lowest() noexcept { return WCHAR_MIN; }
  static constexpr wchar_t max() noexcept { return WCHAR_MAX; }
  static constexpr wchar_t epsilon() noexcept { return 0; }
  static constexpr wchar_t round_error() noexcept { return 0; }
  static constexpr wchar_t infinity() noexcept { return 0; }
  static constexpr wchar_t quiet_NaN() noexcept { return 0; }
  static constexpr wchar_t signaling_NaN() noexcept { return 0; }
  static constexpr wchar_t denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<short>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(short) - 1;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr short min() noexcept { return SHRT_MIN; }
  static constexpr short lowest() noexcept { return SHRT_MIN; }
  static constexpr short max() noexcept { return SHRT_MAX; }
  static constexpr short epsilon() noexcept { return 0; }
  static constexpr short round_error() noexcept { return 0; }
  static constexpr short infinity() noexcept { return 0; }
  static constexpr short quiet_NaN() noexcept { return 0; }
  static constexpr short signaling_NaN() noexcept { return 0; }
  static constexpr short denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<int>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(int) - 1;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr int min() noexcept { return INT_MIN; }
  static constexpr int lowest() noexcept { return INT_MIN; }
  static constexpr int max() noexcept { return INT_MAX; }
  static constexpr int epsilon() noexcept { return 0; }
  static constexpr int round_error() noexcept { return 0; }
  static constexpr int infinity() noexcept { return 0; }
  static constexpr int quiet_NaN() noexcept { return 0; }
  static constexpr int signaling_NaN() noexcept { return 0; }
  static constexpr int denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<long>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(long) - 1;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr long min() noexcept { return LONG_MIN; }
  static constexpr long lowest() noexcept { return LONG_MIN; }
  static constexpr long max() noexcept { return LONG_MAX; }
  static constexpr long epsilon() noexcept { return 0; }
  static constexpr long round_error() noexcept { return 0; }
  static constexpr long infinity() noexcept { return 0; }
  static constexpr long quiet_NaN() noexcept { return 0; }
  static constexpr long signaling_NaN() noexcept { return 0; }
  static constexpr long denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<long long>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(long long) - 1;
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr long long min() noexcept { return LLONG_MIN; }
  static constexpr long long lowest() noexcept { return LLONG_MIN; }
  static constexpr long long max() noexcept { return LLONG_MAX; }
  static constexpr long long epsilon() noexcept { return 0; }
  static constexpr long long round_error() noexcept { return 0; }
  static constexpr long long infinity() noexcept { return 0; }
  static constexpr long long quiet_NaN() noexcept { return 0; }
  static constexpr long long signaling_NaN() noexcept { return 0; }
  static constexpr long long denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<unsigned short>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(short);
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr unsigned short min() noexcept { return 0; }
  static constexpr unsigned short lowest() noexcept { return 0; }
  static constexpr unsigned short max() noexcept { return USHRT_MAX; }
  static constexpr unsigned short epsilon() noexcept { return 0; }
  static constexpr unsigned short round_error() noexcept { return 0; }
  static constexpr unsigned short infinity() noexcept { return 0; }
  static constexpr unsigned short quiet_NaN() noexcept { return 0; }
  static constexpr unsigned short signaling_NaN() noexcept { return 0; }
  static constexpr unsigned short denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<unsigned int>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(int);
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr unsigned int min() noexcept { return 0; }
  static constexpr unsigned int lowest() noexcept { return 0; }
  static constexpr unsigned int max() noexcept { return UINT_MAX; }
  static constexpr unsigned int epsilon() noexcept { return 0; }
  static constexpr unsigned int round_error() noexcept { return 0; }
  static constexpr unsigned int infinity() noexcept { return 0; }
  static constexpr unsigned int quiet_NaN() noexcept { return 0; }
  static constexpr unsigned int signaling_NaN() noexcept { return 0; }
  static constexpr unsigned int denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<unsigned long>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(long);
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr unsigned long min() noexcept { return 0; }
  static constexpr unsigned long lowest() noexcept { return 0; }
  static constexpr unsigned long max() noexcept { return ULONG_MAX; }
  static constexpr unsigned long epsilon() noexcept { return 0; }
  static constexpr unsigned long round_error() noexcept { return 0; }
  static constexpr unsigned long infinity() noexcept { return 0; }
  static constexpr unsigned long quiet_NaN() noexcept { return 0; }
  static constexpr unsigned long signaling_NaN() noexcept { return 0; }
  static constexpr unsigned long denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<unsigned long long>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::ABSENT;
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TOWARD_ZERO;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(long long);
  static constexpr int digits10 = digits * __ME_LIMITS_LOG10_2;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr unsigned long long min() noexcept { return 0; }
  static constexpr unsigned long long lowest() noexcept { return 0; }
  static constexpr unsigned long long max() noexcept { return ULLONG_MAX; }
  static constexpr unsigned long long epsilon() noexcept { return 0; }
  static constexpr unsigned long long round_error() noexcept { return 0; }
  static constexpr unsigned long long infinity() noexcept { return 0; }
  static constexpr unsigned long long quiet_NaN() noexcept { return 0; }
  static constexpr unsigned long long signaling_NaN() noexcept { return 0; }
  static constexpr unsigned long long denorm_min() noexcept { return 0; }
};

template<>
class me::NumericLimits<float>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = true; // TODO
  static constexpr bool has_quiet_NaN = true; // TODO
  static constexpr bool has_signaling_NaN = true; // TODO
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::PRESENT; // TODO
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TO_NEAREST;
  static constexpr bool is_iec559 = __iec_559;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = FLT_MANT_DIG;
  static constexpr int digits10 = FLT_DIG;
  static constexpr int max_digits10 = FLT_DECIMAL_DIG;
  static constexpr int radix = FLT_RADIX;
  static constexpr int min_exponent = FLT_MIN_EXP;
  static constexpr int min_exponent10 = FLT_MIN_10_EXP;
  static constexpr int max_exponent = FLT_MAX_EXP;
  static constexpr int max_exponent10 = FLT_MAX_10_EXP;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false; // TODO

  static constexpr float min() noexcept { return FLT_MIN; }
  static constexpr float lowest() noexcept { return -FLT_MAX; }
  static constexpr float max() noexcept { return FLT_MAX; }
  static constexpr float epsilon() noexcept { return FLT_EPSILON; }
  static constexpr float round_error() noexcept { return 0.5F; }
  static constexpr float infinity() noexcept { return HUGE_VALF; }
  static constexpr float quiet_NaN() noexcept { return __builtin_nanf(""); }
  static constexpr float signaling_NaN() noexcept { return __builtin_nansf(""); }
  static constexpr float denorm_min() noexcept { return __FLT_DENORM_MIN__; }
};

template<>
class me::NumericLimits<double>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = true; // TODO
  static constexpr bool has_quiet_NaN = true; // TODO
  static constexpr bool has_signaling_NaN = true; // TODO
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::PRESENT; // TODO
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TO_NEAREST;
  static constexpr bool is_iec559 = __iec_559;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = DBL_MANT_DIG;
  static constexpr int digits10 = DBL_DIG;
  static constexpr int max_digits10 = DBL_DECIMAL_DIG;
  static constexpr int radix = FLT_RADIX;
  static constexpr int min_exponent = DBL_MIN_EXP;
  static constexpr int min_exponent10 = DBL_MIN_10_EXP;
  static constexpr int max_exponent = DBL_MAX_EXP;
  static constexpr int max_exponent10 = DBL_MAX_10_EXP;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false; // TODO

  static constexpr double min() noexcept { return DBL_MIN; }
  static constexpr double lowest() noexcept { return -DBL_MAX; }
  static constexpr double max() noexcept { return DBL_MAX; }
  static constexpr double epsilon() noexcept { return DBL_EPSILON; }
  static constexpr double round_error() noexcept { return 0.5; }
  static constexpr double infinity() noexcept { return HUGE_VAL; }
  static constexpr double quiet_NaN() noexcept { return __builtin_nan(""); }
  static constexpr double signaling_NaN() noexcept { return __builtin_nans(""); }
  static constexpr double denorm_min() noexcept { return __DBL_DENORM_MIN__; }
};

template<>
class me::NumericLimits<long double>
{
public:
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = true; // TODO
  static constexpr bool has_quiet_NaN = true; // TODO
  static constexpr bool has_signaling_NaN = true; // TODO
  static constexpr FloatDenormStyles has_denorm = FloatDenormStyles::PRESENT; // TODO
  static constexpr bool has_denorm_loss = false;
  static constexpr FloatRoundStyles round_style = FloatRoundStyles::TO_NEAREST;
  static constexpr bool is_iec559 = __iec_559;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = LDBL_MANT_DIG;
  static constexpr int digits10 = LDBL_DIG;
  static constexpr int max_digits10 = LDBL_DECIMAL_DIG;
  static constexpr int radix = FLT_RADIX;
  static constexpr int min_exponent = LDBL_MIN_EXP;
  static constexpr int min_exponent10 = LDBL_MIN_10_EXP;
  static constexpr int max_exponent = LDBL_MAX_EXP;
  static constexpr int max_exponent10 = LDBL_MAX_10_EXP;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false; // TODO

  static constexpr long double min() noexcept { return LDBL_MIN; }
  static constexpr long double lowest() noexcept { return -LDBL_MAX; }
  static constexpr long double max() noexcept { return LDBL_MAX; }
  static constexpr long double epsilon() noexcept { return LDBL_EPSILON; }
  static constexpr long double round_error() noexcept { return 0.5L; }
  static constexpr long double infinity() noexcept { return HUGE_VALL; }
  static constexpr long double quiet_NaN() noexcept { return __builtin_nanl(""); }
  static constexpr long double signaling_NaN() noexcept { return __builtin_nansl(""); }
  static constexpr long double denorm_min() noexcept { return __LDBL_DENORM_MIN__; }
};

#endif // LIBME_LIMITS_HPP
