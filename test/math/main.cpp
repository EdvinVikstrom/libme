#include "../../include/libme/Math.hpp"

#include <stdio.h>

int main()
{
  float x = 2;
  float y = 8.5F;

  float res = me::math::pow(x, y);
  ::printf("%f ^ %f = %f\n", x, y, res);

  return 0;
}
