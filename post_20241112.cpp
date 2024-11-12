#include <cstdint>
#include <variant>

#define Types2 char, char
#define Types8 Types2, Types2, Types2, Types2
#define Types64 Types8, Types8, Types8, Types8, Types8, Types8, Types8, Types8
#define Types256 Types64, Types64, Types64, Types64

using VariantIntType = std::variant<int, int>;
static_assert(sizeof(VariantIntType) == 8);

using VariantCharType = std::variant<char, char>;
static_assert(sizeof(VariantCharType) == 2);

using VariantChar256Type = std::variant<Types256>;
static_assert(sizeof(VariantChar256Type) == 4);

using T100 = std::__select_int::_Select_int<'1','0','0'>::type::value_type;
static_assert(std::is_same_v<T100, uint8_t>);

using T1000 = std::__select_int::_Select_int<'1','0','0', '0'>::type::value_type;
static_assert(std::is_same_v<T1000, uint16_t>);

template <typename... _Types>
using select_index =
typename std::__select_int::_Select_int_base<sizeof...(_Types),
					      unsigned char,
					      unsigned short>::type::value_type;

static_assert(std::is_same_v<select_index<int>, uint8_t>);
static_assert(std::is_same_v<select_index<char>, uint8_t>);

static_assert(std::is_same_v<select_index<Types256>, uint16_t>);

int main() {
    
    return 0;
}