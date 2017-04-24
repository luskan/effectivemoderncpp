//
// Created by marci_000 on 22.04.2017.
//

#include "item39_consider_void_futures_for_one_shot_event_communication.h"

#include "thread_raii.h"

#include <future>
#include <iostream>
#include <vector>

void item39_consider_void_futures_for_one_shot_event_communication::run() {

  using namespace std::literals;

  try
  {
    std::cout << "Use condvar to implement intrathread communication!\n";

    std::mutex m;
    std::condition_variable cv;
    bool flag = false;

    ThreadRAII th1(
      std::thread([&] {

      /*
      // Problem1 : demonstrates race condition problem, and lack of fix for spurious wakups
      std::this_thread::sleep_for(2s);
      std::unique_lock<std::mutex> ul(m);
      cv.wait(ul);
      */

      // Correct code
      std::unique_lock<std::mutex> ul(m);
      cv.wait(ul, [&] { return flag; }); // in wait you may see that it immediately check
                                         // predicate before going to wait.

      std::cout << "Thread got executed!\n";
    }),
    ThreadRAII::DtorAction::join);

    //...
    //
    // 1. th1 could not become runnable untill this place. If it didnt got into a wait
    //    then it will wait forever. To reproduce this uncomment in th1 code in
    //    problem1 comment
    // 2. Unfortunately if exception here is thrown, then ThreadRAII will execute
    //    join in its dtor on th1 causing deadlock. (promise+future solution suffers from this too).
    //    for solution see here: http://scottmeyers.blogspot.com/2015/04/more-on-threadraii-and-thread-suspension.html
    /*
    std::cout << "Before exception throwing!\n";
    throw "Problem2";
    std::cout << "After exception throwing - or nothing but deadloc!\n";
     */

    std::cout << "Thread will execute\n";
    {
      std::unique_lock<std::mutex> ul(m);
      flag = true;
    }
    cv.notify_one();
    std::cout << "After notifying thread\n";
  }
  catch(...){
    std::cout << "Exception was thrown!\n";
  }

  //
  // Promise + future solution
  {
    std::cout << "\n\nUse std::promise+std::future to implement intrathread communication!\n";

    std::promise<void> promise;
    std::future<void> fut = promise.get_future();

    ThreadRAII th(
      std::thread([&] {
      fut.get();
      std::cout << "Thread got executed!\n";
    }),
    ThreadRAII::DtorAction::join
    );

    std::cout << "Before setting promise\n";

    promise.set_value();

    std::cout << "After setting promise\n" << std::endl;
  }

  //
  // Promise + future solution and many threads
  {
    std::cout << "\n\nUse std::promise+std::future with many threads\n";

    std::promise<void> promise;
    auto sf = promise.get_future().share();

    std::vector<ThreadRAII> ths;
    for (int n = 0; n < 10; ++n) {
      auto fn = [sf, n] {
        sf.get();
        std::this_thread::sleep_for(n*100ms);
        std::cout << "Thread got executed : " << n << std::endl;
      };
      ths.emplace_back(ThreadRAII(std::thread(fn), ThreadRAII::DtorAction::join));
    }

    // If any exception happens before .set_value() call, then threads will deadlock.
    try {
      std::cout << "Before setting promise (2s delay)\n";
      std::this_thread::sleep_for(2s);
    }
    catch(...){}
    promise.set_value();

    std::cout << "After setting promise\n" << std::endl;
  }
}
