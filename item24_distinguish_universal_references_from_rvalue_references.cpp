//
// Created by marci_000 on 13.02.2017.
//
#include <vector>
#include "item24_distinguish_universal_references_from_rvalue_references.h"

template<typename T>
struct NotUniversalRef {
 public:
  // This is a rvalue reference, thats beause there is no T template type deduction here.
  void foo(T&&) {
  }
};

// Incorrect template declaration type - it should be T&&
template<typename T> void foo(std::vector<T>&&)
{
}

class NonMoveable {
 public:
  NonMoveable(const NonMoveable&){}
};

struct LargeClass {
  LargeClass(std::vector<NonMoveable>&& nonmov) : cpy(std::move(nonmov)) {

  }
  std::vector<NonMoveable> cpy;
};

void item24_distinguish_universal_references_from_rvalue_references::run() {
  NotUniversalRef<int> nur;
  nur.foo(1);

  //int nn=1;
  //nur.foo(nn);  // error: cannot bind 'int' lvalue to 'int&&' - thats correct foo accepts only rvalue refs.

  std::vector<int> vec1;
  //foo(vec1);    // same as above
  foo(std::move(vec1)); // now ok - its rvalue ref.

  // That is ok, we are passing a rvalue
  foo(std::vector<int>());

  // universal ref using auto&&, auto type deduction has actually exact transformation to function type deduction.
  // template<typename T>
  // void foo(T&& param);
  // - T is hidden in auto expression
  // - && is a param type modifier
  auto&& rvec = vec1;

  // For universal references you need 'type deduction' and special form of template type argument: 'T&&'
  std::vector<NonMoveable> vec2;
  LargeClass lc(std::move(vec2));

}
