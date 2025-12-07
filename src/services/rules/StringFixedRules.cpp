//
// Created by victoria on 11/3/25.
//

#include "../../../include/StringFixedRules.h"
#include <string>
#include <vector>
#include "../../../include/Regexes.h"
#include "../../../include/RulesUtils.h"
#include "../../../include/models/ValidationResultModel.h"

ValidationResult StringFixedRules::isValidEmailAddress(const std::string& value) {
    return ValidationResult {
        RulesUtils::regexMatch(Regexes::emailAddressRegex, value),
        std::monostate{},
    };
}

ValidationResult StringFixedRules::isAlphabetic(const std::string& value) {
    auto error_characters = RulesUtils::validateCharacters(value, [](const char c) { return std::isalpha(static_cast<unsigned char>(c)); });
    return {
        error_characters.empty(),
        error_characters,
    };
}

ValidationResult StringFixedRules::isNumeric(const std::string& value) {
    auto error_characters = RulesUtils::validateCharacters(value, [](const char c) { return std::isdigit(static_cast<unsigned char>(c)); });
    return {
        error_characters.empty(),
        error_characters,
    };
}

ValidationResult StringFixedRules::isAlphanumeric(const std::string& value) {
    auto error_characters = RulesUtils::validateCharacters(value, [](const char c) { return std::isalnum(static_cast<unsigned char>(c)); });
    return {
        error_characters.empty(),
        error_characters,
    };
}

ValidationResult StringFixedRules::minLength(const std::string& value, const int& min_length) {
    return ValidationResult {
        value.length() >= min_length,
        std::monostate{},
    };
}

ValidationResult StringFixedRules::maxLength(const std::string& value, const int& max_length) {
    return ValidationResult {
        value.length() <= max_length,
        std::monostate{},
    };
}

ValidationResult StringFixedRules::isFullLowercase(const std::string& value) {
    return ValidationResult {
        RulesUtils::genericConditionValidation(value, [](const char c) { return std::isupper(static_cast<unsigned char>(c)); }),
        std::monostate{},
    };
}

ValidationResult StringFixedRules::isFullUppercase(const std::string& value) {
    return ValidationResult {
        RulesUtils::genericConditionValidation(value, [](const char c) { return std::islower(static_cast<unsigned char>(c)); }),
        std::monostate{},
    };
}

ValidationResult StringFixedRules::hasSubstrings(const std::string& value, const std::vector<std::string>& substrings) {
    auto const foundSubstrings = RulesUtils::findSubstrings(value, substrings);
    return ValidationResult {
        !foundSubstrings.empty(),
        foundSubstrings,
    };
}

ValidationResult StringFixedRules::isOneOf(const std::string& value, std::vector<std::string>& fixedValues) {
    const auto it = std::ranges::find(fixedValues, value);
    return ValidationResult {
        it != fixedValues.end(),
        std::monostate{},
    };
}
