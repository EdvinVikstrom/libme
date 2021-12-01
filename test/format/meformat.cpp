#include <string>
#include <fmt/core.h>
#include "../../include/libme/format.hpp"

#include <sys/time.h>

static me::uint64_t get_time()
{
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  return tv.tv_usec;
}

int main()
{
  me::uint64_t me_start = get_time();
  me::format::print(stdout, "Hello {} and {}\n", "Edvin", "Vilmer", 83);
  me::uint64_t me_end = get_time();

  me::uint64_t fmt_start = get_time();
  fmt::print("Hello {} and {}\n", "Edvin", "Vilmer", 83);
  me::uint64_t fmt_end = get_time();

  me::uint64_t res1 = me_end - me_start;
  me::uint64_t res2 = fmt_end - fmt_start;

  double f = static_cast<double>(res2) / static_cast<double>(res1);

  ::printf("me::format took [%lu]\n", res1);
  ::printf("fmt took [%lu]\n", res2);
  ::printf("me::format is %lf faster than fmt\n", f);
  return 0;
}
