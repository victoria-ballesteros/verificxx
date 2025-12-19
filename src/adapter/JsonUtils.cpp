//
// Created by victoria on 12/7/25.
//

#include "JsonUtils.h"
#include "../../include/models/ColumnSchemaModel.h"
#include "../../include/Utils.h"
#include "../../include/constants/ExecutionErrorMessages.h"
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

json JsonUtils::parseFile(std::ifstream& file) {
    if (!file.is_open()) {
        throw std::runtime_error(ExecutionErrorMessages::FILE_NOT_OPEN);
    }

    json j;
    try {
        file >> j;
    } catch (const std::exception& e) {
        throw std::runtime_error(Utils::formatMessage(
            ExecutionErrorMessages::JSON_PARSING_ERROR, {e.what()}
        ));
    }
    return j;
}

void JsonUtils::validateRootJson(const json& j) {
    if (!j.contains(JsonUtils::COLUMNS_PROPERTY_NAME) || !j[COLUMNS_PROPERTY_NAME].is_array()) {
        throw std::runtime_error(Utils::formatMessage(
            ExecutionErrorMessages::JSON_INVALID_FORMAT, {MISSING_COLUMNS_PROPERTY}
        ));
    }
}

ColumnDefinition JsonUtils::parseColumn(const json& colJson) {
    if (!colJson.contains(COLUMN_NAME_PROPERTY) || !colJson[COLUMN_NAME_PROPERTY].is_string()) {
        throw std::runtime_error(Utils::formatMessage(
            ExecutionErrorMessages::JSON_INVALID_FORMAT, {MISSING_NAME_PROPERTY}
        ));
    }

    ColumnDefinition col;
    col.name = colJson[COLUMN_NAME_PROPERTY].get<std::string>();

    if (colJson.contains(ALLOWS_EMPTY_PROPERTY) && colJson[ALLOWS_EMPTY_PROPERTY].is_boolean()) {
        col.allowsEmptyValues = colJson[ALLOWS_EMPTY_PROPERTY].get<bool>();
    } else {
        col.allowsEmptyValues = false;
    }

    if (colJson.contains(RULES_PROPERTY_NAME)) {
        col.rules = parseRules(colJson[RULES_PROPERTY_NAME]);
    }

    return col;
}

std::vector<RuleDefinition> JsonUtils::parseRules(const json& rulesJson) {
    if (!rulesJson.is_array()) {
        throw std::runtime_error(Utils::formatMessage(
            ExecutionErrorMessages::JSON_INVALID_FORMAT, {INVALID_RULES_PROPERTY}
        ));
    }

    std::vector<RuleDefinition> rules;
    for (const auto& ruleJson : rulesJson) {
        rules.push_back(parseSingleRule(ruleJson));
    }
    return rules;
}

RuleDefinition JsonUtils::parseSingleRule(const json& ruleJson) {
    if (!ruleJson.contains(RULE_NAME_PROPERTY_NAME) || !ruleJson[RULE_NAME_PROPERTY_NAME].is_string()) {
        throw std::runtime_error(Utils::formatMessage(
            ExecutionErrorMessages::JSON_INVALID_FORMAT, {INVALID_SINGLE_RULE_PROPERTY}
        ));
    }

    RuleDefinition rule;
    rule.name = ruleJson[RULE_NAME_PROPERTY_NAME].get<std::string>();

    if (ruleJson.contains(PARAMS_RULES_PROPERTY_NAME)) {
        if (!ruleJson[PARAMS_RULES_PROPERTY_NAME].is_array()) {
            throw std::runtime_error(Utils::formatMessage(
                ExecutionErrorMessages::JSON_INVALID_FORMAT, {INVALID_PARAMS_PROPERTY}
            ));
        }
        for (const auto& param : ruleJson[PARAMS_RULES_PROPERTY_NAME]) {
            rule.params.push_back(param.get<std::string>());
        }
    }
    return rule;
}


