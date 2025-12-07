//
// Created by victoria on 11/5/25.
//

#ifndef VERIFICXX_RULESUTILS_H
#define VERIFICXX_RULESUTILS_H

#include <algorithm>
#include <boost/regex.hpp>
#include <string>
#include "Utils.h"

class RulesUtils {
public:
    static bool regexMatch(const boost::regex& pattern, const std::string& stringToMatch) {
        return boost::regex_match(stringToMatch, pattern);
    }

    template <typename Predicate>
    static std::vector<char> validateCharacters(
        const std::string& value,
        Predicate isValid
    ) {
        std::vector<char> invalid_characters;

        for (const char c : value) {
            if (!isValid(static_cast<unsigned char>(c))) {
                invalid_characters.emplace_back(c);
            }
        }

        return invalid_characters;
    }

    template <typename Predicate>
    static void invalidCharactersReport(
        const std::string& value,
        std::vector<std::string>& errors,
        Predicate pred,
        const std::string& errorMessageCode
    ) {
        if (auto const result = RulesUtils::validateCharacters(value, pred); !result.empty()) {
                errors.emplace_back(
                    Utils::formatMessage(
                        errorMessageCode,
                        { Utils::errorCharactersFormatter(result) }
                    )
                );
            }
        }

    template <typename Predicate>
    static bool genericConditionValidation(
        const std::string& value,
        Predicate pred
    ) {
        return std::ranges::none_of(value, [pred](unsigned const char c) {
            return pred(c);
        });
    }

    static std::vector<std::string> findSubstrings(
        const std::string& value,
        const std::vector<std::string>& substrings
    ) {
        std::vector<std::string> found;
        found.reserve(substrings.size());

        for (const auto& sub : substrings) {
            if (value.find(sub) != std::string::npos) {
                found.push_back(sub);
            }
        }

        return found;
    }
};

#endif //VERIFICXX_RULESUTILS_H