#include <stdio.h>
#include <unistd.h>

#include "libme/detail/CharTraits.hpp"
#include "libme/detail/String.hpp"
#include "libme/Allocator.hpp"

int main()
{
  me::detail::String<char, me::detail::CharTraits<char>, me::DefaultAllocator<char>> str("Hi everybody!");
#include "libme/detail/StringTest.hpp"
  return 0;
}
