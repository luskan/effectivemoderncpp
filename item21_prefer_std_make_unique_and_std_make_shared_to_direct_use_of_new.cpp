//
// Created by marci_000 on 08.02.2017.
//

#include <memory>
#include <iostream>
#include <vector>

#include "item21_prefer_std_make_unique_and_std_make_shared_to_direct_use_of_new.h"

namespace stdex {
  template<typename T, typename... Ts>
  std::unique_ptr<T> make_unique(Ts&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
  }
}

struct TestCtrParen {
  TestCtrParen(std::initializer_list<int> init_list) {
    std::cout << "init list\n";
  }

  TestCtrParen(int d1) {
    std::cout << "TestCtrParen(int d1)\n";
  }
};

struct SomeLargeObj {
  SomeLargeObj() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
  ~SomeLargeObj() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
};

template <typename T>
struct buffer_allocator {
  using value_type = T;

  buffer_allocator() = default;

  template <class U>
  buffer_allocator(const buffer_allocator<U>&) {}

  T* allocate(size_t n) {
    void *p = operator new(n * sizeof(T));

    printf("Allocate   %p, (%zu)\n", p, get_size());

    return (T*) p;
  }

  void deallocate(T* p, size_t n) {
    delete p;

    printf("Deallocate %p, (%zu)\n", p, get_size());
  }

  size_t get_size(){
    return size;
  }

  void set_size(size_t size){
    this->size = size;
  }

 private:
  size_t size = 0;
};

void item21_prefer_std_make_unique_and_std_make_shared_to_direct_use_of_new::run() {

  // custom make_unique
  auto ptr = stdex::make_unique<std::string>("Whatever");
  //auto ptr = std::make_unique<std::string>("Whatever");
  std::cout << *ptr;
  std::cout << "\n";

  TestCtrParen tcp1(1); // uses int ctor version
  TestCtrParen tcp2{2}; // uses std::initializer_list ctor version

  // make_shared does not allow to call initializer list ctor version, as std::forward does not forwards init list arguments.
  //std::make_shared<TestCtrParen>({1,2,3,4});
  //auto spv = std::make_shared<std::vector<int>>({1,2,3,4});

  // to overcome this problem you may use:
  auto initList = {1,2,3,4};
  auto spv0 = std::make_shared<TestCtrParen>(initList);
  auto spv1 = std::make_shared<std::vector<int>>(initList);

  //
  {
    std::cout << "\nTest code to find out how weak_ptr causes memory reclamation to be postponed\n";
    auto sp = std::allocate_shared<SomeLargeObj>(buffer_allocator<SomeLargeObj>());
    // here memory is allocated by allocator (control block + memory for SomeLargeObj), then ctor is called
    std::weak_ptr<SomeLargeObj> wp1(sp);
    std::cout << " - before sp release\n";
    sp.reset();
    // here ~SomeLargeObj called
    std::cout << " - after sp release\n";
    std::cout << " - before wp release\n";
    wp1.reset();
    // here memory is freed by allocator
    std::cout << " - after wp release\n";
  }
}
