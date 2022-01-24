#include "libme/detail/String.hpp"

#include <stdio.h>

int main()
{
  typedef me::detail::String<char, me::detail::CharTraits<char>, me::DefaultAllocator<char>> String;
  String str("Testar bara");

  str.insert(2LU, 5LU, '!');

  ::printf("string: [%s]\n", str.c_str());
  return 0;
}
