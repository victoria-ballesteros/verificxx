//
// Created by victoria on 12/7/25.
//

#ifndef VERIFICXX_COLUMNSCHEMAMODEL_H
#define VERIFICXX_COLUMNSCHEMAMODEL_H
#include <string>
#include <vector>

struct RuleDefinition {
    std::string name;
    std::vector<std::string> params;
};

struct ColumnDefinition {
    std::string name;
    bool allowsEmptyValues;
    std::vector<RuleDefinition> rules;
};

struct ValidationSchema {
    std::vector<ColumnDefinition> columns;
};

#endif //VERIFICXX_COLUMNSCHEMAMODEL_H