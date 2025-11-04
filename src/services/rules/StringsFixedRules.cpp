//
// Created by victoria on 11/3/25.
//

#include <string>
#include <vector>
#include "../../../include/Utils.h"
#include "../../../include/ErrorMessages.h"


class StringsFixedRules {
    public:
    static void isEmpty(const std::string& value, std::vector<std::string>& errors) {
        if (value.empty()) {
            errors.emplace_back(ErrorMessages::EMPTY_VALUE);
        }
    }
};
