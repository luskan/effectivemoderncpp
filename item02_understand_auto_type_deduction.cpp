//
// Created by marcin on 12.01.17.
//

#include <initializer_list>
#include "item02_understand_auto_type_deduction.h"

//
// std:initializer_list

// OK!
auto foo() {
    return std::initializer_list<int>({1,2,3});
}

// BAD!
//auto foo2() {
//    return {1,2,3};
//}


// Will not compile,
template<typename T> void foo2(T t) {}

void item2_understand_auto_type_deduction::run() {

    // init list
    auto res = foo();

    // will not compile
    // std::initializer list is non deduced context
    //foo2({1,2,3});

    // now its ok
    foo2<std::initializer_list<int>>({1,2,3});
    foo2(std::initializer_list<int>({1,2,3}));

    //const auto il {'a', 'b', 'c'};
}
