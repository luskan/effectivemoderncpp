//
// Created by marci_000 on 18.04.2017.
//

#include "item37_make_std_threads_unjoinable_on_all_paths.h"
#include "thread_raii.h"

#include <thread>
#include <iostream>
#include <string>

void item37_make_std_threads_unjoinable_on_all_paths::run() {
  using namespace std::literals;

  /*
  {
    std::thread th([] { std::this_thread::sleep_for(2s); });
    // its still joinable when leaving scope, so this will result in exception
  }
  */

  {
    std::thread th([] { std::this_thread::sleep_for(2s); });
    // thats fine, by calling join we make std::thread object unjoinable.
    th.join();
    //th.join(); // unjoinable, so causes: std::system_error - Invalid argument
  }

  {
    std::thread th([] { std::this_thread::sleep_for(2s); });
    // we may also detach (but watch out for any by ref captured local objects)
    th.detach();
    //th.detach(); // unjoinable, so causes: std::system_error - Invalid argument
  }

  {
    ThreadRAII th(
      std::thread([] { std::this_thread::sleep_for(2s); }),
      ThreadRAII::DtorAction::join
    );
  }

}
