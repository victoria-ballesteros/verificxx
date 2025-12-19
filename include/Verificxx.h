#pragma once
#include <string>
#include <vector>
#include <functional>
#include "StringFixedRules.h"
#include "SchemaManager.h"

namespace validation {

    class Verificxx {
        std::string value;
        bool allowsEmptyValue;
        std::vector<std::function<ValidationResult()>> pendingRules;
        std::vector<ValidationResult> errors;

        SchemaManager schemaManager;

    public:
        explicit Verificxx(std::string value, const bool allowsEmptyValue = false)
            : value(std::move(value)), allowsEmptyValue(allowsEmptyValue) {}

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
                if (!allowsEmptyValue) {
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

        Verificxx& fromColumnSchema(const std::string& columnName) {
            const ColumnDefinition& column = schemaManager.getColumn(columnName);
            allowsEmptyValue = column.allowsEmptyValues;

            for (const auto& rule : column.rules) {
                addRuleFromDefinition(rule);
            }

            return *this;
        }

        void loadSchema(std::ifstream& file) {
            schemaManager.loadFromJson(file);
        }

        void addRuleFromDefinition(const RuleDefinition& rule) {
            if (rule.name == "isValidEmailAddress") {
                isValidEmailAddress();
            }
            else if (rule.name == "isAlphabetic") {
                isAlphabetic();
            }
            else if (rule.name == "isNumeric") {
                isNumeric();
            }
            else if (rule.name == "isAlphanumeric") {
                isAlphanumeric();
            }
            else if (rule.name == "minLength") {
                minLength(std::stoi(rule.params.at(0)));
            }
            else if (rule.name == "maxLength") {
                maxLength(std::stoi(rule.params.at(0)));
            }
            else if (rule.name == "hasSubstrings") {
                hasSubstrings(rule.params);
            }
            else if (rule.name == "isOneOf") {
                isOneOf(rule.params);
            }
            else {
                pendingRules.emplace_back(
                    [ruleName = rule.name]() -> ValidationResult {
                        return {
                            false,
                            std::vector<std::string>{ "Unknown rule: " + ruleName }
                        };
                    }
                );
            }
        }

        void addColumnToSchema(const std::string& columnName, const bool allowsEmptyValues,const std::vector<RuleDefinition>& rules) {
            schemaManager.addColumn(columnName, allowsEmptyValues, rules);
        }
    };
}
