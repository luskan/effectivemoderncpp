//
// Created by marcin on 15.01.17.
//

#include "item4_know_how_to_view_deduced_types.h"
#include <boost/type_index.hpp>
#include <iostream>
#include <cxxabi.h>
using boost::typeindex::type_id_with_cvr;

void item4_know_how_to_view_deduced_types::run() {
    int nn=10;
    const int& arr = nn;

    // typeid strips cv qualification together with referencness.
    std::cout << "boost : " << type_id_with_cvr<decltype(arr)>().pretty_name() << "\n";
    std::cout << "typeid : " << __cxxabiv1::__cxa_demangle(typeid(decltype(arr)).name(),0,0,0);


}
