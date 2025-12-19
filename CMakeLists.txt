cmake_minimum_required(VERSION 3.16)
project(verificxx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex)

add_library(verificxx_lib
        src/services/rules/StringFixedRules.cpp
        src/services/SchemaManager.cpp
        src/adapter/JsonUtils.cpp
        include/models/ColumnSchemaModel.h
        include/SchemaManager.h
        include/adapter/JsonUtils.h
        include/constants/ValidationsErrorMessages.h
        include/constants/ExecutionErrorMessages.h
)

target_include_directories(verificxx_lib PUBLIC include)
target_link_libraries(verificxx_lib Boost::regex)

install(TARGETS verificxx_lib
        EXPORT verificxxTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

add_executable(verificxx_tests
        tests/test_strings_fixed_rules.cpp
        tests/test_verificxx_strings_fixed_rules.cpp
        tests/test_bulk_load_methods.cpp
        tests/test_verificxx_schema_execution.cpp
)

target_link_libraries(verificxx_tests
        verificxx_lib
        GTest::gtest
        GTest::gtest_main
)

add_custom_command(TARGET verificxx_tests
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/tests/data
        $<TARGET_FILE_DIR:verificxx_tests>/data
)

include(GoogleTest)
gtest_discover_tests(verificxx_tests)
