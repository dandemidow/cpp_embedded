#include <iostream>
#include <array>
#include <cstdint>


class Secret {
  int32_t id {0x12345678};
  int32_t code {100};
};

template <int I>
using INT = std::integral_constant<int, I>;

template <auto, int Tag>
struct Stealer;

template <class S, int S::* Member, int Tag>
struct Stealer <Member, Tag> {
  friend int& dataGetter(Secret& iObj, INT<Tag>) {
    return iObj.*Member;
  }
};

template struct Stealer<&Secret::code, 0>;
template struct Stealer<&Secret::id, 1>;
int& dataGetter(Secret&, INT<0> = {});
int& dataGetter(Secret&, INT<1> = {});

int main() {
    {
        Secret s{};
        std::cout << dataGetter(s, INT<0>{}) << std::endl;
    }
  return 0;
}