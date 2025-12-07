#pragma once
#include <string>
#include <vector>
#include <functional>
#include "StringFixedRules.h"

namespace validation {

    class Verificxx {
    private:
        std::string value;
        bool allowEmpty;
        std::vector<std::function<ValidationResult()>> pendingRules;
        std::vector<ValidationResult> errors;

    public:
        explicit Verificxx(std::string value, bool allowEmpty = false)
            : value(std::move(value)), allowEmpty(allowEmpty) {}

        Verificxx& isValidEmailAddress() {
            pendingRules.emplace_back([this]() {
                return StringFixedRules::isValidEmailAddress(value);
            });
            return *this;
        }

        Verificxx& isAlphabetic() {
            pendingRules.emplace_back([this]() {
                return StringFixedRules::isAlphabetic(value);
            });
            return *this;
        }

        Verificxx& isNumeric() {
            pendingRules.emplace_back([this]() {
                return StringFixedRules::isNumeric(value);
            });
            return *this;
        }

        Verificxx& isAlphanumeric() {
            pendingRules.emplace_back([this]() {
                return StringFixedRules::isAlphanumeric(value);
            });
            return *this;
        }

        Verificxx& minLength(int min_length) {
            pendingRules.emplace_back([this, min_length]() {
                return StringFixedRules::minLength(value, min_length);
            });
            return *this;
        }

        Verificxx& maxLength(int max_length) {
            pendingRules.emplace_back([this, max_length]() {
                return StringFixedRules::maxLength(value, max_length);
            });
            return *this;
        }

        Verificxx& isFullLowercase() {
            pendingRules.emplace_back([this]() {
                return StringFixedRules::isFullLowercase(value);
            });
            return *this;
        }

        Verificxx& isFullUppercase() {
            pendingRules.emplace_back([this]() {
                return StringFixedRules::isFullUppercase(value);
            });
            return *this;
        }

        Verificxx& hasSubstrings(const std::vector<std::string>& substrings) {
            pendingRules.emplace_back([this, substrings]() {
                return StringFixedRules::hasSubstrings(value, substrings);
            });
            return *this;
        }

        Verificxx& isOneOf(std::vector<std::string> fixedValues) {
            pendingRules.emplace_back([this, fixedValues]() {
                return StringFixedRules::isOneOf(value, const_cast<std::vector<std::string>&>(fixedValues));
            });
            return *this;
        }

        bool execute() {
            errors.clear();

            if (value.empty()) {
                if (!allowEmpty) {
                    errors.push_back({ false, std::monostate{} });
                    return false;
                }
                return true;
            }

            for (auto& rule : pendingRules) {
                if (ValidationResult r = rule(); !r.ok) {
                    errors.push_back(r);
                }
            }

            return errors.empty();
        }

        [[nodiscard]] bool valid() const {
            return errors.empty();
        }

        [[nodiscard]] const std::vector<ValidationResult>& getErrors() const {
            return errors;
        }
    };
}
