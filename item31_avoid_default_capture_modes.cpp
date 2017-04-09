//
// Created by marci_000 on 31.03.2017.
//

#include "item31_avoid_default_capture_modes.h"

#include <vector>
#include <cstdint>
#include <functional>

std::vector<std::function<bool(int)>> filters;
struct MyData {
  void add_filter() {

    // Does not compile, as this is not captured
    //filters.emplace_back([](){
    //  return somedata == 2;
    //});

    // Those works but because `this` pointer is being captured.
    filters.emplace_back([=](int){
      return somedata == 2;
    });
    filters.emplace_back([&](int){
      return somedata == 2;
    });

    // Those wont compile as somedata is non local and non parameter variable.
    //filters.emplace_back([&somedata](int){
    //  return somedata == 2;
    //});
    //filters.emplace_back([somedata](int){
    //  return somedata == 2;
    //});

    // Best solution is not to capture this, which can end in dangling pointer
    // but a local copy:
    auto somedata_local = somedata;
    filters.emplace_back([=](int){
      return somedata_local == 2;
    });

    // or - since c++14 - a better aproach is generalized lambda capture:
    filters.emplace_back([somedata=somedata](int){
      return somedata == 2;
    });

    // Objects with static storage duration are accessed without captures.
    static int some_static = 1;
    filters.emplace_back([](int){ // no capture needed!
      return some_static == 2;
    });
  }
  int somedata;
};

void item31_avoid_default_capture_modes::run() {


}
