//
// Created by marcin on 30.04.17.
//

#include "item42_consider_emplacement_instead_of_insertion.h"

#include <vector>
#include <string>
#include <regex>
#include <memory>
#include <iostream>
#include <list>
#include <deque>

struct PrintMe {
    PrintMe(){ if (allowPrint) std::cout << __PRETTY_FUNCTION__ << "\n"; }
    PrintMe(std::string){ if (allowPrint) std::cout << __PRETTY_FUNCTION__ << "\n"; }
    ~PrintMe(){ if (allowPrint) std::cout << __PRETTY_FUNCTION__ << "\n"; }
    PrintMe(const PrintMe&){ if (allowPrint) std::cout << __PRETTY_FUNCTION__ << "\n"; }
    PrintMe(PrintMe&&) noexcept { if (allowPrint) std::cout << __PRETTY_FUNCTION__ << "\n"; }
    PrintMe& operator=(const PrintMe&){ if (allowPrint) std::cout << __PRETTY_FUNCTION__ << "\n"; return *this;}
    PrintMe& operator=(PrintMe&&) noexcept { if (allowPrint) std::cout << __PRETTY_FUNCTION__ << "\n"; return *this;}

    static bool allowPrint;
};

bool PrintMe::allowPrint = false;

void item42_consider_emplacement_instead_of_insertion::run() {
  std::vector<std::string> av;
  av.push_back("test");

  // Benefit from emplacement arises from the lack of temporary object needed to add new element
  // to container. So it makes sense when type of element added using emplacement differs from the type
  // of container element type.

  // Below code gives no benefits.
  av.emplace_back(std::string("dfd"));
  std::string str("dfd");
  av.emplace_back(str);

  // If emplace is implemented in a form of assignment, then there is no benefit from using emplacement
  // as assignment (even if move assignment) requires temporary from which a move is performed.

  // Below code presents that vector does not suffer from this, list either, no temporaries were created
  // in below code.

  {
    std::cout << "\n Vector test for emplace construction efficiency\n";
    std::vector<PrintMe> vec1;
    vec1.resize(2);
    PrintMe::allowPrint = true;
    vec1.emplace(vec1.begin(), "test");
    PrintMe::allowPrint = false;
  }

  // Now lets test this for list

  {
    std::cout << "\n List test for emplace construction efficiency\n";
    std::list<PrintMe> lst1;
    lst1.resize(2);
    PrintMe::allowPrint = true;
    lst1.emplace(lst1.begin(), "test");
    PrintMe::allowPrint = false;
  }

  //
  //

  auto deleter = [](std::string* p) {
      delete p;
  };
  using str_ptr = std::unique_ptr<std::string, decltype(deleter)>;
  std::vector<str_ptr> vec;

  // This is unsafe, if internally emplace_back will fail to allocate memory to increate capacity,
  // then below pointer will be leaked.
  vec.emplace_back(new std::string("test"), deleter);

  // This is safe, as temporary here saves us from possible memory leaks
  //vec.push_back(str_ptr{new std::string("some test"), deleter});
  vec.push_back(str_ptr{new std::string("some test"), deleter});
  vec.push_back({new std::string("some test"), deleter});

  using str_sp_ptr = std::shared_ptr<std::string>;
  std::vector<str_sp_ptr> vec2;
  vec2.push_back({new std::string("test"), deleter});

  //
  //

  std::vector<std::regex> regs;
  //regs.push_back(nullptr);  // does not compile as it requires copy initialization which does not
                              // allow to use explicit initialization

  //regs.emplace_back(nullptr); // does compile because emplacement uses direct initialization which
  //                            // allows to use explicit constructors
                                // But its UB, and causes segfault
}
