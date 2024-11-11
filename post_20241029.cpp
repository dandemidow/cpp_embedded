// -std=c++20 -Wno-deprecated-declarations
#include <type_traits>
 
struct A { 
  constexpr A() : m{} {}
  A(int i) : m{i} {}
  int m; 
};
static_assert(std::is_literal_type_v<A> == true);
static_assert(std::is_literal_type_v<A &> == true);
 
struct B { constexpr ~B() {} };  // c++20
static_assert(std::is_literal_type_v<B> == true);

struct C {
  C() : m{} {}
  C(int i) : m{i} {}
  int m;
};
static_assert(std::is_literal_type_v<C> == false);
static_assert(std::is_literal_type_v<C &> == true);

constexpr int FUNC(int i) {
    A a{i};
    return i + a.m;
}

// error: non-constant condition for static assertion
// static_assert(FUNC(1) == 2);

int main() {
    // return 2
    return FUNC(1);
}