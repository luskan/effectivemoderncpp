//
// Created by marcin on 18.04.17.
//

#include "item36_specify_std_launch_async_if_asynchronicity_is_essential.h"
#include <thread>
#include <future>
#include <iostream>
#include <iomanip>

template<typename F, typename... Args>
inline std::future<typename std::result_of<F(Args...)>::type>
reallyAsync(F&& f, Args&&... args) {
 return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
}

void Item36_specify_std_launch_async_if_asynchronicity_is_essential::run() {

  using namespace std::literals;

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

  //the correct way to execute a task with default policy.
  std::cout << "\nTask execute." << "\n";
  auto fut_a1 = std::async([]{ std::cout << "Some task being executed."; std::this_thread::sleep_for(1s); });
  if (fut_a1.wait_for(0s) == std::future_status::deferred) {
    std::cout << "Task is deferred!.\n";
    fut_a1.get();
  }
  else {
    int n = 0;
    while(fut_a1.wait_for(100ms) != std::future_status::ready) {
      std::cout << "#" << n++ << " Task is still being executed.\n";
    }
  }

  // std::async by default executes using default|async launch policy. Below is use of realAsync which by default always
  // executes async tasks.
  auto fut_ra = reallyAsync(
    [](int n, std::string msg){ std::cout << "\nrealAsync: " << msg << " - " << n << "\n"; },
    0,
    "Test"
  );
  fut_ra.get();
}
