#ifndef LIBME_FORMAT_OPTIONS_HPP
  #define LIBME_FORMAT_OPTIONS_HPP

namespace me::format {

  struct Options {
    int width_ = 0;
    int base_ = 10;
    char padding_char_ = ' ';
    char padding_ = '>';
    char case_ = '-';
    char sign_ = '-';
  };

}

#endif
