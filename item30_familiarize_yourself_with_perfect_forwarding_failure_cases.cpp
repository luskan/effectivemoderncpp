//
// Created by marci_000 on 24.03.2017.
//
#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

#include "item30_familiarize_yourself_with_perfect_forwarding_failure_cases.h"

using boost::typeindex::type_id_with_cvr;

static void func(std::vector<int> v) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

template<typename... Ts>
static void fwd(Ts&&... params) {
  func(std::forward<Ts>(params)...);
}

template <class... Tail>
struct Last {
  typedef typename Last<Tail...>::Type Type;
};

template <class Head>
struct Last<Head> {
  typedef Head Type;
};

static void funcPtr(int* ptr) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

template<typename... Ts>
static void fwdFuncPtr(Ts&&... params) {
  //std::cout << type_id_with_cvr<Last<typename Ts>::Type>().pretty_name() << "\n";
  funcPtr(std::forward<Ts>(params)...);
}

class Widget {
 public:
  static const int value_count = 123;
};

static void funcInt(int i){}
template<typename... Ts>
void fwdFuncInt(Ts&&... params) {
  funcInt(std::forward<Ts>(params)...);
}

static void funcOver(int (*pf)(int)) {
  std::cout << pf(123) << "\n";
}

static int funcCallInt(int n) {
  return n * 100;
}

static int funcCallInt(int n, int n2) {
  return n * 100 + n2;
}

template<typename... Ts>
static void fwdFuncOver(Ts&&... params) {
  funcOver(std::forward<Ts>(params)...);
}

///
///

struct SomeBitFieldStruct {
  std::uint_fast32_t field1 : 6,
                  field2 : 12,
                  field3 : 18;
};

static void funcCallValue(int value) {}
template<typename... Ts>
static void fwdFuncCallValue(Ts&&... params) {
  funcCallValue(std::forward<Ts>(params)...);
}

void item30_familiarize_yourself_with_perfect_forwarding_failure_cases::run() {

  std::cout << "Braced initializers\n";

  // This is ok!
  func({1,2,3});

  // That fails, as initializer list is non-deduced context when using template deducation
  // ... so perfect forwarding is not so perfect after all
  //fwd({1,2,3});

  // Now, a fix is to use temp variable for our list.
  auto init = {1,2,3};
  fwd(init);

  std::cout << "\n\n0 or NULL as null pointers\n";
  funcPtr(NULL);
  // This will result in error, as compiler will treat NULL as long long int, insterad of pointer
  //fwdFuncPtr(NULL);   // error: invalid conversion from 'long long int' to 'int*'
  fwdFuncPtr(nullptr); // thats fine!

  std::cout << "\n\nDeclaration-only integral static const and constexpr data\n";
  funcInt(Widget::value_count);
  //fwdFuncInt(Widget::value_count); // this is implementation defined, under windows mingw 6.3 it gives no linker error
                                     //  but with gcc 6.3 and linux you will get linker error.

  std::cout << "\n\nOverloaded function names and template names\n";

  // This call is ok, even thought funcCallInt is overloaded, compiler is able to choose correct
  // overload by looking at the parameter type.
  funcOver(funcCallInt);

  // This is wrong, as compiler is not able to deduce correct overload for funcOver call.
  // So again, perfect forwarding is not so perfect.
  //fwdFuncOver(funcCallInt); // error

  // A fix to to cast function argument to correct overload.
  fwdFuncOver(static_cast<int(*)(int)>(funcCallInt));

  std::cout << "\n\nBit-fields\n";
  SomeBitFieldStruct data;
  data.field1 = 6;
  data.field2 = 7;
  data.field3 = 8;
  funcCallValue(data.field3);
  //fwdFuncCallValue(data.field3); // error: bitfield cannot be bound to non const reference
  fwdFuncCallValue(static_cast<int>(data.field3));
}
