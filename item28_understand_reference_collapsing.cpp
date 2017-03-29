//
// Created by marci_000 on 22.03.2017.
//

#include "item28_understand_reference_collapsing.h"
#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

template<typename T>
void foo(T&& rhs){
  std::cout << "T = " << type_id_with_cvr<T>().pretty_name() << ", and decltype(rhs) = " << type_id_with_cvr<decltype(rhs)>().pretty_name() << "\n";
}

void item28_understand_reference_collapsing::run() {
  int ss = 1;
  foo(ss);      // ss is a lvalue reference so we have: T = int&, and decltype(rhs) = int&
  foo(int{12}); // we are passing a rvalue to T will no non-reference: T = int, and decltype(rhs) = int&&

  auto&& ri = {1,2}; // yeah, that is allowed and yields std::initializer_list<int>&&
  std::cout << "\n" << type_id_with_cvr<decltype(ri)>().pretty_name() << "\n";
}
