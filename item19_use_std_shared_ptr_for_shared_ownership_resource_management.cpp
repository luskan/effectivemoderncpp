//
// Created by marci_000 on 07.02.2017.
//

#include <iostream>
#include <memory>
#include <vector>

#include "item19_use_std_shared_ptr_for_shared_ownership_resource_management.h"

class Worker : public std::enable_shared_from_this<Worker> {
  std::string name;
  std::vector<std::shared_ptr<Worker>> updated;
 public:

  template<typename... Ts>
  static std::shared_ptr<Worker> create(Ts&&... args) {
    return std::shared_ptr<Worker>(new Worker(std::forward<Ts>(args)...));
  }

  void update() {
    updated.emplace_back(shared_from_this());
  }

 //private:
  Worker(std::string s) {
    name = s;
  }
};

void item19_use_std_shared_ptr_for_shared_ownership_resource_management::run() {

  // Test showing that the unique_ptr deleter will be moved to shared_ptr, when moving unique_ptr to shared_ptr.
  auto deleter1 = [](int* p) {
    std::cout << "Delter\n";
    delete p;}
  ;
  std::unique_ptr<int, decltype(deleter1)> up1(new int, deleter1);
  std::shared_ptr<int> sp1(std::move(up1));

  // Sample showing that in case of shared_ptr the deleter is not part of the type.
  std::shared_ptr<int> sp2(new int, [](int* p){ std::cout << "sp2 dleter\n"; delete p; });
  std::shared_ptr<int> sp3(new int, [](int* p){ std::cout << "sp3 dleter\n"; delete p; });
  sp2 = std::move(sp3);

  // enable_shared_from_this
  auto sp = Worker::create("test");
  sp->update();

  // Wrong use, shared_ptr must be created for instance using enable_shared_from_this.
  try {
    auto wrk = new Worker("Test");
    wrk->update();
  }
  catch(std::bad_weak_ptr& ex) {
    std::cout << ex.what() << "\n";
  }
}
