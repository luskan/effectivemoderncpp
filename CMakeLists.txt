cmake_minimum_required(VERSION 3.6)
project(effectivemoderncpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -pedantic -pthread")
#set(CMAKE_CXX_STANDARD 14)

if(UNIX)
    set(CMAKE_CXX_COMPILER "/home/marcin/gcc-6.3.0/bin/g++")
    set(CMAKE_C_COMPILER "/home/marcin/gcc-6.3.0/bin/gcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
endif()

if(WIN32)
    SET(BOOST_ROOT C:/local/boost_1_63_0)
    SET(BOOST_LIBRARYDIR C:/local/boost_1_63_0/stage/lib)
    #include_directories("C:/Program Files/mingw-w64/x86_64-6.3.0-posix-seh-rt_v5-rev1/mingw64/lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++")
endif()

if(UNIX)
    SET(BOOST_ROOT /home/marcin/libs/boost_1_63_0)
    SET(BOOST_LIBRARYDIR /home/marcin/libs/boost_1_63_0/stage/lib)
endif()

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.63.0 COMPONENTS system REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

if(WIN32)
    find_library(ws2_32_LIBRARY_PATH ws2_32)
endif()
set(SOURCE_FILES main.cpp item08_prefer_nullptr_to_0_and_null.cpp item08_prefer_nullptr_to_0_and_null.h item09_prefer_alias_declarations_to_typedefs.cpp item09_prefer_alias_declarations_to_typedefs.h item10_prefer_scoped_enums_to_unscoped_enums.cpp item10_prefer_scoped_enums_to_unscoped_enums.h item11_prefer_deleted_functions_to_private_undefined_ones.cpp item11_prefer_deleted_functions_to_private_undefined_ones.h item02_understand_auto_type_deduction.cpp item02_understand_auto_type_deduction.h item01_understand_template_type_deduction.cpp item01_understand_template_type_deduction.h item03_understand_decltype.cpp item03_understand_decltype.h item04_know_how_to_view_deduced_types.cpp item04_know_how_to_view_deduced_types.h item05_prefer_auto_to_explicit_type_declaration.cpp item05_prefer_auto_to_explicit_type_declaration.h item06_use_the_explicitly_typed_initializer_idiom_when_auto_deduces_undesired_types.cpp item06_use_the_explicitly_typed_initializer_idiom_when_auto_deduces_undesired_types.h item07_distinguish_between_parenthesis_and_braces_when_creating_objects.cpp item07_distinguish_between_parenthesis_and_braces_when_creating_objects.h item12_declare_overriding_functions_override.cpp item12_declare_overriding_functions_override.h item13_prefer_const_iterators_to_iterators.cpp item13_prefer_const_iterators_to_iterators.h item14_declare_functions_noexcept_if_they_wont_emit_exceptions.cpp item14_declare_functions_noexcept_if_they_wont_emit_exceptions.h item15_use_constexpr_whenever_possible.cpp item15_use_constexpr_whenever_possible.h item16_make_const_member_functions_thread_safe.cpp item16_make_const_member_functions_thread_safe.h item17_understand_special_member_function_generation.cpp item17_understand_special_member_function_generation.h item18_use_std_unique_ptr_for_exclusive_ownership_resource_management.cpp item18_use_std_unique_ptr_for_exclusive_ownership_resource_management.h item19_use_std_shared_ptr_for_shared_ownership_resource_management.cpp item19_use_std_shared_ptr_for_shared_ownership_resource_management.h item20_use_std_weak_ptr_for_std_shared_ptr_like_pointers_that_can_dangle.cpp item20_use_std_weak_ptr_for_std_shared_ptr_like_pointers_that_can_dangle.h item21_prefer_std_make_unique_and_std_make_shared_to_direct_use_of_new.cpp item21_prefer_std_make_unique_and_std_make_shared_to_direct_use_of_new.h item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file.cpp item22_when_using_the_pimpl_idiom_define_special_member_functions_in_the_implementation_file.h item23_understand_std_move_and_std_forward.cpp item23_understand_std_move_and_std_forward.h item24_distinguish_universal_references_from_rvalue_references.cpp item24_distinguish_universal_references_from_rvalue_references.h item25_use_std_move_on_rvalue_references_std_forward_on_universal_references.cpp item25_use_std_move_on_rvalue_references_std_forward_on_universal_references.h item26_avoid_overloading_on_universal_references.cpp item26_avoid_overloading_on_universal_references.h item27_familiarize_yourself_with_alternatives_to_overriding_on_universal_references.cpp item27_familiarize_yourself_with_alternatives_to_overriding_on_universal_references.h item28_understand_reference_collapsing.cpp item28_understand_reference_collapsing.h item29_assume_that_move_operations_are_not_present_not_cheap_and_not_used.cpp item29_assume_that_move_operations_are_not_present_not_cheap_and_not_used.h item30_familiarize_yourself_with_perfect_forwarding_failure_cases.cpp item30_familiarize_yourself_with_perfect_forwarding_failure_cases.h item31_avoid_default_capture_modes.cpp item31_avoid_default_capture_modes.h item32_use_init_capture_to_move_objects_into_closures.cpp item32_use_init_capture_to_move_objects_into_closures.h item33_use_decltype_on_auto_ref_ref_parameters_to_std_forward_them.cpp item33_use_decltype_on_auto_ref_ref_parameters_to_std_forward_them.h item34_prefer_lambdas_to_std_bind.cpp item34_prefer_lambdas_to_std_bind.h item35_prefer_task_based_programming_to_thread_based.cpp item35_prefer_task_based_programming_to_thread_based.h item36_specify_std_launch_async_if_asynchronicity_is_essential.cpp item36_specify_std_launch_async_if_asynchronicity_is_essential.h item37_make_std_threads_unjoinable_on_all_paths.cpp item37_make_std_threads_unjoinable_on_all_paths.h item38_be_aware_of_varying_thread_handle_destructor_behavior.cpp item38_be_aware_of_varying_thread_handle_destructor_behavior.h item39_consider_void_futures_for_one_shot_event_communication.cpp item39_consider_void_futures_for_one_shot_event_communication.h thread_raii.h item40_use_std_atomic_for_concurrency_volatile_for_special_memory.cpp item40_use_std_atomic_for_concurrency_volatile_for_special_memory.h item41_consider_pass_by_value_for_copyable_parameters_that_are_cheap_to_move_and_always_copied.cpp item41_consider_pass_by_value_for_copyable_parameters_that_are_cheap_to_move_and_always_copied.h item42_consider_emplacement_instead_of_insertion.cpp item42_consider_emplacement_instead_of_insertion.h)
add_executable(effectivemoderncpp ${SOURCE_FILES})

#target_link_libraries(BoostAsioTest ${ws2_32_LIBRARY_PATH})
if(WIN32)
    target_link_libraries(effectivemoderncpp ${ws2_32_LIBRARY_PATH})
endif()
if(Boost_FOUND)
    target_link_libraries(effectivemoderncpp ${Boost_LIBRARIES})
endif()
