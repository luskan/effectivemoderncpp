//
// Created by marci_000 on 03.04.2017.
//

#include "item32_use_init_capture_to_move_objects_into_closures.h"

#include <iostream>
#include <vector>
#include <functional>

using namespace std::placeholders;

struct Test {
  void foo() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
};

void item32_use_init_capture_to_move_objects_into_closures::run() {

  std::cout << "C++14 init capture\n";
  std::vector<int> vec = {0,1,2};
  auto fn1 = [vec=std::move(vec)]{
    std::cout << "Inside fn1: vec.size() == " << vec.size() << "\n";
  };
  fn1();
  std::cout << "Outside fn1: vec.size() == " << vec.size() << "\n";

  std::cout << "\nEmulate C++14 init capture with std::bind\n";
  std::vector<int> vec2 = {0,1,2,4,5};
  auto fn2 = std::bind([](std::vector<int>& vec){
    std::cout << "Inside fn2: vec.size() == " << vec.size() << "\n";
  }, std::move(vec2));
  fn2();

  std::cout << "\nSimple test of std::bind calling a class instance member function:\n";
  Test pt;
  auto fn3 = std::bind(&Test::foo, &pt);
  fn3();


}
