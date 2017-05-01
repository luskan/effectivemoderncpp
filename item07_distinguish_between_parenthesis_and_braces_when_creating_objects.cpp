//
// Created by marcin on 16.01.17.
//

#include <atomic>
#include <initializer_list>
#include <iostream>
#include "item07_distinguish_between_parenthesis_and_braces_when_creating_objects.h"

class X {
public:
    int k;

    X(int,double){ std::cout << "X(int,double)\n";}
    X(int,bool){ std::cout << "X(int,bool)\n";}

    //below ctor will be prefered when X instance is created using braced initialization
    //X(std::initializer_list<long double>){ std::cout << "X(std::initializer_list<long double>)\n";}

    //below ctor will be prefered when X instance is created using braced initialization
    X(std::initializer_list<bool>){ std::cout << "X(std::initializer_list<bool>)\n";}

};

class X2 {
public:
    int k;
    X2(){ std::cout << __PRETTY_FUNCTION__ << "\n";}
    X2(int,double){ std::cout << __PRETTY_FUNCTION__ << "\n";}
    X2(int,bool){ std::cout << __PRETTY_FUNCTION__ << "\n";}
    X2(std::initializer_list<std::string>){ std::cout << __PRETTY_FUNCTION__ << "\n";}
};

void item7_distinguish_between_parenthesis_and_braces_when_creating_objects::run() {

    // "uniform initialization" is an idea
    // "braced initialization" is a syntatic construct

    int i(0);
    int i2 = 0;
    int i3 {0};
    int i4 = {0};

    //
    std::atomic<int> at(0);
    std::atomic<int> at2{0};
    //std::atomic<int> at3 = 0; // error: use of deleted function

    //int n{1.0f}; // error: narrowing conversion
    //int n = {1.0f}; // error: narrowing conversion
    int n(1.0f); // ok

    //X x();
    //x.k = 0; // ups: thats most vexing parse, as x is found to be a function declaration.
             //      this is because if c++ compiler sees a construct which might be a declaration or definition
             //      then it always chooses a definition.

    // Below called with X(std::initializer_list<long double>) commented out:
    X x1(0, 34.5);
    X x2(0, false);
    X x3{0, 34.5};
    X x4{0, false};

    // will output:
    //X(int,double)
    //X(int,bool)
    //X(int,double)
    //X(int,bool)

    // but with X(std::initializer_list<long double>), initializer_list ctor is choosen as best overload. So
    // the output is:
    //X(int,double)
    //X(int,bool)
    //X(std::initializer_list<long double>)
    //X(std::initializer_list<long double>)

    //
    // According to standard this is an illformed :
    //X x5{0,10.5};
    // compiler will try to match the std::initializer_list because it sees that it can convert
    // {0, 10,5} to {false, true}, but then the narrowing conversion is dissallowed rule kicks in
    // and an error is shown. No other overloads are tried.

    std::cout << "\ninitializer_list ctor is not used as there is no conversion to it\n";

    // X2 has a ctor taking initializer_list but of type std::string, since there is no way to convert
    // 0 or 34.5 and false to std::string this overload will not be regarded.
    X2 x21(0, 34.5);
    X2 x22(0, false);
    X2 x23{0, 34.5};
    X2 x24{0, false};

    // Will output:
    //X2::X2(int, double)
    //X2::X2(int, bool)
    //X2::X2(int, double)
    //X2::X2(int, bool)

    std::cout << "\nwhich is called: defaut constructor or initializer_list ctor with empty list?\n";

    X2 x31; // default ctor
    X2 x32{}; // default ctor !!
    X2 x33({}); // initializer_list ctor !!
    X2 x34{{}}; // initializer_list ctor !!
}

















