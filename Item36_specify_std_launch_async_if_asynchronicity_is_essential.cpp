//
// Created by marcin on 18.04.17.
//

#include "Item36_specify_std_launch_async_if_asynchronicity_is_essential.h"
#include <thread>
#include <future>
#include <iostream>
#include <iomanip>

void Item36_specify_std_launch_async_if_asynchronicity_is_essential::run() {

  auto func = [](){ std::cout << std::setw(30) << "From async: thread id is " << std::this_thread::get_id() << "\n"; };

  // Default launch policy is defered + async
  auto f1 = std::async(func);
  auto f2 = std::async(func);
  f1.get();
  f2.get();

  // Now deferred only
  // Printed thread ids will be the same in all three outputs
  std::cout << "\n" << std::setw(30) << "This thread is " << std::this_thread::get_id() << "\n";
  auto f3 = std::async(std::launch::deferred, func);
  auto f4 = std::async(std::launch::deferred, func);
  f3.get();
  f4.get();

  // Now async only
  // Printed thread ids will be different in all three outputs
  std::cout << "\n" << std::setw(30) << "in async launch async will use software threads" << "\n";
  auto f5 = std::async(std::launch::async, func);
  auto f6 = std::async(std::launch::async, func);
  f5.get();
  f6.get();
}
