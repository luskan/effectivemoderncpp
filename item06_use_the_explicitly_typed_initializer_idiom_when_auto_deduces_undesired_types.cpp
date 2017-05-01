//
// Created by marcin on 16.01.17.
//

#include <bitset>
#include <iostream>
#include "item06_use_the_explicitly_typed_initializer_idiom_when_auto_deduces_undesired_types.h"
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

std::bitset<10> getBits() {
    return std::bitset<10>(123);
}

void item6_use_the_explicitly_typed_initializer_idiom_when_auto_deduces_undesired_types::run() {

    auto bs = getBits()[1];

    // std::bitsets operator[] returns not a reference to bool, or bool but a proxy class instance:
    std::cout << type_id_with_cvr<decltype(bs)>().pretty_name() << "\n";

    // Outputs: std::bitset<10ul>::reference

    // This makes above code UB, as bs is a proxy class which refers to a temporary bitset which was destroyed at the
    // end of `auto bs = getBits()[1];` statement.

    // To fix it use Explicitly Typed Initializer idiom:
    auto bs2 = static_cast<bool>(getBits()[1]);
    std::cout << type_id_with_cvr<decltype(bs2)>().pretty_name() << "\n";

    // Output: bool

    // Proxy classes are common in apis that use expression templates. For example:
    //Matrix sum = m1 + m2 + m3 + m4;
    // as an optimization aid, m1+m2 does not yet produce a Matrix, only upon assignment to `Matrix sum` the real
    // computation takes place. So the intermediate results are acutally a proxies. And use of auto here
    // can cause similar problems as with bitset<>.
}
