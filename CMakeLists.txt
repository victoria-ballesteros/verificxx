cmake_minimum_required(VERSION 4.0)
project(verificxx)

set(CMAKE_CXX_STANDARD 20)

add_library(verificxx SHARED
        main.cpp
        include/IVerify.h
        src/Verify.cpp
        src/services/rules/StringsFixedRules.cpp
        include/ErrorMessages.h
        include/Utils.h)
