//
// Created by marci_000 on 08.02.2017.
//

#ifndef EFFECTIVEMODERNCPP_ITEM22_WHEN_USING_THE_PIMPL_IDIOM_DEFINE_SPECIAL_MEMBER_FUNCTIONS_IN_THE_IMPLEMENTATION_FILE_H
#define EFFECTIVEMODERNCPP_ITEM22_WHEN_USING_THE_PIMPL_IDIOM_DEFINE_SPECIAL_MEMBER_FUNCTIONS_IN_THE_IMPLEMENTATION_FILE_H

#include <memory>

class item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file {
public:
  item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file();
  ~item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file();
  void run();

 private:
  struct Impl;
  std::unique_ptr<Impl> pImpl;
};


#endif //EFFECTIVEMODERNCPP_ITEM22_WHEN_USING_THE_PIMPL_IDIOM_DEFINE_SPECIAL_MEMBER_FUNCTIONS_IN_THE_IMPLEMENTATION_FILE_H
