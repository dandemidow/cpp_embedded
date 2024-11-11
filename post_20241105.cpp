#include <iostream>
#include <cstdint>
#include <variant>

using _Val = std::__parse_int::_Parse_int<'1', '0'>;
static_assert(_Val::value == 10U);  // OK

template<char ... _Digits>
double operator ""_x() {
  // just to show the signature
  std::cout << "sign: " << __PRETTY_FUNCTION__ << std::endl;
  return 0.;
}

struct Hour {
  uint32_t value;
};

template <char... _Digits>
constexpr Hour operator""_H() { 
  using _Val = std::__parse_int::_Parse_int<_Digits...>; 
  static_assert(_Val::value < 24U, "literal value is wrong!");
  return Hour {_Val::value};
}

int main() {

  [[maybe_unused]] auto x = 10_x;

  constexpr auto h1 = 10_H;
  static_assert(h1.value == 10);  // OK

  // error: static assertion failed: literal value is wrong!
  // constexpr auto h2 = 25_H;

  return 0;
}