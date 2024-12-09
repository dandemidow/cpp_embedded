#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <cstdio>

static_assert(std::is_same_v<std::type_identity_t<int>, int>);

template <class T>
T sum(T a, T b) { return a + b; }

template <class T>
T sum(T a, std::type_identity_t<T> b) { return a + b; }

template <class T>
void foo(std::type_identity_t<T>) {}

template <class T>
struct smart_pointer {
    smart_pointer(T *) {printf("%s\r\n", __PRETTY_FUNCTION__);}
};

template <class T>
struct smart_pointer2 {
    smart_pointer2(std::type_identity_t<T> *) {printf("%s\r\n", __PRETTY_FUNCTION__);}
};

struct Empty {} empty;

template <class T>
struct my_remove_const : std::type_identity<T> {};
template <class T>
struct my_remove_const<T const> : std::type_identity<T> {};

static_assert(std::is_same_v<typename my_remove_const<int>::type, int>);
static_assert(std::is_same_v<typename my_remove_const<int const>::type, int>);

int main() {
    // sum(0.F, 0);  // error: func(float, int)
    // sum(0.F, empty);
    // sum(0.F, "");
    sum(0.F, 0);

    // foo(1);  // no matching function for call to 'foo(int)'
    foo<int>(1);
    int arr[10] {};

    smart_pointer p {new int};
    smart_pointer p1 {arr};

    smart_pointer2<int> p2 {new int};
    smart_pointer2<int[10]> p3 {&arr};

    
    return 0;
}