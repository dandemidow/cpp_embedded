#include <algorithm>
#include <cassert>
#include <ranges>
#include <vector>
#include <functional>
#include <ext/functional>

struct X {
  int x;
};

int main() {
  int x {42};
  assert(x == std::identity{}(x));
  assert(x == __gnu_cxx::identity<int>{}(x));

  std::vector<int> w {{1, 2, 3}};
  auto projection = [](int x) { return x + 10; };
  auto result = std::ranges::all_of(w, [](int x){ return x < 10; }, projection);
  assert(not result);

  std::vector<X> w2 {{X{1}, X{2}, X{3}}};
  result = std::ranges::all_of(w2, 
                               [](int x){ return x < 10; }, 
                               [](X x) { return x.x + 10; });

  assert(not result);

  return 0;
}
