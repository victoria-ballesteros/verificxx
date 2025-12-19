//
// Created by victoria on 12/7/25.
//

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "SchemaManager.h"
#include "../include/Utils.h"
#include "../include/models/ColumnSchemaModel.h"

TEST(SchemaManagerTests, LoadFromJsonValidSchema) {
    std::string path = "../tests/data/data.json";
    std::ifstream file(path);
    ASSERT_TRUE(file.is_open());

    SchemaManager manager;
    ASSERT_NO_THROW(manager.loadFromJson(file));

    const auto&[columns] = manager.getSchema();

    ASSERT_EQ(columns.size(), 2);

    const auto&[name, allowsEmptyValues, rules] = columns[0];
    EXPECT_EQ(name, "email");
    EXPECT_FALSE(allowsEmptyValues);
    ASSERT_EQ(rules.size(), 1);

    EXPECT_EQ(rules[0].name, "is_valid_email");
    EXPECT_TRUE(rules[0].params.empty());

    const auto& colEdad = columns[1];
    EXPECT_EQ(colEdad.name, "age");
    EXPECT_TRUE(colEdad.allowsEmptyValues);
    ASSERT_EQ(colEdad.rules.size(), 3);

    EXPECT_EQ(colEdad.rules[0].name, "is_numeric");
    EXPECT_TRUE(colEdad.rules[0].params.empty());

    EXPECT_EQ(colEdad.rules[1].name, "min_value");
    ASSERT_EQ(colEdad.rules[1].params.size(), 1);
    EXPECT_EQ(colEdad.rules[1].params[0], "0");

    EXPECT_EQ(colEdad.rules[2].name, "max_value");
    ASSERT_EQ(colEdad.rules[2].params.size(), 1);
    EXPECT_EQ(colEdad.rules[2].params[0], "120");
}

TEST(SchemaManagerTests, AddColumnBasic) {
    SchemaManager manager;

    EXPECT_NO_THROW(manager.addColumn("firstName"));
    const auto& schema1 = manager.getSchema();
    ASSERT_EQ(schema1.columns.size(), 1);
    EXPECT_EQ(schema1.columns[0].name, "firstName");
    EXPECT_FALSE(schema1.columns[0].allowsEmptyValues);
    EXPECT_TRUE(schema1.columns[0].rules.empty());

    RuleDefinition emailRule;
    emailRule.name = "isValidEmailAddress";

    EXPECT_NO_THROW(manager.addColumn("email", false, {emailRule}));
    const auto& schema2 = manager.getSchema();
    ASSERT_EQ(schema2.columns.size(), 2);

    const auto& emailCol = schema2.columns[1];
    EXPECT_EQ(emailCol.name, "email");
    EXPECT_FALSE(emailCol.allowsEmptyValues);
    ASSERT_EQ(emailCol.rules.size(), 1);
    EXPECT_EQ(emailCol.rules[0].name, "isValidEmailAddress");

    EXPECT_THROW(manager.addColumn("email"), std::runtime_error);
}

TEST(SchemaManagerTests, RemoveColumn) {
    SchemaManager manager;

    manager.addColumn("firstName");
    manager.addColumn("email");

    EXPECT_NO_THROW(manager.removeColumn("email"));
    const auto&[columns] = manager.getSchema();
    ASSERT_EQ(columns.size(), 1);
    EXPECT_EQ(columns[0].name, "firstName");

    EXPECT_THROW(manager.removeColumn("email"), std::runtime_error);
}
