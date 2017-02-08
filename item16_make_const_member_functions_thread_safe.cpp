//
// Created by marci_000 on 01.02.2017.
//
#include <memory>
#include <mutex>
#include <thread>
#include <cassert>
#include <iostream>
#include <atomic>
#include "item16_make_const_member_functions_thread_safe.h"

// Example from book:
class Widget {
 public:

  int expensiveComputation1() const { return 1; }
  int expensiveComputation2() const { return 2; }

  int magicValue() const
  {
    std::lock_guard<std::mutex> guard(m);  // lock m
    if (cacheValid) return cachedValue;
    else {
      auto val1 = expensiveComputation1();
      auto val2 = expensiveComputation2();
      cachedValue = val1 + val2;
      cacheValid = true;
      return cachedValue;
    }
  }                                        // unlock m
 private:
  mutable std::mutex m;
  mutable int cachedValue;                 // no longer atomic
  mutable bool cacheValid{ false };        // no longer atomic
};

class Widget2 {
 public:

  int expensiveComputation1() const { std::this_thread::yield(); return 1; }
  int expensiveComputation2() const { std::this_thread::yield(); return 2; }

  int magicValue() const
  {

    if (cacheValid) return cachedValue;
    else {
      std::lock_guard<std::mutex> guard(m);  // lock m
      if (cacheValid) return cachedValue;
      auto val1 = expensiveComputation1();
      auto val2 = expensiveComputation2();
      cachedValue = val1 + val2;
      cacheValid = true;
      return cachedValue;
    }
  }                                        // unlock m

 private:
  mutable std::atomic<bool>  cacheValid{false};
  mutable std::mutex m;
  mutable int cachedValue;                 // no longer atomic
};

void item16_make_const_member_functions_thread_safe::run() {
  std::array<std::thread, 15> thds;

  // Verify thread safety of mutex version
  auto start = std::chrono::steady_clock::now();
  for (int tr =0; tr < 10000; tr++) {
    Widget w;
    for (auto i = 0; i < thds.size(); ++i) {
      thds[i] = std::thread([&]() { for (int k = 0; k < 150; ++k) assert(w.magicValue() == 3); });
    }
    for (auto i = 0; i < thds.size(); ++i)
      thds[i].join();
  }
  auto end = std::chrono::steady_clock::now();
  auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

  // Verify thread safety of double checked version
  start = std::chrono::steady_clock::now();
  for (int tr =0; tr < 10000; tr++) {
    Widget2 w;
    for (auto i = 0; i < thds.size(); ++i) {
      thds[i] = std::thread([&]() { for (int k = 0; k < 150; ++k) assert(w.magicValue() == 3); });
    }
    for (auto i = 0; i < thds.size(); ++i)
      thds[i].join();
  }
  end = std::chrono::steady_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

  // under windows both durations are almost the same (with -O3 gives 5.4s and 5.1s)
  std::cout << "Duration1: " << duration1.count() << "\n";
  std::cout << "Duration2: " << duration2.count() << "\n";
}
