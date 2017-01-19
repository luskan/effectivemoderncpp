//
// Created by marcin on 14.01.17.
//

#include "item3_understand_decltype.h"
#include <boost/type_index.hpp>
#include <iostream>
#include <array>

using boost::typeindex::type_id_with_cvr;

template<typename T>
struct VK {
    std::array<T, 5> arr;
    T& operator[](int n) {
        return arr[n];
    }
};

template<typename Cont, typename Index>
auto authAndAccess(Cont& c, Index i) /*since c++14 its not needed: -> decltype(c[0])*/ {
    return c[i];
}

template<typename Cont, typename Index>
decltype(auto) authAndAccess2(Cont& c, Index i) {
    return c[i];
}

void item3_understand_decltype::run() {

    // Typical cases
    const int i = 0;
    std::cout << type_id_with_cvr<decltype(i)>().pretty_name() << "\n";

    const int& ri = i;
    std::cout << type_id_with_cvr<decltype(ri)>().pretty_name() << "\n";

    VK<int> vk;
    std::cout << type_id_with_cvr<decltype(vk[1])>().pretty_name() << "\n";
    // int& as in operator[]

    std::cout << "\nauto used in function declaration will deduce type stripped of reference (as auto does normally)\n";
    // Below indicates that auto in authAndAccess will strip referencness, which is
    // not what we want here.
    std::cout << type_id_with_cvr<decltype(authAndAccess(vk, 0))>().pretty_name() << "\n";
    // on output is: int, but we want int&

    // The solution is to use decltype(auto) instead of auto
    std::cout << type_id_with_cvr<decltype(authAndAccess2(vk, 0))>().pretty_name() << "\n";
    // on output int&

    // You may use decltype(auto) in the same places as auto:
    std::cout << "\nauto variable is assigned reference type, this should stripp reference\n";
    auto a1 = ri;
    std::cout << type_id_with_cvr<decltype(a1)>().pretty_name() << "\n";
    std::cout << "\nnow we will have a true type as in argument\n";
    decltype(auto) a2 = ri;
    std::cout << type_id_with_cvr<decltype(a2)>().pretty_name() << "\n";

    // decltype applied to a name yields declared type for that name, but applied to expression yields a reference.
    std::cout << "\ndecltype applied to name and expressions\n";
    int n = 0;
    std::cout << type_id_with_cvr<decltype(n)>().pretty_name() << "\n";
    std::cout << type_id_with_cvr<decltype((n))>().pretty_name() << "\n";
    std::cout << type_id_with_cvr<decltype(1+1)>().pretty_name() << "\n";
    std::cout << type_id_with_cvr<decltype((1+1))>().pretty_name() << "\n";
}
































