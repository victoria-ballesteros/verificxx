//
// Created by victoria on 11/7/25.
//

#ifndef VERIFICXX_VALIDATIONRESULTMODEL_H
#define VERIFICXX_VALIDATIONRESULTMODEL_H

#include <string>
#include <variant>
#include <vector>

using ValidationPayload = std::variant<
    std::monostate,                      // No data
    std::vector<char>,                   // Invalid characters
    std::vector<std::string>             // Substrings found (or others)
>;

struct ValidationResult {
    bool ok;
    ValidationPayload payload;
};

#endif //VERIFICXX_VALIDATIONRESULTMODEL_H