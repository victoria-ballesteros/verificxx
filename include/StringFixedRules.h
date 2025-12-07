//
// Created by victoria on 11/6/25.
//

#ifndef VERIFICXX_STRINGFIXEDRULES_H
#define VERIFICXX_STRINGFIXEDRULES_H

#pragma once
#include <string>
#include <vector>
#include "models/ValidationResultModel.h"

class StringFixedRules {
public:
    static ValidationResult isValidEmailAddress(const std::string& value);
    static ValidationResult isAlphabetic(const std::string& value);
    static ValidationResult isNumeric(const std::string& value);
    static ValidationResult isAlphanumeric(const std::string& value);
    static ValidationResult minLength(const std::string& value, const int& min_length);
    static ValidationResult maxLength(const std::string& value, const int& max_length);
    static ValidationResult isFullLowercase(const std::string& value);
    static ValidationResult isFullUppercase(const std::string& value);
    static ValidationResult hasSubstrings(const std::string& value, const std::vector<std::string>& substrings);
    static ValidationResult isOneOf(const std::string& value, std::vector<std::string>& fixedValues);
};

#endif //VERIFICXX_STRINGFIXEDRULES_H