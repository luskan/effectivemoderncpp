//
// Created by marcin on 13.01.17.
//

#include <boost/type_index.hpp>
#include <iostream>
#include "item1_understand_template_type_deduction.h"

using boost::typeindex::type_id_with_cvr;

template<typename T>
void f_case1a(T& param){
    std::cout << "T is " << type_id_with_cvr<T>().pretty_name() << ", param is: " << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
}

template<typename T>
void f_case1b(T const& param){
    std::cout << "T is " << type_id_with_cvr<T>().pretty_name() << ", param is: " << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
}

template<typename T>
void f_case2a(T&& param){
    std::cout << "T is " << type_id_with_cvr<T>().pretty_name() << ", param is: " << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
}

template<typename T>
void f_case3(T param){
    std::cout << "T is " << type_id_with_cvr<T>().pretty_name() << ", param is: " << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
}


template<typename T>
void f_case_arr(T param){
    std::cout << "T is " << type_id_with_cvr<T>().pretty_name() << ", param is: " << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
}

template<typename T>
void f_case_arr2(T& param){
    std::cout << "T is " << type_id_with_cvr<T>().pretty_name() << ", param is: " << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
}

template<typename T>
void f_case_arr3(T&& param){
    std::cout << "T is " << type_id_with_cvr<T>().pretty_name() << ", param is: " << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
}

void item1_understand_template_type_deduction::run() {
    // three cases of type deduction:

    //
    // 1. ParamType is a pointer or reference but not universal reference.

    // - if expr (argument) is a reference then ignore reference part
    // - then pattern match exprs type against ParamType to determine T

    int x = 27;
    const int cx = x;
    const int& rx = x;

    std::cout << "1. (T const& param)\n";
    f_case1a(x);
    f_case1a(cx);
    f_case1a(rx);

    // Results in T being:
    //int
    //int const
    //int const
    // so T is non reference, and at most const.

    std::cout << "\n1. (T const& param)\n";
    f_case1b(x);
    f_case1b(cx);
    f_case1b(rx);

    // Results in T being:
    //int&
    //int const&
    //int const&
    // so T is non reference, and non const.

    // 2. ParamType is a universal reference

    std::cout << "\n2. (T && param)\n";
    f_case2a(x);
    f_case2a(cx);
    f_case2a(rx);
    f_case2a(27);
    f_case2a(std::string(""));

    // Results in in T being:
    //int&
    //int const&
    //int const&
    // so if lvalue is passed in, then compiler will make T and ParamType cv qualified lvalue reference

    //int &&
    //std::string&&
    // but if you provide an rvalue - then you will get rvalue reference

    // 3. ParamType is neither a pointer nor a reference
    std::cout << "\n3. (T param)\n";
    f_case3(x);
    f_case3(cx);
    f_case3(rx);
    f_case3(27);
    f_case3(std::string(""));
    const char* psz = "";
    f_case3(psz); // just a proof of concept, T and ParamType are here: char const*

    std::string ss;
    f_case3(std::move(ss));

    //int
    //int
    //int
    //std::string
    //char const*
    //std::string
    // so its always a type of argument stripped of both cv qualification and referencness

    std::cout << "\nArray tests. (T param)\n";
    char arr[123];
    f_case_arr(arr);

    std::cout << "\nArray tests. (T& param)\n";
    f_case_arr2(arr);

    std::cout << "\nArray tests. (T&& param)\n";
    f_case_arr3(arr);

    std::cout << "\nFunction pointer tests. (T param)\n";
    void (*func)(int);
    f_case_arr(func);

    std::cout << "\nArray tests. (T& param)\n";
    f_case_arr2(func);

    std::cout << "\nArray tests. (T&& param)\n";
    f_case_arr3(func);
}
