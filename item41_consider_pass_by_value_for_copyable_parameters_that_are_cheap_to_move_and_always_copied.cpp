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

void item41_consider_pass_by_value_for_copyable_parameters_that_are_cheap_to_move_and_always_copied::run() {
  WidgetOverload wo;
  wo.addName("Test");
}
