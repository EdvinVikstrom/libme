#ifndef LIBME_FILE_HPP
  #define LIBME_FILE_HPP

#include <stdio.h>

namespace me {

  class File {

  private:

    FILE* file_;

  public:

    constexpr File(FILE* file);

  };

}

constexpr me::File::File(FILE* file)
  : file_(file)
{
}

#endif
