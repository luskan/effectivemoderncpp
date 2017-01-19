//
// Created by marcin on 07.01.17.
//

#include <iostream>
#include <memory>
#include "item8_prefer_nullptr_to_0_and_null.h"

namespace {

    void f(int) { std::cout << "f(int)\n"; }
    void f(bool) { std::cout << "f(bool)\n"; }
    void f(void *) { std::cout << "f(void*)\n"; }

    struct Widget{};

    int f1(std::shared_ptr<Widget> spw) { std::cout << "int f1(std::shared_ptr<Widget> spw)\n"; return 0; }
    double f2(std::unique_ptr<Widget> upw) { std::cout << "double f2(std::unique_ptr<Widget> upw)\n"; return 0; }
    bool f3(Widget* pw) { std::cout << "bool f3(Widget* pw)\n"; return false; }

    template<typename FuncType, typename PtrType>
    auto makeCall(FuncType func, PtrType ptr) -> decltype(func(ptr)) {
        return func(ptr);
    };
}

void item8_prefer_nullptr_to_0_and_null::run() {
    std::cout << "item8" << std::endl;

    //
    //

    f(0); //f(int)
    //f(NULL); // gcc: does not compile, it tries to execute each f. It works like if NULL was 0L, even tho it is a mysterious: __null
             // vs: probably the sam eas f(0)
    f(nullptr); //f(void*)

    //
    //

    //f1(0); f1(false); f1('\0'); // 0 is contagious, it works but only for 0-like, if used with 1,2,.. it wont compile (see: http://stackoverflow.com/questions/28588827/implicit-conversion-from-int-to-shared-ptr)
    f2(NULL);
    f3(nullptr);


    // Causes error, int cannot be converted to shared_ptr
    //makeCall(f1, 0);
    // This is the same case as:
    //int pi = 0; f1(pi);

//    makeCall(f2, NULL);
  //  makeCall(f3, nullptr);
}
