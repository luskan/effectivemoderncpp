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
#include "item15_use_constexpr_whenever_possible.h"
#include "item16_make_const_member_functions_thread_safe.h"
#include "item17_understand_special_member_function_generation.h"
#include "item18_use_std_unique_ptr_for_exclusive_ownership_resource_management.h"
#include "item19_use_std_shared_ptr_for_shared_ownership_resource_management.h"
#include "item20_use_std_weak_ptr_for_std_shared_ptr_like_pointers_that_can_dangle.h"
#include "item21_prefer_std_make_unique_and_std_make_shared_to_direct_use_of_new.h"
#include "item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file.h"
#include "item23_understand_std_move_and_std_forward.h"
#include "item24_distinguish_universal_references_from_rvalue_references.h"
#include "item25_use_std_move_on_rvalue_references_std_forward_on_universal_references.h"
#include "item26_avoid_overloading_on_universal_references.h"
#include "item27_familiarize_yourself_with_alternatives_to_overriding_on_universal_references.h"
#include "item28_understand_reference_collapsing.h"
#include "item29_assume_that_move_operations_are_not_present_not_cheap_and_not_used.h"
#include "item30_familiarize_yourself_with_perfect_forwarding_failure_cases.h"
#include "item31_avoid_default_capture_modes.h"
#include "item32_use_init_capture_to_move_objects_into_closures.h"
#include "item33_use_decltype_on_auto_ref_ref_parameters_to_std_forward_them.h"
#include "item34_prefer_lambdas_to_std_bind.h"
#include "item35_prefer_task_based_programming_to_thread_based.h"
#include "Item36_specify_std_launch_async_if_asynchronicity_is_essential.h"
#include "item37_make_std_threads_unjoinable_on_all_paths.h"
#include "item38_be_aware_of_varying_thread_handle_destructor_behavior.h"
#include "item39_consider_void_futures_for_one_shot_event_communication.h"
#include "item40_use_std_atomic_for_concurrency_volatile_for_special_memory.h"
#include "item41_consider_pass_by_value_for_copyable_parameters_that_are_cheap_to_move_and_always_copied.h"

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
    //item14_declare_functions_noexcept_if_they_wont_emit_exceptions().run();
    //item15_use_constexpr_whenever_possible().run();
    //item16_make_const_member_functions_thread_safe().run();
    //item17_understand_special_member_function_generation().run();
    //item18_use_std_unique_ptr_for_exclusive_ownership_resource_management().run();
    //item19_use_std_shared_ptr_for_shared_ownership_resource_management().run();
    //item20_use_std_weak_ptr_for_std_shared_ptr_like_pointers_that_can_dangle().run();
    //item21_prefer_std_make_unique_and_std_make_shared_to_direct_use_of_new().run();
    //item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file().run();
    //item23_understand_std_move_and_std_forward().run();
    //item24_distinguish_universal_references_from_rvalue_references().run();
    //item25_use_std_move_on_rvalue_references_std_forward_on_universal_references().run();
    //item26_avoid_overloading_on_universal_references().run();
    //item27_familiarize_yourself_with_alternatives_to_overriding_on_universal_references().run();
    //item28_understand_reference_collapsing().run();
    //item29_assume_that_move_operations_are_not_present_not_cheap_and_not_used().run();
    //item30_familiarize_yourself_with_perfect_forwarding_failure_cases().run();
    //item31_avoid_default_capture_modes().run();
    //item32_use_init_capture_to_move_objects_into_closures().run();
    //item33_use_decltype_on_auto_ref_ref_parameters_to_std_forward_them().run();
    //item34_prefer_lambdas_to_std_bind().run();
    //item35_prefer_task_based_programming_to_thread_based().run();
    //Item36_specify_std_launch_async_if_asynchronicity_is_essential().run();
    //item37_make_std_threads_unjoinable_on_all_paths().run();
    //item38_be_aware_of_varying_thread_handle_destructor_behavior().run();
    //item39_consider_void_futures_for_one_shot_event_communication().run();
    //item40_use_std_atomic_for_concurrency_volatile_for_special_memory().run();
    item41_consider_pass_by_value_for_copyable_parameters_that_are_cheap_to_move_and_always_copied().run();

    return 0;
}