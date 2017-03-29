//
// Created by marci_000 on 23.03.2017.
//

#include <iostream>
#include <array>
#include <vector>
#include "item29_assume_that_move_operations_are_not_present_not_cheap_and_not_used.h"

class TestC {
 public:
  TestC() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestC(const TestC&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestC(TestC&&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestC& operator=(TestC&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestC& operator=(TestC&&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
};

class TestCNoExcept {
 public:
  TestCNoExcept() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestCNoExcept(const TestCNoExcept&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestCNoExcept(TestCNoExcept&&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestCNoExcept& operator=(TestCNoExcept&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  TestCNoExcept& operator=(TestCNoExcept&&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
};

void item29_assume_that_move_operations_are_not_present_not_cheap_and_not_used::run() {
  std::array<TestC, 3> arr;

  // Copy array and elements.
  // Only 'TestC::TestC(const TestC&)' will be in output
  std::cout << "\n\n";
  std::array<TestC, 3> arr2 = arr;

  // Copy array and move elements.
  // Only 'TestC::TestC(const TestC&&)' will be in output
  std::cout << "\n\n";
  std::array<TestC, 3> arr3 = std::move(arr);

  // Now lets do the same thing with std::vector
  std::vector<TestC> vec(3);

  // Copying will call copy constructors
  std::cout << "\n\nVector...\n\n";
  std::vector<TestC> vec1 = vec;

  // Now move will result in using simply copying pointer to heap array from vec to vec2. So no TestC constructor
  // will be called.
  std::cout << "\n\nnothing here...\n";
  std::vector<TestC> vec2 = std::move(vec);

  // Now lets see if resize will use move operations...
  // ... TestC::TestC(const TestC&) will be used, because the are non-noexcept
  std::cout << "\n\nnothing here...\n";
  vec2.resize(6);

  // Now lets make move operations noexcept, now resize should use move copy constructor
  // TestCNoExcept::TestCNoExcept(TestCNoExcept&&) will show in output
  std::cout << "\n\nTest to prove that move ctors will be shown if no except copy ctor is implemented. \n";
  std::cout.setstate(std::ios_base::failbit);
  std::vector<TestCNoExcept> vec3{3};
  std::cout.clear();
  vec3.resize(6);
}
