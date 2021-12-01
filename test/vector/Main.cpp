#include <libme/Vector.hpp>

using namespace me;

#define TEST_FUNCTION(f) \
{ \
  Vector<Object> org = vec; \
  bool res = f(vec); \
  if (res) \
  { \
    ::printf("%s: passed\n", #f); \
  }else \
  { \
    ::fprintf(stderr, "%s: failed\n", #f); \
    ::printf("Vector[%lu]:\n", vec.length()); \
    char temp[256]; \
    for (size_t i = 0; i != vec.length(); i++) \
      ::printf("\t%s\n", vec.at(i).as_string(temp)); \
    return 1; \
  } \
}

struct Object {
  int x, y;
  Object(int x, int y)
    : x(x), y(y)
  {
  }
  bool operator==(const Object &obj) const
  {
    return x == obj.x && y == obj.y;
  }
  const char* as_string(char* temp) const
  {
    sprintf(temp, "{%i,%i}", x, y);
    return temp;
  }
};

bool test_assign1(Vector<Object> &vec)
{
  Object val(47, 83);
  vec.assign(val, 3);
  if (vec.length() == 3)
  {
    if (vec.at(0) == val && vec.at(1) == val && vec.at(2) == val)
      return true;
  }
  return false;
}

bool test_assign2(Vector<Object> &vec)
{
  constexpr size_t len = 4;
  Object vals[len] = {
    Object(55, 66), Object(77, 96), Object(13, 87), Object(107, 128)
  };
  vec.assign(vals, vals + len);
  if (vec.length() == len)
  {
    for (size_t i = 0; i != len; i++)
    {
      if (vals[i] != vec.at(i))
	return false;
    }
    return true;
  }
  return false;
}

bool test_assign3(Vector<Object> &vec)
{
  vec.assign({Object(93, 808), Object(87, 756)});
  if (vec.length() == 2)
  {
    if (vec.at(0) == Object(93, 808) && vec.at(1) == Object(87, 756))
      return true;
  }
  return false;
}

int main()
{
  Vector<Object> vec({Object(0, 1), Object(2, 3), Object(4, 7), Object(9, 7), Object(13, 5)});
  TEST_FUNCTION(test_assign1);
  TEST_FUNCTION(test_assign2);
  TEST_FUNCTION(test_assign3);
  return 0;
}
