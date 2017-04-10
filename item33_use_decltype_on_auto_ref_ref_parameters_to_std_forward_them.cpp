//
// Created by marcin on 10.04.17.
//

#include "item33_use_decltype_on_auto_ref_ref_parameters_to_std_forward_them.h"
#include <iostream>
#include <string>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

void normalize(std::string s, int n = 0) {
  std::cout << __PRETTY_FUNCTION__ << ": " << s << "\n";
}

void item33_use_decltype_on_auto_ref_ref_parameters_to_std_forward_them::run() {

  // generic lambda expression creates a lambda class which is basicly a class with templated
  // operator(). Below we have a forwaring lambda which assumes normalize expects only lvalues,
  // which is not true as std::string might be as well created from rvalue - and even more
  // efficient.
  std::cout << "1.\n";
  auto fn = [](auto s) {
      std::cout << type_id_with_cvr<decltype(s)>().pretty_name() << "\n";
      normalize(s);
  };
  fn(std::string("test"));

  // Now lets modify it so it will perfectly forward
  std::cout << "\n2.\n";
  auto fn2 = [](auto&& fs) {
      std::cout << type_id_with_cvr<decltype(fs)>().pretty_name() << "\n";
      normalize(std::forward<decltype(fs)>(fs));
  };

  // Below will output fs parameter as rvalue reference
  fn2(std::string("test2"));
  // Here fs parameter is an array reference
  fn2("test3");
  // Here fs parameter is an lvalue reference
  std::string lvalue_str("test4");
  fn2(lvalue_str);

  // Now the final tweak is to allow to use variadics (add six dots).
  std::cout << "\n3.\n";
  auto fn3 = [](auto&&... fs) {

      // Lets print all type names inside this pack:
      // Based on: http://stackoverflow.com/questions/25680461/variadic-template-pack-expansion/25683817#25683817
      //int dummy[] = {0, ((void)(std::cout << "Param #"<< dummy[0]++ << ":" << type_id_with_cvr<decltype(fs)>().pretty_name() << "\n"), 0)...};

      // Or with c++17 fold expressions:
      int param_id = 0;
      ((std::cout << "Param #"<< param_id++ << ":" << type_id_with_cvr<decltype(fs)>().pretty_name() << "\n"), ...);

      //std::cout << type_id_with_cvr<decltype(fs)...>().pretty_name() << "\n";
      normalize(std::forward<decltype(fs)>(fs)...);
  };
  fn3(std::string("test5"), 5);
}
