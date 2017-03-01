//
// Created by marci_000 on 17.02.2017.
//
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <boost/type_index.hpp>
#include <typeinfo>
#include "item25_use_std_move_on_rvalue_references_std_forward_on_universal_references.h"

using boost::typeindex::type_id_with_cvr;

class Widget {
public:
  Widget(std::string s) : name(s) {}
  Widget(Widget&& rhs) :
    // here move as rhs is rvalue reference, but it is lvalue (because its a parameter and has name), so we must cast
    // it to xvalue with std::move to make name field use rvalue reference constructor instead of regular lvalue one.
    name(std::move(rhs.name)) {
  }

  //
  template<typename T>
    void setName(T&& newName)
  {
    name = std::forward<T>(newName);
  }

private:
  std::string name;
};

class WrongUseOfMove {
 public:
  template<typename T>
  // On forwarding references (aka. universal references) std::move should never be used
  // as this is an unconditional cast. Always use std::forward. Te probable problem with
  // using std::move is when forwarding reference, referse to lvalue variable.
  WrongUseOfMove(T&& rhs)
  {
    //name = std::move(rhs.name); // Very wrong!!
    //name = std::forward<T>(rhs.name); // OK!!
    *this = std::forward<T>(rhs); // OK!!
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }

  //WrongUseOfMove& operator=(WrongUseOfMove&&) = default;
  //WrongUseOfMove& operator=(const WrongUseOfMove&) = default;

  WrongUseOfMove(){}

  std::string name;
};

struct CollectStrings {
  template<typename T>
  void add(T&& str) {
    std::string ss = str;
    auto now = std::chrono::system_clock::now();
    std::cout << "\n" << __PRETTY_FUNCTION__ << ": " << now.time_since_epoch().count() << ": " << str << "\n";
    vec.emplace_back(std::forward<T>(str));
  }
  std::vector<std::string> vec;
};

struct TestArg {
  TestArg() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestArg(std::string ss) {
    s = ss;
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestArg(const TestArg&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestArg(TestArg&&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestArg& operator=(const TestArg&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return *this;
  }
  TestArg& operator=(TestArg&&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return *this;
  }
  ~TestArg() {}
  std::string s;
};

TestArg operator+(TestArg&& lhs, const TestArg& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  lhs.s += " : ";
  lhs.s += rhs.s;
  //return lhs;           // without move a copy is being done, in output you will see:
                          //  TestArg::TestArg(const TestArg&)
  return std::move(lhs);  // now TestArg::TestArg(TestArg&&) is called which is optimal
}

TestArg operator+(const TestArg& lhs, const TestArg& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  TestArg res;
  res.s += " : ";
  res.s += rhs.s;
  return res;   // this results in RVO, as res is local variable
}

TestArg makeTestArg() {
  TestArg res("hello");
  return res;
}

TestArg makeTestArgMove() {
  TestArg res("hello");

  // No RVO here as std::move(res) does not fulfill RVO requirements. RVO can be aplied only if local variable is
  // returned, but here a reference! is being returned.
  return std::move(res);
}

TestArg makeTestArgMove(TestArg res) {

  // No RVO but compiler is oblidged to return by std::move even if not specified explicitly.
  return res;
}

void item25_use_std_move_on_rvalue_references_std_forward_on_universal_references::run() {

  // 1
  Widget w("test");
  Widget w2(std::move(w));

  // 2. Wrong use of std::move instead of std::forward
  WrongUseOfMove wm;
  WrongUseOfMove wm2 = wm;
  // here wm is "empty" as it was moved from in above line.

  // 3. Add forward as last line.
  CollectStrings cs;
  cs.add("test1");

  // 4. Proof of concept, parameters returned from function are not subject to RVO.
  std::cout << "\n4. -----\n";
  TestArg ta1("ta1");
  TestArg ta2("ta2");
  TestArg ta3("ta3");
  TestArg ta12 = ta1 + ta2 + ta3;

  // 5. using std::move when returning local object is always bad as it inhibits RVO
  std::cout << "\n5. Dont use std::move in return for local objects\n";
  std::cout << " - RVO - here single constructor should be executed - the res variable in makeTestArg is the same as a1 below\n";
  TestArg a1 = makeTestArg();
  std::cout << " - no RVO - here regular constructor should be executed to create res then move constructor to returned a2 variable\n";
  TestArg a2 = makeTestArgMove();

  // 6. Dont use std::move on returning a parameter, as compiler will use it anyway if it cant apply RVO. And using
  //    std::move explicitly always inhibits RVO.
  std::cout << "\n6. Dont use std::move in return for parameter objects, maybe use if they are rvalue references\n";
  TestArg res1 = makeTestArgMove(a1);
  // results in:
  //   TestArg::TestArg(const TestArg&)
  //   TestArg::TestArg(TestArg&&)  <---- evidence that compiler applied implicitly std::move in return statement
}

