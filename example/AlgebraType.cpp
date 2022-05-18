#include <type_traits>

namespace type {
    struct empty final {
        virtual ~empty() = 0;
    };

    template<typename T1, typename T2>
    struct product;

    template<typename T1, typename T2>
    struct sum;

    template<typename T>
    struct baseType {
        using ret = T;
    };

    template<typename T>
    struct baseType < product<T, empty> > {
        using ret = empty;
    };

    template<typename T>
    struct baseType < product<empty, T> > {
        using ret = empty;
    };

    template<typename T>
    struct baseType < sum<T, empty> > {
        using ret = typename baseType<T>::ret;
    };

    template<typename T>
    struct baseType < sum<empty, T> > {
        using ret = typename baseType<T>::ret;
    };

    template<typename T1, typename T2>
    struct baseType< product<T1, T2> > {
        using ret = typename baseType<
            product<
                typename baseType<T1>::ret,
                typename baseType<T2>::ret
            >
        >::ret;
    };

    template<typename T1, typename T2, typename T3>
    struct baseType < product<sum<T1, T2>, T3> > {
        using ret = typename baseType<
            sum<
                product<T1, T3>,
                product<T2, T3>
            >
        >::ret;
    };

    template<typename T1, typename T2, typename T3>
    struct baseType < product<T1, sum<T2, T3> > > {
        using ret = typename baseType<
            sum<
                product<T1, T2>,
                product<T1, T3>
            >
        >::ret;
    };

    template<typename T1, typename T2>
    struct product {
    };

    template<typename T1, typename T2>
    struct sum {};
}

int main() {
    using namespace type;
    static_assert(std::is_same_v<baseType<empty>::ret, empty>);
    static_assert(std::is_same_v<baseType<int>::ret, int>);
    static_assert(std::is_same_v<
        baseType<sum<int, int> >::ret,
        sum<int, int>
    >);
    static_assert(std::is_same_v<
        baseType<sum<sum<int, int>, int> >::ret,
        sum<sum<int, int>, int>
    >);
    static_assert(std::is_same_v<
        baseType<product<sum<int, int>, int> >::ret,
        sum<product<int, int>, product<int, int> >
    >);
}
