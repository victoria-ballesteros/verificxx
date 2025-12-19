//
// Created by victoria on 12/7/25.
//

#include "../../include/SchemaManager.h"
#include "../adapter/JsonUtils.h"
#include <nlohmann/json.hpp>
#include "../../include/Utils.h"

using json = nlohmann::json;

inline std::string DUPLICATED_COLUMN_ERROR = "Column '{}' already exists in the schema.";
inline std::string NONEXISTENT_COLUMN_ERROR = "Column '{}' was not found in the schema.";

void SchemaManager::loadFromJson(std::ifstream& file) {
    json j = JsonUtils::parseFile(file);
    JsonUtils::validateRootJson(j);

    schema.columns.clear();
    for (const auto& colJson : j[JsonUtils::COLUMNS_PROPERTY_NAME]) {
        schema.columns.push_back(JsonUtils::parseColumn(colJson));
    }
}

void SchemaManager::addColumn(
    const std::string& columnName,
    const bool allowsEmptyValues,
    const std::vector<RuleDefinition>& rules
) {
    const auto it = std::ranges::find_if(schema.columns,
                                         [&columnName](const ColumnDefinition& col) {
                                             return col.name == columnName;
                                         });
    if (it != schema.columns.end()) {
        throw std::runtime_error(Utils::formatMessage(DUPLICATED_COLUMN_ERROR, {columnName}));
    }

    ColumnDefinition col;
    col.name = columnName;
    col.allowsEmptyValues = allowsEmptyValues;
    col.rules = rules;

    schema.columns.push_back(std::move(col));
}

void SchemaManager::removeColumn(const std::string& columnName) {
    const auto it = std::ranges::find_if(schema.columns,
                                         [&columnName](const ColumnDefinition& col) {
                                             return col.name == columnName;
                                         });

    if (it == schema.columns.end()) {
        throw std::runtime_error(Utils::formatMessage(NONEXISTENT_COLUMN_ERROR, {columnName}));
    }

    schema.columns.erase(it);
}
