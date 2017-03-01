//
// Created by marci_000 on 08.02.2017.
//

#include "item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file.h"

struct item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file::Impl {

};

void item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file::run() {

}

item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file::item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file()
  : pImpl(std::make_unique<Impl>())
{
}

/**
 * requirec dtor here, unique_ptr has assertion on that:
 * static_assert(sizeof(_Tp)>0,
		      "can't delete pointer to incomplete type");
 * */
item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file::~item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file() = default;