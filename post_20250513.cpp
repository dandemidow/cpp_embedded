#include <iostream>
#include <array>
#include <cstdint>

template<int N>                      
struct Flag {
  friend constexpr bool flag(Flag<N>);
};

template<int N>
struct Writer {
  friend constexpr bool flag(Flag<N>) { 
    return true; 
  }
  static constexpr int value = N;
};

template<int N = 0>
constexpr int reader(float) {
  return Writer<N>::value;
}

template<int N = 0,
         bool = flag(Flag<N>{}),
         auto = []{}>
constexpr int reader(int) {
  return reader<N + 1>(int{});
}

static_assert(not std::is_same_v<decltype([](){}), decltype([](){})>);

int main() {

    static_assert(next() == 0);
    static_assert(next() == 1);
    static_assert(next() == 2);


  return 0;
}