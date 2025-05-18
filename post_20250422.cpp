#include <iostream>
#include <array>
#include <cstdint>


class Secret {
  int32_t id {0x12345678};
  int32_t code {100};
};

template <int id, class R, class C>
struct Tag {
  using member = R C::*;
  inline static member m {};
};

template <class T, T::member t>
struct Outlaw {
  Outlaw(T::member tt) { T::m = tt; }
  static inline Outlaw instance {t};
};

using Secret_id = Tag<0, int32_t, Secret>;
template struct Outlaw<Secret_id, &Secret::id>;

struct Something {
    friend bool operator==(Something const &a, Something const &b) { return false; }
    friend void Print() {
        std::cout<<__PRETTY_FUNCTION__<<std::endl;
    }
};

template <class T>
struct CoolFeature {
};

// class Something {
//     int32_t value {40};
//     template struct CoolFeature<&Something::value>;
// };

//bool operator==(Something const a, Something const &b);
void Print();


int main() {
    Something a, b;
    a == b;
    Print();
    {
        Secret s{};
        std::cout << Tag<0, int32_t, Secret>::m << std::endl;
        std::cout << s.*Secret_id::m << std::endl;
    }
    return 0;
}