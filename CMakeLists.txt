cmake_minimum_required(VERSION 3.16)
project(verificxx)

set(CMAKE_CXX_STANDARD 20)
enable_testing()

find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex)

# Biblioteca principal
add_library(verificxx_lib
        src/services/rules/StringFixedRules.cpp
        include/models/ColumnSchemaModel.h
)

target_include_directories(verificxx_lib PUBLIC include)
target_link_libraries(verificxx_lib Boost::regex)

# Tests
add_executable(verificxx_tests
        tests/test_strings_fixed_rules.cpp
        tests/test_verificxx_strings_fixed_rules.cpp
)

target_link_libraries(verificxx_tests
        verificxx_lib
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(verificxx_tests)
