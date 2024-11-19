#include <type_traits>
#include <cstdint>

void panic_at_the_disco() {
    throw 1;
}

int lovely_atoi(const uint8_t *ptr) {
    static_assert(std::is_same_v<decltype(*ptr - '0'), int32_t>);
    int result = 0;
    while (*ptr) {
        int dig = *ptr - '0';
        if (dig < 0 || dig > 9) {
            panic_at_the_disco();
        }
        result *= 10;
        result += dig;
        ptr++;
    }
    return result;
}

static_assert(not std::is_same_v<char, int8_t>);
static_assert(std::is_same_v<decltype('0'), char>);
static_assert(std::is_same_v<decltype(0x30), int32_t>);
static_assert(std::is_same_v<decltype(48), int32_t>);

static_assert(0x80000000 == -0x80000000);
static_assert(std::is_same_v<decltype(0x80000000), uint32_t>);
static_assert(std::is_same_v<decltype(2147483648), int64_t>);

int main() {
    int x = lovely_atoi((const uint8_t*)"145");
    return x;
}