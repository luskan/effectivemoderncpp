//
// Created by marcin on 10.01.17.
//

#include <sys/types.h>
#include <cstdint>
#include "item10_prefer_scoped_enums_to_unscoped_enums.h"


void item10_prefer_scoped_enums_to_unscoped_enums::run() {

    //enum TestUnscoped; // error, cannot declare unscoped enums, underlying type is unknown

    // Ok
    enum TestUnscoped { White, Green };
    int nn = White;

    // Unscoped with underlying type
    enum TestUnscoped2 : int32_t; // that declaration is fine, underlying type is known
    enum TestUnscoped2 : int32_t  { White1, Green1 };
    int nn2 = White1;

    // Scoped! use of White, Green as in TestUnscoped
    enum class TestScoped; // that declaration is fine, by default underlying type is int
    enum class TestScoped { White, Green };
    TestScoped ts = TestScoped::White;
    //int nn3 = ts; // error, implict cast wont work
    //int nn3 = TestScoped::White; // error, same as above
    int nn3 = static_cast<int>(ts);

    enum class TestScoped2 : int32_t; // type is known so declaration is allowed.
    enum class TestScoped2 : int32_t { White, Green };
    TestScoped2 ts2 = TestScoped2::White;
    //int nn3 = ts; // error, implict cast wont work
    //int nn3 = TestScoped::White; // error, same as above
    int nn32 = static_cast<int>(ts2);
}
