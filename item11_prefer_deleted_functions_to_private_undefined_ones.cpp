//
// Created by marcin on 11.01.17.
//

#include <iostream>
#include "item11_prefer_deleted_functions_to_private_undefined_ones.h"

// Function

void foo(int n) {
    std::cout << "foo(int)\n";
}
//static void foo(char) = delete;
//static void foo(float) = delete;
//static void foo(double) = delete;

struct XA {
    operator int() {
        return 0;
    }
};

template<typename T>
void foo(T) = delete;

template<typename T>
void foo(T*) {
    std::cout << "foo(T*)\n";
}

template<>
void foo<float>(float) {
    std::cout << "foo<float>(float)\n";
}

void item11_prefer_deleted_functions_to_private_undefined_ones::run() {
    //foo('c');
    int i1 = 0;
    foo(i1);
    foo(123);
    foo((int*)0);
    //foo(XA{});
    //foo(0.2);
    foo(0.2f);
}
