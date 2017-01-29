cmake_minimum_required(VERSION 3.6)
project(effectivemoderncpp)

if(UNIX)
    set(CMAKE_CXX_COMPILER "/home/marcin/gcc-6.3.0/bin/g++")
    set(CMAKE_C_COMPILER "/home/marcin/gcc-6.3.0/bin/gcc")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fext-numeric-literals -Wall -pedantic -pthread")
set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    SET(BOOST_ROOT C:/local/boost_1_63_0)
    SET(BOOST_LIBRARYDIR C:/local/boost_1_63_0/stage/lib)
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
set(SOURCE_FILES main.cpp item8_prefer_nullptr_to_0_and_null.cpp item8_prefer_nullptr_to_0_and_null.h item9_prefer_alias_declarations_to_typedefs.cpp item9_prefer_alias_declarations_to_typedefs.h item10_prefer_scoped_enums_to_unscoped_enums.cpp item10_prefer_scoped_enums_to_unscoped_enums.h item11_prefer_deleted_functions_to_private_undefined_ones.cpp item11_prefer_deleted_functions_to_private_undefined_ones.h item2_understand_auto_type_deduction.cpp item2_understand_auto_type_deduction.h item1_understand_template_type_deduction.cpp item1_understand_template_type_deduction.h item3_understand_decltype.cpp item3_understand_decltype.h item4_know_how_to_view_deduced_types.cpp item4_know_how_to_view_deduced_types.h item5_prefer_auto_to_explicit_type_declaration.cpp item5_prefer_auto_to_explicit_type_declaration.h item6_use_the_explicitly_typed_initializer_idiom_when_auto_deduces_undesired_types.cpp item6_use_the_explicitly_typed_initializer_idiom_when_auto_deduces_undesired_types.h item7_distinguish_between_parenthesis_and_braces_when_creating_objects.cpp item7_distinguish_between_parenthesis_and_braces_when_creating_objects.h item12_declare_overriding_functions_override.cpp item12_declare_overriding_functions_override.h item13_prefer_const_iterators_to_iterators.cpp item13_prefer_const_iterators_to_iterators.h item14_declare_functions_noexcept_if_they_wont_emit_exceptions.cpp item14_declare_functions_noexcept_if_they_wont_emit_exceptions.h)
add_executable(effectivemoderncpp ${SOURCE_FILES})

#target_link_libraries(BoostAsioTest ${ws2_32_LIBRARY_PATH})
if(WIN32)
    target_link_libraries(effectivemoderncpp ${ws2_32_LIBRARY_PATH})
endif()
if(Boost_FOUND)
    target_link_libraries(effectivemoderncpp ${Boost_LIBRARIES})
endif()
