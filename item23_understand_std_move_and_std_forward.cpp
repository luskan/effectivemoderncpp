//
// Created by marci_000 on 11.02.2017.
//
#include <utility>
#include <string>
#include <iostream>
#include <boost/type_index.hpp>
#include <iomanip>

using boost::typeindex::type_id_with_cvr;

#include "item23_understand_std_move_and_std_forward.h"


template<typename T>
void test(T&& rhs) {
  std::cout << type_id_with_cvr<T>().pretty_name() << "\n";
  std::cout << type_id_with_cvr<decltype(rhs)>().pretty_name() << "\n";
  std::cout << type_id_with_cvr<decltype(std::move(rhs))>().pretty_name() << "\n";
  std::cout << type_id_with_cvr<decltype(std::forward<T>(rhs))>().pretty_name() << "\n";
  //std::forward(rhs);
}

namespace stdex {
  template<typename T>
  typename std::remove_reference<T>::type&& move(T&& rhs) {
    using ResultType = typename std::remove_reference<T>::type&&;

    std::cout << std::setw(15) << "T: " << type_id_with_cvr<T>().pretty_name() << "\n";
    std::cout << std::setw(15) << "rhs: " << type_id_with_cvr<decltype(rhs)>().pretty_name() << "\n";
    std::cout << std::setw(15) << "ResultType: " << type_id_with_cvr<ResultType>().pretty_name() << "\n";
    std::cout << std::setw(15) << "casted: " << type_id_with_cvr<decltype(static_cast<ResultType>(rhs))>().pretty_name() << "\n";

    return static_cast<ResultType>(rhs);
  }
}

void process(std::string&& rhs) {
  std::cout << " - " << __PRETTY_FUNCTION__ << "\n";
}
void process(const std::string& rhs) {
  std::cout << " - " << __PRETTY_FUNCTION__ << "\n";
}
template<typename T>
void doProcess(T&& rhs) {
  process(std::forward<T>(rhs));
}

void item23_understand_std_move_and_std_forward::run() {
  std::string str = "";
  auto res = std::forward<std::string>(str);

  std::cout << "shows lvalue references, beside std::move result which always results in rvalue\n\n";
  test(str);

  std::cout << "rvalue\n\n";
  test(std::string(""));

  std::cout << "\n\nexperiments with std::move\n";
  stdex::move(str);

  std::cout << "\n\nNow lets see some forwarding in action\n";
  std::cout << "this should call lvalue reference process version:\n";
  doProcess(str);
  std::cout << "this should call rvalue reference process version:\n";
  doProcess(std::move(str));
  std::cout << "this should call rvalue reference process version:\n";
  doProcess("");
}
