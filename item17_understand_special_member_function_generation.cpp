//
// Created by marci_000 on 02.02.2017.
//

#include <type_traits>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "item17_understand_special_member_function_generation.h"

// refs:
// http://stackoverflow.com/questions/33939687/how-can-i-check-if-a-move-constructor-is-being-generated-implicitly/33947302#33947302

class Movable {
 public:
  Movable() {}

  // this makes move operations to be not generated,
  // but is_move_constructible will still return true.
  //Movable(Movable const&)  {}

  std::string ss;
};

class NonMovable {
 public:
  NonMovable() {}

  NonMovable(NonMovable const&)  {}
  //NonMovable(NonMovable &&) = delete;

  std::string ss;
};

// This is a wired way to find if class (here NonMovable) has default move operations.
// This triggers a compile-time error if the defaulted function would be implicitly defined as deleted.
// http://stackoverflow.com/questions/33939687/how-can-i-check-if-a-move-constructor-is-being-generated-implicitly/33947302#33947302
class CheckIfHasDefaultMoveOperations {
 public:
  CheckIfHasDefaultMoveOperations() = default;

  CheckIfHasDefaultMoveOperations(CheckIfHasDefaultMoveOperations const&) = default;
  CheckIfHasDefaultMoveOperations& operator=(CheckIfHasDefaultMoveOperations const&) = default;

  CheckIfHasDefaultMoveOperations(CheckIfHasDefaultMoveOperations &&) noexcept;
  CheckIfHasDefaultMoveOperations& operator=(CheckIfHasDefaultMoveOperations &&);

  ~CheckIfHasDefaultMoveOperations() = default;

  // uncomment to see compiler error indicating that NonMovable has no move operatons
  //NonMovable dd;
  Movable mm;
};
inline CheckIfHasDefaultMoveOperations::CheckIfHasDefaultMoveOperations(CheckIfHasDefaultMoveOperations &&) noexcept = default;
inline CheckIfHasDefaultMoveOperations& CheckIfHasDefaultMoveOperations::operator=(CheckIfHasDefaultMoveOperations &&) = default;

// Templated version does not work!
template<typename T>
class CheckIfHasDefaultMoveOperationsTempl {
 public:
  CheckIfHasDefaultMoveOperationsTempl() = default;

  CheckIfHasDefaultMoveOperationsTempl(CheckIfHasDefaultMoveOperationsTempl const&) = default;
  CheckIfHasDefaultMoveOperationsTempl& operator=(CheckIfHasDefaultMoveOperationsTempl const&) = default;

  CheckIfHasDefaultMoveOperationsTempl(CheckIfHasDefaultMoveOperationsTempl &&) noexcept;
  CheckIfHasDefaultMoveOperationsTempl& operator=(CheckIfHasDefaultMoveOperationsTempl &&);

  ~CheckIfHasDefaultMoveOperationsTempl() = default;

  T t;
};

template<typename T>
inline CheckIfHasDefaultMoveOperationsTempl<T>::CheckIfHasDefaultMoveOperationsTempl(CheckIfHasDefaultMoveOperationsTempl &&) noexcept = default;
template<typename T>
inline CheckIfHasDefaultMoveOperationsTempl<T>& CheckIfHasDefaultMoveOperationsTempl<T>::operator=(CheckIfHasDefaultMoveOperationsTempl &&) = default;


class LogClass {
 public:
  LogClass() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  ~LogClass() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  LogClass(LogClass const&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  LogClass(LogClass &&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  LogClass& operator=(LogClass &) noexcept {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return *this;
  }
  LogClass& operator=(LogClass &&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return *this;
  }
};

//
class Base {
};

class TestNonMovable {
 public:
  TestNonMovable(){}
  TestNonMovable(const TestNonMovable&){}
  TestNonMovable& operator=(const TestNonMovable&){}
  //LogClass log;
  TestNonMovable(TestNonMovable&&) = delete;
  //std::string d;// - funny but under mingw it causes crashes
};

class Derived : public Base {
  //NonMovable nm;
  TestNonMovable tnm;
  LogClass log;
};

void item17_understand_special_member_function_generation::run() {

  // Yep, NonMovable is move constructible.
  // but if :
  // NonMovable(NonMovable &&) = delete;
  // is uncommented then below assert fails. This is because deleted move constructor takes part in
  // overload resolution. But then is found to be deleted which causes compile error.
  //static_assert(std::is_move_constructible<Movable>::value,"");

  // this will work (to find if there is default move ctor) only if copy constructor is throwing (without noexcept)
  //static_assert(std::is_nothrow_move_constructible<NonMovable>::value,"");

  // This does not work even thought non templated version does generate error. Why?
  // see (no answer as for 02/02/17).: http://stackoverflow.com/questions/41992993/check-if-move-constructor-is-generated-implicitly-templated-method
  //CheckIfHasDefaultMoveOperationsTempl<NonMovable> ci;

  // Below, move semantics will be not used only if:
  //  TestNonMovable(TestNonMovable&&) = delete;
  // will be explicitly declared. The fact that move operations for TestNonMovable are not implicitly
  // generated does not inhibit move semantics in classes where TestNonMovable is used.
  // Some more deep explanation whats going on here:
  //  http://stackoverflow.com/questions/42051361/why-does-c-allow-you-to-move-classes-containing-objects-with-deleted-move-oper
  {
    //TestNonMovable tnm;
    //TestNonMovable tnm2 = std::move(tnm);

    Derived d1;
    Derived d2 = std::move(d1);
    std::vector<Derived> dv;
    dv.shrink_to_fit();
    dv.push_back(Derived{});
    dv.push_back(Derived{});
    dv.push_back(Derived{});
  }
}
