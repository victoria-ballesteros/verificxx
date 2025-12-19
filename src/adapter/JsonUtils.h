//
// Created by victoria on 12/7/25.
//

#ifndef VERIFICXX_JSONUTILS_H
#define VERIFICXX_JSONUTILS_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../../include/models/ColumnSchemaModel.h"

class JsonUtils {
public:
    inline static const std::string MISSING_COLUMNS_PROPERTY = "'columns' array is missing.";
    inline static const std::string MISSING_NAME_PROPERTY = "'name' property is missing for one column.";
    inline static const std::string INVALID_RULES_PROPERTY = "'rules' property must be an array.";
    inline static const std::string INVALID_SINGLE_RULE_PROPERTY = "Invalid single 'rule' property found in 'rules' array.";
    inline static const std::string INVALID_PARAMS_PROPERTY = "Single 'params' property must be an array.";

    inline static const std::string COLUMNS_PROPERTY_NAME = "columns";
    inline static const std::string COLUMN_NAME_PROPERTY = "name";
    inline static const std::string ALLOWS_EMPTY_PROPERTY = "allowsEmptyValues";
    inline static const std::string RULES_PROPERTY_NAME = "rules";
    inline static const std::string RULE_NAME_PROPERTY_NAME = "rule";
    inline static const std::string PARAMS_RULES_PROPERTY_NAME = "params";

    static nlohmann::json parseFile(std::ifstream& file);
    static void validateRootJson(const nlohmann::json& j);
    static ColumnDefinition parseColumn(const nlohmann::json& colJson);
    static std::vector<RuleDefinition> parseRules(const nlohmann::json& rulesJson);
    static RuleDefinition parseSingleRule(const nlohmann::json& ruleJson);
};


#endif //VERIFICXX_JSONUTILS_H