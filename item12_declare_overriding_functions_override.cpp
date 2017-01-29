//
// Created by marci_000 on 19.01.2017.
//

#include "item12_declare_overriding_functions_override.h"
#include <iostream>
#include <memory>
#include <vector>
#include <boost/type_index.hpp>
using boost::typeindex::type_id_with_cvr;

class Base {
 public:
  virtual void doWork() { std::cout << "Base::doWork\n"; }
};

class Derived : public Base {
 public:
  void doWork() override { std::cout << "Derived::doWork\n"; }
};

class DataPack {
 public:
  std::vector<int> data;

  DataPack(std::initializer_list<int> d) : data{d} {}

  std::vector<int>& get_data() & {
    return data;
  }
  //std::vector<int>&& get_data() && {
  //  return std::move(data);
  //}
  // This version fixes all problems
  std::vector<int> get_data() && {
    return data;
  }
};

void item12_declare_overriding_functions_override::run() {

  //
  std::unique_ptr<Base> p = std::make_unique<Derived>();
  p->doWork();

  //
  DataPack dp{1,2,3,4,5};

  // Use get_data lvalue reference version
  for (auto v : dp.get_data()) {
    std::cout << v << ", ";
  }

  auto my_data = DataPack{1,2,3}.get_data();
  std::cout << "\n" << type_id_with_cvr<decltype(my_data)>().pretty_name();
  // Outputs std::vector<int, std::allocator<int> >

  std::cout << "\n";
  // Use get_data rvalue reference version
  for (auto v : DataPack{1,2,3}.get_data()) {
    std::cout << v << ", ";
  }

}
