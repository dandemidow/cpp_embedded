#include <iostream>
#include <array>
#include <cstdint>


class Secret {
  int32_t id {0x12345678};
  int32_t code {100};
};

class TSecret {
  int32_t id {0x12345678};
  int32_t code {100};
public:
  template <class T>
  int get() { return 0; }
};

template <class T>
class T2Secret {
  int32_t id {0x12345678};
  int32_t code {100};
public:
  int get() { return 0; }
};


template <>
int TSecret::get<int>() {
    std::cout << id << " - "<< code << std::endl;
    return 1;
}
template <>
int T2Secret<int>::get() {
    std::cout << id << " = " << code << std::endl;
    return 1;
}

template <>
int& std::array<int, 10>::front() noexcept { 
std::cout << "   " << this->_M_elems[0] << std::endl; return *begin(); 
}


int main() {
    TSecret u{};
    u.get<int64_t>();
    T2Secret<int> y{};
    y.get();
    std::array<int, 10> t{};
    t.front();
    return 0;
}