//
// Created by marci_000 on 11.04.2017.
//

#include "item35_prefer_task_based_programming_to_thread_based.h"

#include <iostream>
#include <thread>
#include <future>
#include <vector>

using namespace std::literals;

void item35_prefer_task_based_programming_to_thread_based::run() {
  auto workFn = [](auto s) { std::cout << "Doing some work: " << s << "\n"; };

  // Thread based aproach.
  std::thread th(workFn, "Thread based aproach");
  th.join();

  // Task based aproach.
  auto fut = std::async(workFn, "Task based aproach");
  fut.get();

  // No way with std::thread to easily catch exception or return value
  /*
  try {
    std::thread th2([] { throw ""; return 0; });
    th2.join();
  } catch (...){}
  */

  // Now, task based aproach provide all this with ease.
  auto fn2= [](bool can_throw){ if (can_throw) throw  ""; return 101; };
  auto fut2 = std::async(fn2, false);
  std::cout << "result from fn2: " << fut2.get() << "\n";
  auto fut3 = std::async(fn2, true);
  try {
    std::cout << "result from fn2 (throws): " << fut3.get() << "\n";
  }
  catch(...) {
    std::cout << "exception from fn2 was caught\n";
  }

  // Now fn2 will be lazy evaluated only after get is called.
  auto fut4 = std::async(std::launch::deferred, fn2, false);
  std::cout << "Wait 2s... " << "\n";
  std::this_thread::sleep_for(2s);
  std::cout << "result from fn2: " << fut4.get() << "\n";

  // Now lets try to generate "out of thrads" error
  // WARNING: under windows 10 it drains resources to the point when system is beeing rebooted!
  /*
  std::cout << "\nGeneration of out of threads exception\n";
  std::vector<std::thread> th_vec;
  std::atomic<bool> wait(true);
  for(std::size_t i= 0; ; ++i) {
    th_vec.emplace_back([&](){ while(wait){ std::this_thread::sleep_for(100ms); }});
    if ((th_vec.size()%100) == 0) {
      std::cout << "#" << (th_vec.size() / 100) << " th_vec.size() = " << th_vec.size() << "\n";
    }
  }
  */

  // Now the same as above but with task based aproach (std::async)
  // WARNING: now as bad as with above std::threads system resets, but still strange, std::future_status::deferred is not
  // returned, system heavily freezes.
  std::cout << "\nGeneration of out of threads exception\n";
  std::vector<std::future<void>> fut_vec;
  std::vector<std::future<void>> fut_vec_defered;
  std::atomic<bool> wait(true);
  for(std::size_t i= 0; ; ++i) {
    auto fut = std::async([&](){ while(wait){ std::this_thread::sleep_for(100ms); }});

    if (fut.wait_for(0s) == std::future_status::deferred)
      fut_vec_defered.emplace_back(std::move(fut));
    else
      fut_vec.emplace_back(std::move(fut));

    if ((i % 100) == 0) {
      std::cout << "#" << (i / 100) << " fut_vec.size() = " << fut_vec.size() << ", fut_vec_defered.size() = " << fut_vec_defered.size() << "\n";
    }
  }
}
