//
// Created by victoria on 12/18/25.
//

#include <string>
#include <vector>
#include <gtest/gtest.h>

#include "../include/Verificxx.h"

TEST(VerificxxSchemaTests, UnknownRuleProducesError) {
    validation::Verificxx validator("some_value");

    validator.addColumnToSchema("test_column", false, {{"unknownRule", {}}});

    const bool result = validator
        .fromColumnSchema("test_column")
        .execute();

    EXPECT_FALSE(result);
    EXPECT_FALSE(validator.valid());

    const auto& errors = validator.getErrors();
    ASSERT_EQ(errors.size(), 1);

    const auto& [ok, payload] = errors.front();
    EXPECT_FALSE(ok);

    ASSERT_TRUE(std::holds_alternative<std::vector<std::string>>(payload));

    const auto& messages = std::get<std::vector<std::string>>(payload);
    ASSERT_EQ(messages.size(), 1);
    EXPECT_EQ(messages[0], "Unknown rule: unknownRule");
}

