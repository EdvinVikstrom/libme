#ifndef LIBME_TRAITS_HPP
  #define LIBME_TRAITS_HPP

namespace me {

  template<typename Type>
  class Traits {

  public:
    
    template<typename... Args> static void construct(Type* dest, const Args... args);
    static void destroy(const Type &val);

  };

} // namespace me


#endif
