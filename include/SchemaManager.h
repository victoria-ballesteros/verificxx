//
// Created by victoria on 12/7/25.
//

#ifndef VERIFICXX_SCHEMAMANAGER_H
#define VERIFICXX_SCHEMAMANAGER_H
#include <algorithm>
#include <stdexcept>

#include "models/ColumnSchemaModel.h"

class SchemaManager {
    ValidationSchema schema;
public:
    SchemaManager() = default;

    [[nodiscard]] const ValidationSchema& getSchema() const { return schema; }

    void addColumn(const std::string& columnName, bool allowsEmptyValues = false, const std::vector<RuleDefinition>& rules = {});
    void removeColumn(const std::string& columnName);

    [[nodiscard]] const ColumnDefinition& getColumn(const std::string& columnName) const {
        const auto it = std::ranges::find_if(schema.columns,
                                       [&](const ColumnDefinition& col) { return col.name == columnName; });

        if (it == schema.columns.end()) {
            throw std::runtime_error("Column not found: " + columnName);
        }

        return *it;
    }

    void loadFromJson(std::ifstream& file);
};

#endif //VERIFICXX_SCHEMAMANAGER_H