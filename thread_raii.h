//
// Created by marci_000 on 24.04.2017.
//

#ifndef EFFECTIVEMODERNCPP_THREAD_RAII_H
#define EFFECTIVEMODERNCPP_THREAD_RAII_H

#include <thread>

// From item 37 of effective modern c++ by Scott Meyers
class ThreadRAII {
 public:
  enum class DtorAction { join, detach };

  ThreadRAII(std::thread&& t, DtorAction a) : action(a), t(std::move(t)) {}

  ThreadRAII(ThreadRAII&&) = default;
  ThreadRAII& operator=(ThreadRAII&&) = default;

  ~ThreadRAII() {
    if (t.joinable()) // invoking join/detach on unjoinable std::thread causes Undefined Behaviour (e.g. std::system_error exception);
    {
      if (action == DtorAction::join)
        t.join();
      else if (action == DtorAction::detach)
        t.detach();
    }
  }

  std::thread& get() { return t; }

 private:
  DtorAction action;
  std::thread t;  // intentionally put as last data member, this all the rest of data member will be initialized.
                  //  and std::thread will be able to make use of them if needed.
};


#endif //EFFECTIVEMODERNCPP_THREAD_RAII_H
