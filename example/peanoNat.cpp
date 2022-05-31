#include <type_traits>

template <typename T>
struct is_nat {
    constexpr static auto ret = false;
};

template <typename T>
concept nat = is_nat<T>::ret;

struct zero { };

template <nat v>
struct succ { };

template <>
struct is_nat<zero> {
    constexpr static auto ret = true;
};

template <nat pre_v>
struct is_nat<succ<pre_v> > {
    constexpr static auto ret = true;
};

template <nat v1, nat v2>
struct add;

template <nat v1>
struct add<v1, zero> {
    using ret = v1;
};

template <nat v1, nat pre_v2>
struct add<v1, succ<pre_v2> > {
    using ret = add<succ<v1>, pre_v2>::ret;
};

template <nat v>
struct convertToInt;

template <>
struct convertToInt<zero> {
    constexpr static auto ret = 0;
};

template <nat pre_v>
struct convertToInt<succ<pre_v> > {
    constexpr static auto ret = convertToInt<pre_v>::ret + 1;
};

using one = succ<zero>;
using two = succ<one>;
using three = succ<two>;

int main() {
    static_assert(std::is_same_v<add<zero, three>::ret, add<two, one>::ret>);
    static_assert(std::is_same_v<add<one, two>::ret, add<two, one>::ret>);
    static_assert(std::is_same_v<add<one, two>::ret, three>);

    static_assert(convertToInt<zero>::ret == 0);
    static_assert(convertToInt<one>::ret == 1);
    static_assert(convertToInt<two>::ret == 2);
    static_assert(convertToInt<three>::ret == 3);
}
