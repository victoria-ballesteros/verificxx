//
// Created by victoria on 11/3/25.
//

#ifndef VERIFICXX_ERRORMESSAGES_H
#define VERIFICXX_ERRORMESSAGES_H
#include <string>

namespace ErrorMessages {
    // {} are used as placeholders for dynamic strings
    inline std::string EMPTY_VALUE = "No data to validate";
    inline std::string STRING_OUT_OF_RANGE = "Value must have between {} and {} characters";
    inline std::string STRING_BOUND_SUBCEED = "Value must have over {} characters";
    inline std::string STRING_BOUND_EXCEED = "Value must have under {} characters";
    inline std::string INVALID_EMAIL_ADDRESS = "Invalid email address";
    inline std::string INVALID_ALPHABETIC_STRING = "Invalid non alphabetic characters: {}";
    inline std::string INVALID_NUMERIC_STRING = "Invalid non numeric characters: {}";
    inline std::string INVALID_ALPHANUMERIC_STRING = "Invalid non alphanumeric characters: {}";
    inline std::string INVALID_UPPERCASE_CHARACTERS = "Invalid uppercase characters where found.";
    inline std::string INVALID_LOWERCASE_CHARACTERS = "Invalid lowercase characters where found.";
    inline std::string INVALID_SUBSTRING = "Invalid substring found at index{}: {}";
    inline std::string VALUE_NOT_ALLOWED = "The given value does not belong to the fixed values list.";
};

#endif //VERIFICXX_ERRORMESSAGES_H