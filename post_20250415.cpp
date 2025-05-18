#include <iostream>
#include <array>
#include <cstdint>

#define private public
#define class struct

class TooSecret {
  int32_t id {0x12345678};
  int32_t code {42};
};

#undef class
#undef private

struct SecretPub {
  int32_t id;
  int32_t code;
};

class Secret {
  int32_t id {0x12345678};
  int32_t code {100};
};

struct Weird {
    uint8_t ptr[0];
};

struct SomeMemoryLayout {
    uint8_t x {0xAA};
    Weird r {};
    uint8_t y {0x55};
};

int main() {
    SomeMemoryLayout s{};
    std::cout << "test s = " << (uint32_t)(s.r.*((uint8_t Weird::*){})) << std::endl;
    std::cout << "test s = " << (uint32_t)(*(s.r.ptr)) << std::endl;
    
    {
        TooSecret s {};
        std::cout << "secret: " << s.code << std::endl;
    }
    {
        Secret s {};
        uint8_t *tmp = reinterpret_cast<uint8_t *>(&s);
        int *code = reinterpret_cast<int32_t *>(tmp + sizeof(int32_t));
        std::cout << "secret: " << *code << std::endl;
    }
    {
        using member = int32_t Secret::*;
        Secret s {};
        uint64_t offset{4};
        member m {std::bit_cast<member>(offset)};
        std::cout << "secret: " << s.*m << std::endl;
    }
    {
        using member = int32_t Secret::*;
        Secret s {};
        member m {reinterpret_cast<member>(&SecretPub::code)};
        std::cout << "secret: " << s.*m << std::endl;
    }
    return 0;
}