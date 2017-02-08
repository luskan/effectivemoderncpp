//
// Created by marci_000 on 08.02.2017.
//

#include <iostream>
#include <memory>
#include <string>

#include "item20_use_std_weak_ptr_for_std_shared_ptr_like_pointers_that_can_dangle.h"

void item20_use_std_weak_ptr_for_std_shared_ptr_like_pointers_that_can_dangle::run() {

  {
    // basic check for expiration
    std::shared_ptr<std::string> sp1(new std::string("test"));
    std::weak_ptr<std::string> wp1(sp1);

    std::cout << "weak_ptr expired : " << std::boolalpha << wp1.expired() << "\n";

    sp1.reset();
    std::cout << "weak_ptr expired : " << wp1.expired() << "\n";

    std::cout << "\nNow lets test conversion from weak_ptr to shared_ptr:\n";

    // use of weak_ptr, 1
    sp1.reset(new std::string("test2"));

    // still expired, above reset created new control block
    std::cout << " weak_ptr expired : " << wp1.expired() << "\n";

    std::weak_ptr<std::string> wp2(sp1);
    std::cout << " weak_ptr 2 expired : " << wp2.expired() << "\n";

    // Now create from weak_ptr two shared_ptrs
    auto sp2 = wp2.lock();
    if (sp2) {
      std::cout << " We have a pointer to sp1 : " << *sp2 << "\n";
    }

    std::shared_ptr<std::string> sp3(wp2);
    if (sp3) {
      std::cout << " We have a pointer to sp1 (method2) : " << *sp3 << "\n";
    }

    sp2.reset();
    sp3.reset();

    // Free alocated resource
    std::cout << " " << sp1.use_count() << "\n";
    sp1.reset();
    std::cout << " " << sp1.use_count() << "\n";

    // Check if weak ptr is expired.
    std::cout << " wp2.expired() : " << wp2.expired() << "\n";
    try {
      std::shared_ptr<std::string> sp4(wp2);
      if (sp4) {
        std::cout << " hmm, should be expired!\n";
      }
    }
    catch (std::bad_weak_ptr) {
      std::cout << " bad_weak_ptr - OK!\n";
    }
  }

  {
    std::cout << "\n\n";
    std::shared_ptr<std::string> sp1(new std::string("tt"));
    std::shared_ptr<std::string> sp2(sp1);
    std::shared_ptr<std::string> sp3(sp1);
    sp1.reset();
    std::cout << sp1.use_count() << "\n";
    std::cout << sp2.use_count() << "\n";
    std::cout << sp3.use_count() << "\n";
  }
}
