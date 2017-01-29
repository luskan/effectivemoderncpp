#include <iostream>
#include <boost/system/error_code.hpp>
#include <boost/version.hpp>
#include "item8_prefer_nullptr_to_0_and_null.h"
#include "item9_prefer_alias_declarations_to_typedefs.h"
#include "item10_prefer_scoped_enums_to_unscoped_enums.h"
#include "item11_prefer_deleted_functions_to_private_undefined_ones.h"
#include "item1_understand_template_type_deduction.h"
#include "item2_understand_auto_type_deduction.h"
#include "item3_understand_decltype.h"
#include "item4_know_how_to_view_deduced_types.h"
#include "item5_prefer_auto_to_explicit_type_declaration.h"
#include "item6_use_the_explicitly_typed_initializer_idiom_when_auto_deduces_undesired_types.h"
#include "item7_distinguish_between_parenthesis_and_braces_when_creating_objects.h"
#include "item12_declare_overriding_functions_override.h"
#include "item13_prefer_const_iterators_to_iterators.h"
#include "item14_declare_functions_noexcept_if_they_wont_emit_exceptions.h"

int main() {

    std::cout << "gcc version : " << __VERSION__ << "\n";
    std::cout << "boost version : " << (BOOST_VERSION / 100000) << "." << ((BOOST_VERSION / 100) % 1000) << "." << (BOOST_VERSION % 100) << "\n\n";

    //item1_understand_template_type_deduction().run();
    //item2_understand_auto_type_deduction().run();
    //item3_understand_decltype().run();
    //item4_know_how_to_view_deduced_types().run();
    //item5_prefer_auto_to_explicit_type_declaration().run();
    //item6_use_the_explicitly_typed_initializer_idiom_when_auto_deduces_undesired_types().run();
    //item7_distinguish_between_parenthesis_and_braces_when_creating_objects().run();
    //item8_prefer_nullptr_to_0_and_null().run();
    //item9_prefer_alias_declarations_to_typedefs().run();
    //item10_prefer_scoped_enums_to_unscoped_enums().run();
    //item11_prefer_deleted_functions_to_private_undefined_ones().run();
    //item12_declare_overriding_functions_override().run();
    //item13_prefer_const_iterators_to_iterators().run();
    item14_declare_functions_noexcept_if_they_wont_emit_exceptions().run();

    return 0;
}