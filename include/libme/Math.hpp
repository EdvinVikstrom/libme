#ifndef LIBME_MATH_HPP
  #define LIBME_MATH_HPP

#include "libme/Type.hpp"

#define HUGE_VAL (1)
#define HUGE_VALF (1)
#define HUGE_VALL (1)
#define INFINITY (1)
#define NAN (0)
#define FP_INFINITY (1)
#define FP_NAN (0)
#define FP_NORMAL (1)
#define FP_SUBNORMAL (1)
#define FP_ZERO (0)
#define FP_FAST_FMA (0)
#define FP_FAST_FMAF (0)
#define FP_FAST_FMAL (0)
#define FP_ILOGBO (0)
#define FP_ILOGBNAN (0)
#define MATH_ERRNO (1)
#define MATH_ERREXCEPT (1)

namespace me::math {

  using float_t = float;
  using double_t = double;
  
  /* Basic operations */

  template<typename NumType>
  constexpr NumType abs(NumType x);

  template<typename NumType>
  constexpr NumType mod(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType remainder(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType remquo(NumType x, NumType y, int &quo);

  template<typename NumType>
  constexpr NumType fma(NumType x, NumType y, NumType z);

  template<typename NumType>
  constexpr NumType max(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType min(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType dim(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType nan(const char* arg);

  /* Exponential functions */

  template<typename NumType>
  constexpr NumType exp(NumType x);

  template<typename NumType>
  constexpr NumType exp2(NumType x);

  template<typename NumType>
  constexpr NumType expm(NumType x);

  template<typename NumType>
  constexpr NumType log(NumType x);

  template<typename NumType>
  constexpr NumType log10(NumType x);

  template<typename NumType>
  constexpr NumType log2(NumType x);

  template<typename NumType>
  constexpr NumType log1p(NumType x);

  /* Power functions */

  template<typename NumType>
  constexpr NumType pow(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType sqrt(NumType x);

  template<typename NumType>
  constexpr NumType cbrt(NumType x);

  template<typename NumType>
  constexpr NumType hypot(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType hypot(NumType x, NumType y, NumType z);

  /* Trigonometric functions */

  template<typename NumType>
  constexpr NumType sin(NumType x);

  template<typename NumType>
  constexpr NumType cos(NumType x);

  template<typename NumType>
  constexpr NumType tan(NumType x);

  template<typename NumType>
  constexpr NumType asin(NumType x);

  template<typename NumType>
  constexpr NumType acos(NumType x);

  template<typename NumType>
  constexpr NumType atan(NumType x);

  template<typename NumType>
  constexpr NumType atan2(NumType x, NumType y);

  /* Hyperbolic functions */

  template<typename NumType>
  constexpr NumType sinh(NumType x);

  template<typename NumType>
  constexpr NumType cosh(NumType x);

  template<typename NumType>
  constexpr NumType tanh(NumType x);

  template<typename NumType>
  constexpr NumType asinh(NumType x);

  template<typename NumType>
  constexpr NumType acosh(NumType x);

  template<typename NumType>
  constexpr NumType atanh(NumType x);

  /* Error and gamma functions */

  template<typename NumType>
  constexpr NumType erf(NumType x);

  template<typename NumType>
  constexpr NumType erfc(NumType x);

  template<typename NumType>
  constexpr NumType tgamma(NumType x);

  template<typename NumType>
  constexpr NumType lgamma(NumType x);

  /* Rounding operations */

  template<typename NumType>
  constexpr NumType ceil(NumType x);

  template<typename NumType>
  constexpr NumType floor(NumType x);

  template<typename NumType>
  constexpr NumType trunc(NumType x);

  template<typename NumType>
  constexpr NumType round(NumType x);

  template<typename NumType>
  constexpr NumType lround(NumType x);

  template<typename NumType>
  constexpr NumType llround(NumType x);

  template<typename NumType>
  constexpr NumType nearbyint(NumType x);

  template<typename NumType>
  constexpr NumType rint(NumType x);

  template<typename NumType>
  constexpr NumType lrint(NumType x);

  template<typename NumType>
  constexpr NumType llrint(NumType x);
   
  /* Floating point manipulation functions */

  template<typename NumType>
  constexpr NumType frexp(NumType x, int &exp);

  template<typename NumType>
  constexpr NumType ldexp(NumType x, int exp);

  template<typename NumType>
  constexpr NumType modf(NumType x, NumType &i);

  template<typename NumType>
  constexpr NumType scalbn(NumType x, int exp);

  template<typename NumType>
  constexpr NumType scalbln(NumType x, int exp);

  template<typename NumType>
  constexpr int ilogb(NumType x);

  template<typename NumType>
  constexpr NumType logb(NumType x);

  template<typename NumType>
  constexpr NumType nextafter(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType nexttoward(NumType x, NumType y);

  template<typename NumType>
  constexpr NumType copysign(NumType x, NumType y);

  /* Classification and comparison */

  template<typename NumType>
  constexpr int fpclassify(NumType x);

  template<typename NumType>
  constexpr bool isfinite(NumType x);

  template<typename NumType>
  constexpr bool isinf(NumType x);

  template<typename NumType>
  constexpr bool isnan(NumType x);

  template<typename NumType>
  constexpr bool isnormal(NumType x);

  template<typename NumType>
  constexpr bool signbit(NumType x);

  template<typename NumType>
  constexpr bool isgreater(NumType x, NumType y);

  template<typename NumType>
  constexpr bool isgreaterequal(NumType x, NumType y);

  template<typename NumType>
  constexpr bool isless(NumType x, NumType y);

  template<typename NumType>
  constexpr bool islessequal(NumType x, NumType y);

  template<typename NumType>
  constexpr bool islessgreater(NumType x, NumType y);

  template<typename NumType>
  constexpr bool isunordered(NumType x, NumType y);

} // namespace me
// Implementations:

template<typename NumType>
constexpr NumType
  me::math::abs(NumType x)
{
  return x < 0 ? -x : x;
}

template<typename NumType>
constexpr NumType
  me::math::mod(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::remainder(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::remquo(NumType x, NumType y, int &quo)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::fma(NumType x, NumType y, NumType z)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::max(NumType x, NumType y)
{
  return x > y ? x : y;
}

template<typename NumType>
constexpr NumType
  me::math::min(NumType x, NumType y)
{
  return x < y ? x : y;
}

template<typename NumType>
constexpr NumType
  me::math::dim(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::nan(const char* arg)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::exp(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::exp2(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::expm(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::log(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::log10(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::log2(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::log1p(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::pow(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::sqrt(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::cbrt(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::hypot(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::hypot(NumType x, NumType y, NumType z)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::sin(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::cos(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::tan(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::asin(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::acos(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::atan(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::atan2(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::sinh(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::cosh(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::tanh(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::asinh(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::acosh(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::atanh(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::erf(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::erfc(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::tgamma(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::lgamma(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::ceil(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::floor(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::trunc(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::round(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::lround(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::llround(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::nearbyint(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::rint(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::lrint(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::llrint(NumType x)
{
  return 0;
}
 
template<typename NumType>
constexpr NumType
  me::math::frexp(NumType x, int &exp)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::ldexp(NumType x, int exp)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::modf(NumType x, NumType &i)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::scalbn(NumType x, int exp)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::scalbln(NumType x, int exp)
{
  return 0;
}

template<typename NumType>
constexpr int
  me::math::ilogb(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::logb(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::nextafter(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::nexttoward(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr NumType
  me::math::copysign(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr int
  me::math::fpclassify(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::isfinite(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::isinf(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::isnan(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::isnormal(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::signbit(NumType x)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::isgreater(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::isgreaterequal(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::isless(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::islessequal(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::islessgreater(NumType x, NumType y)
{
  return 0;
}

template<typename NumType>
constexpr bool
  me::math::isunordered(NumType x, NumType y)
{
  return 0;
}

#endif // LIBME_MATH_HPP
