#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>

constexpr size_t kSize {10U};
using Bound = int[kSize];
using Unbound = int[];

int64_t ext[kSize];

int sum(int32_t v[kSize]) {
    static_assert(not std::is_bounded_array_v<std::remove_reference_t<decltype(v)>>);
    static_assert(not std::is_unbounded_array_v<std::remove_reference_t<decltype(v)>>);
    return 0;
}
int sum(int (&v)[kSize]) {
    return 1;
}
int sum(int (&v)[]) {
    return 2;
}

int sum(int64_t (&v)[kSize]) {
    static_assert(std::is_bounded_array_v<std::remove_reference_t<decltype(v)>>);
    return 3;
}
int sum(int64_t (&v)[]) {
    static_assert(std::is_unbounded_array_v<std::remove_reference_t<decltype(v)>>);
    return 4;
}

static_assert(std::is_bounded_array_v<Bound>);
static_assert(std::is_unbounded_array_v<Unbound>);

template <class T>
void func(T t) {
    printf("%s\r\n", __PRETTY_FUNCTION__);
}

template <class T>
void func2(T &&t) {
    printf("%s\r\n", __PRETTY_FUNCTION__);
}

int main() {
  int x[kSize] {};
  int result {};
//   result = sum(x);  // call of overloaded 'sum(int [10])' is ambiguous
  result = sum(&x[0]);  // OK
  int64_t y[kSize] {};
  result = sum(y);  // OK, result == 3
  int64_t y2[kSize + 1] {};
  result = sum(y2);  // OK, result == 4
  int64_t z[0];
  static_assert(std::is_bounded_array_v<decltype(z)>);
  static_assert(not std::is_unbounded_array_v<decltype(z)>);

  extern int64_t ext[];
  result = sum(ext);  // OK, result == 4
  result = sum(static_cast<int64_t(&)[]>(y));  // OK, result == 4
//   result = sum(static_cast<int64_t(&)[10]>(ext));  // error, invalid 'static_cast'
  
  func(x);  // void func(T) [with T = int*]
  func2(x);  // void func2(T&&) [with T = int (&)[10]]
  return result;
}