//
// Created by marcin on 07.01.17.
//

#include <type_traits>
#include <cxxabi.h>
#include <boost/type_index.hpp>
#include <iostream>
#include "item09_prefer_alias_declarations_to_typedefs.h"

using boost::typeindex::type_id_with_cvr;

namespace {
    void foo(int){}

    template<typename T>
    void foo(const T& t) {
        //skips cv&
        std::cout << "Type using typeid: " << __cxxabiv1::__cxa_demangle(typeid(decltype(t)).name(),0,0,0) << "\n";
        std::cout << "Boost index type : " << type_id_with_cvr<decltype(t)>().pretty_name() << "\n";

        // typename and ::type required (c++11)
        using test_t = typename std::remove_const<decltype(t)>::type;

        // no need for typename nor ::type (c++14)
        using test2_t = std::remove_const_t<decltype(t)>;
        std::cout << "Modified type    : " << type_id_with_cvr<test2_t>().pretty_name() << "\n";


    }
}

void item9_prefer_alias_declarations_to_typedefs::run() {

    typedef void (*FV)(int);
    using FV2 = void(*)(int);

    FV fv = foo;
    FV2 fv2 = foo;

    const int n = 10;
    foo<>(n);
}
