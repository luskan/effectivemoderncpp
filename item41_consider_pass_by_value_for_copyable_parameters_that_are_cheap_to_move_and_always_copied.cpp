//
// Created by marci_000 on 30.04.2017.
//

#include "item41_consider_pass_by_value_for_copyable_parameters_that_are_cheap_to_move_and_always_copied.h"

#include <vector>
#include <iostream>
#include <string>

class WidgetOverload {
 public:

  // Rvalue reference overload, for calls like w.addName(
  void addName(std::string&& newName) {
    names.push_back(std::move(newName));
  }

  void addName(const std::string& newName) {
    names.push_back(newName);
  }

 private:
  std::vector<std::string> names;
};

// Well, actually it should be WidgetForwardingReference
class WidgetUniversalReference {
public:

  template<typename T>
  void addName(T&& newName) {
    names.push_back(std::forward<T>(newName));
  }

 private:
  std::vector<std::string> names;
};

class WidgetByValue {
public:
  void addName(std::string newName) {
    names.push_back(std::move(newName));
  }

 private:
  std::vector<std::string> names;
};

void item41_consider_pass_by_value_for_copyable_parameters_that_are_cheap_to_move_and_always_copied::run() {
  WidgetOverload wo;

  // User rvalue ref. overload
  wo.addName("Test");

  std::string someTest = "test";
  // User lvalue ref overload
  wo.addName(someTest);

  //
  //

  WidgetUniversalReference wur;

  // Here one single function is used in source code, but in object code it can result in multiple functions.
  wur.addName("Test");
  std::string someTest2 = "test";
  wur.addName(someTest);


}
