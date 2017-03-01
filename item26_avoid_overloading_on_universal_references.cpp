//
// Created by marci_000 on 28.02.2017.
//

#include <utility>
#include <string>
#include <sstream>
#include <iostream>
#include "item26_avoid_overloading_on_universal_references.h"

class Person {
 public:
  template<typename T>
    Person(T&& t) : s(std::forward<T>(t)) {
      std::cout << __PRETTY_FUNCTION__ << "\n";
    }

  Person(int n) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }

  // No need to declare copy/move constructors as compiler will do this implicitly
  // Templated constructor does not inhibit it.
  //Person(const Person&) = default;
  //Person(Person&) = delete;
  //Person(Person&&) = default;
  //Person(Person&&) = delete;

 private:
  std::string s;
};

void item26_avoid_overloading_on_universal_references::run() {
  Person p("asd");        // OK!
  Person p2(123);         // OK!

  //std::size_t ts = 123;
  //Person p3(ts);        // does not compile as Person(T&&) here is better match than Person(int)

  //Person p4(p); // Does not compile for the same reason as above

  const Person p5("asd");
  Person p6(p5);        // Ok, but only because p5 is const, then compiler finds that template and normal constructor
                        // has the same singatures which allows compiler to choose normal function as best match.
}
