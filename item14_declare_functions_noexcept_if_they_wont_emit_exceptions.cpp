//
// Created by marci_000 on 29.01.2017.
//

#include "item14_declare_functions_noexcept_if_they_wont_emit_exceptions.h"
#include <iostream>
#include <vector>

struct TestDataWithoutNoexcept {
  static bool allowLog;
  TestDataWithoutNoexcept() {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  ~TestDataWithoutNoexcept() {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestDataWithoutNoexcept(TestDataWithoutNoexcept const & rhs) {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestDataWithoutNoexcept(TestDataWithoutNoexcept && rhs) {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestDataWithoutNoexcept& operator=(TestDataWithoutNoexcept const& rhs) {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
};
bool TestDataWithoutNoexcept::allowLog = false;

struct TestDataWithNoexcept {
  static bool allowLog;
  TestDataWithNoexcept() noexcept {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  ~TestDataWithNoexcept() {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestDataWithNoexcept(TestDataWithNoexcept const & rhs) noexcept {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestDataWithNoexcept(TestDataWithNoexcept && rhs) noexcept {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestDataWithNoexcept& operator=(TestDataWithNoexcept const& rhs) noexcept {
    if (allowLog)
      std::cout << __PRETTY_FUNCTION__ << "\n";
  }
};
bool TestDataWithNoexcept::allowLog = false;

struct TestDTorNoExcept {
  TestDTorNoExcept() {}
  ~TestDTorNoExcept() noexcept(false)// since c++11 noexcept(false) is required if you want to catch this exception
  // ~TestDTorNoExcept() throw() // c++03 equivalence, but throw() forces compler to unwind stack anyway
  {
                                          //
    // it is discouraged to throw in dtor, thats why since c++11 all dtors (user defined/or generated)
    // are always noexcept
    // !! - objects of classes with throwing destructors should not be used with STL classes as this causes UB.
    throw std::runtime_error("DTor - except");
  }
};

void NoExceptFunctionWithObj1() noexcept {
  TestDataWithoutNoexcept test;
  throw std::runtime_error("NoExceptFunctionWithObj1 ex.");
}

void NoExceptFunctionWithObj2() throw() {
  TestDataWithoutNoexcept test;
  throw std::runtime_error("NoExceptFunctionWithObj2 ex.");
}

void item14_declare_functions_noexcept_if_they_wont_emit_exceptions::run() {

  // Test dtors being noexcept by default
  std::cout << "Test noexcept dtors\n";
  try {
    TestDataWithoutNoexcept ts;
    TestDTorNoExcept t;
  }
  catch(const std::runtime_error& ex) {
    std::cout << "Trying to catch: " << ex.what();
  }

  std::cout << "\n\n";
  std::cout << "\n\n";

  // Test how vector uses move constructor when NO noexcept is used on it
  std::cout << "Test vector with object of type with NO noexcept.\n";
  TestDataWithoutNoexcept::allowLog = false;
  std::vector<TestDataWithoutNoexcept> vec1;
  vec1.push_back(TestDataWithoutNoexcept());
  vec1.push_back(TestDataWithoutNoexcept());
  vec1.shrink_to_fit();

  // Now lets see what will happen when adding new element, this will require reallocation and copying of data
  // no Move will be performed which is not very efficient.
  TestDataWithoutNoexcept td;
  TestDataWithoutNoexcept::allowLog = true;
  vec1.push_back(td);

  //
  // Now the same test, but with object with noexcept copy/move constructors
  std::cout << "\n\n";
  std::cout << "Test vector with object of type with noexcept.\n";
  TestDataWithNoexcept::allowLog = false;
  std::vector<TestDataWithNoexcept> vec2;
  vec2.push_back(TestDataWithNoexcept());
  vec2.push_back(TestDataWithNoexcept());
  vec2.shrink_to_fit();

  // Now move constructor will be seen
  TestDataWithNoexcept td2;
  TestDataWithNoexcept::allowLog = true;
  vec2.push_back(td2);

  TestDataWithNoexcept::allowLog = false;
  TestDataWithoutNoexcept::allowLog = false;

  // Now lets see whether stack is being unwound when exception is thrown in noexcept versus throw() function.
  std::cout << "\n See how dtors are called in noexcept or throw() functions\n";
  try {
    //NoExceptFunctionWithObj1();
  }
  catch(std::runtime_error& ex) {
    std::cout << ex.what();
  }

  try {
    NoExceptFunctionWithObj2();
  }
  catch(std::runtime_error& ex) {
    std::cout << ex.what();
  }
}
