//
// Created by marci_000 on 21.04.2017.
//

#include <iostream>
#include <thread>
#include <future>
#include <chrono>

#include "item38_be_aware_of_varying_thread_handle_destructor_behavior.h"

void item38_be_aware_of_varying_thread_handle_destructor_behavior::run() {
  using namespace std::literals;

  {
    auto fut1 = std::async(std::launch::async,
                           [] { std::this_thread::sleep_for(1s);
                                std::cout << "work done 1!\n"; });
    // here fut1 in its destructor will force a join on a thread associated with above task.
  }
  std::cout << "Work done - implicit join on fut1 associated thread just ended\n\n";

  {
    std::async(std::launch::async,
               [] { std::this_thread::sleep_for(1s);
                    std::cout << "work done 2!\n"; });
    // This line will be executed only after above task finishes, this is because:
    //   "If the std::future obtained from std::async has temporary object lifetime
    //    (not moved or bound to a variable), the destructor of the std::future will
    //    block at the end of the full expression until the asynchronous operation
    //    completes, essentially code such as the following synchronous:"
  }
  std::cout << "We are back on caller thread...\n";

  //
  //

  std::cout << "\nPackaged task example\n";
  {
    auto fn = [] { std::cout << "work start - packaged_task exampl!\n";
                   std::this_thread::sleep_for(1s);
                   std::cout << "work done - packaged_task exampl!\n";
                   return 101; };
    std::packaged_task<int()> pt(fn);
    auto fut = pt.get_future();

    std::thread th(std::move(pt));
    // now we need to either join or detach.

    th.detach();
    std::cout << "Thread was detached, now lets get future result.\n";

    // It does not matter if fut.get() is not called, thread was already detached
    // so fut will simply get destroyed.
    //auto res = fut.get(); // here get will make current thread to wait for result.
    //std::cout << "The result is " << res << "\n";
  }
  std::cout << "Packaged task block ended\n";
}
