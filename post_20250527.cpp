#include <iostream>

template<unsigned N>
struct reader {
    friend consteval auto flag(reader<N>);
};

template<int N>
struct Writer {
    friend consteval auto flag(reader<N>) { return true; }
    static constexpr int value {N};
};

template<auto Tag, int NextVal = 0>
[[nodiscard]]
consteval int counter_impl() {
    if constexpr (requires(reader<NextVal> r) { flag(r); }) {
        return counter_impl<Tag, NextVal + 1>();
    } else {
        return Writer<NextVal>::value;
    }
}

template<auto Tag = []{}, int Val = counter_impl<Tag>()>
constexpr int counter {Val};

template <class T>
struct F {
    friend constexpr auto f(F);
    //friend constexpr void f(F);
};

struct U {
    friend constexpr auto f(F<int>) {};
};

template <class T>
void check() {
    if constexpr (requires(F<T> r) {
        f(r);
    }) {
        std::cout << " yes " << std::endl;
    } else {
        std::cout << " no " << std::endl;
    }
}


int main() {
    check<int>();

    static_assert(counter<> == 0);
    static_assert(counter<> == 1);
    static_assert(counter<> == 2);
    static_assert(counter<> == 3);
    static_assert(counter<> == 4);
    static_assert(counter<> == 5);
    static_assert(counter<> == 6);
    static_assert(counter<> == 7);
    static_assert(counter<> == 8);
    static_assert(counter<> == 9);
    static_assert(counter<> == 10);
}
