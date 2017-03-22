//
// Created by marci_000 on 01.03.2017.
//

#include <type_traits>
#include <iostream>
#include <thread>
#include <functional>
#include <boost/type_index.hpp>

#include "item27_familiarize_yourself_with_alternatives_to_overriding_on_universal_references.h"

using boost::typeindex::type_id_with_cvr;

void check_bool(std::true_type) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
}
void check_bool(std::false_type) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

template<typename T>
void log_with_decor_impl(T&& t, std::false_type) {
  std::cout << "Non integral: " << t << "\n";
}

template<typename T>
void log_with_decor_impl(T&& t, std::true_type) {
  std::cout << "Integral: " << t << "\n";
}
//void log_with_decor_impl(int t, std::true_type) {
//  std::cout << "Integral: " << t << "\n";
//}

template<typename T>
void log_with_decor(T&& t) {
  log_with_decor_impl(t, std::is_integral<typename std::remove_reference<T>::type>());
}

// http://stackoverflow.com/a/24018996/471160
template<typename T, typename U, typename... Us>
struct is_any_of
  : std::integral_constant<
    bool,
    std::conditional<
      std::is_same<T,U>::value,
      std::true_type,
      is_any_of<T,Us...>
    >::type::value
  >
{ };

template<typename T, typename U>
struct is_any_of<T,U> : std::is_same<T,U>::type { };

/*

  Below class is wrong, callMe in both versions has the same signatures.
  Default template arguments are not part of the signature of a template (so both definitions try to define the same template twice).
  Their parameter types are part of the signature, however.

class TestCall {
 public:

  template<typename T, typename = std::enable_if_t<is_any_of<T, std::string>{}>>
  void callMe(T val) {
    std::cout << "CallMe for int and std::string : " << type_id_with_cvr<decltype(val)>().pretty_name() << ", " << val << "\n";
  }

  template<typename T, typename = std::enable_if_t<is_any_of<T, float, double>{}>>
  void callMe(T val) {
    std::cout << "CallMe for float and double : " << type_id_with_cvr<decltype(val)>().pretty_name() << ", " << val << "\n";
  }
};
*/

class TestCall {
 public:

  template<typename T, typename std::enable_if<is_any_of<T, std::string, int>::value, int>::type = 0>
  void callMe(T val) {
    std::cout << "CallMe for int and std::string : " << type_id_with_cvr<decltype(val)>().pretty_name() << ", " << val << "\n";
  }

  template<typename T, typename std::enable_if<is_any_of<T, float>::value, int>::type = 0>
  void callMe(T val) {
    std::cout << "CallMe for float and double : " << type_id_with_cvr<decltype(val)>().pretty_name() << ", " << val << "\n";
  }
};

// This is a more visual example of above SFINAE behaviour
struct TestCallType1 {
  typedef int type_1;
};
struct TestCallType2 {
  typedef int type_2;
};
class TestCall2 {
 public:

  template<typename T, typename T::type_1 = 0>
    void callMe(T val) {
    std::cout << "CallMe for T with typedef of name type_1\n";
  }

  template<typename T, typename T::type_2 = 0>
  void callMe(T val) {
    std::cout << "CallMe for T with typedef of name type_2\n";
  }
};

template<typename T>
void foo12(T t,
           std::enable_if_t<std::is_integral<std::decay_t<T>>::value, int> = 0
           //typename std::enable_if<std::is_integral<T>::value, int>::type = 0
)
{
  std::cout << type_id_with_cvr<T>().pretty_name() << "\n";
}

void item27_familiarize_yourself_with_alternatives_to_overriding_on_universal_references::run() {

  foo12(1);
  //foo12(0.2);

  // Tag dispatch
  check_bool(std::is_integral<int>());
  check_bool(std::is_integral<double>());

  std::cout << "\n";
  log_with_decor("Test str");
  log_with_decor(1);

  //
  std::cout << "\nHere test SFINAE with enable_if:\n";
  TestCall tc;
  tc.callMe(123);
  tc.callMe(std::string("asd"));
  tc.callMe(123.1f);
  //tc.callMe("fd");

  //
  std::cout << "\nHere test SFINAE with simple struct, to present how failure in overloading is not an error:\n";
  TestCall2 tc2;
  TestCallType1 tct1;
  TestCallType2 tct2;
  tc2.callMe(tct1);
  tc2.callMe(tct2);
}
