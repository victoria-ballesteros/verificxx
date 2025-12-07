//
// Created by victoria on 12/2/25.
//

#include <string>
#include <vector>
#include <gtest/gtest.h>

#include "../include/Verificxx.h"
#include "../include/StringFixedRules.h"


TEST(VerificxxTests, EmptyStringShouldFailNumeric) {
    validation::Verificxx v("");

    v.isNumeric();
    v.execute();

    ASSERT_FALSE(v.valid());
    ASSERT_EQ(v.getErrors().size(), 1);
}

TEST(VerificxxTests, ChainingMultipleRulesShouldCollectErrors) {
    validation::Verificxx v("abc123");

    v.isAlphabetic()
     .minLength(10)
     .isFullLowercase()
     .execute();

    ASSERT_FALSE(v.valid());
    ASSERT_EQ(v.getErrors().size(), 2);
}

TEST(VerificxxTests, AllValidationsPassShouldBeValid) {
    validation::Verificxx v("ABC");

    v.isAlphabetic()
     .isFullUppercase()
     .minLength(2)
     .maxLength(5)
     .execute();

    // ASSERT_TRUE(v.valid());
    ASSERT_EQ(v.getErrors().size(), 0);
}

TEST(VerificxxTests, IsValidEmailAddressShouldWork) {
    validation::Verificxx v("user@example.com");

    v.isValidEmailAddress()
     .execute();

    ASSERT_TRUE(v.valid());
}

TEST(VerificxxTests, InvalidEmailShouldFail) {
    validation::Verificxx v("not-email");

    v.isValidEmailAddress()
     .execute();

    ASSERT_FALSE(v.valid());
}

TEST(VerificxxTests, IsOneOfSuccessCase) {
    const std::vector<std::string> allowed = {"apple", "banana", "grape"};
    validation::Verificxx v("banana");

    v.isOneOf(allowed)
     .execute();

    ASSERT_TRUE(v.valid());
}

TEST(VerificxxTests, IsOneOfFailCase) {
    const std::vector<std::string> allowed = {"apple", "banana", "grape"};
    validation::Verificxx v("kiwi");

    v.isOneOf(allowed)
     .execute();

    ASSERT_FALSE(v.valid());
}

TEST(VerificxxTests, HasSubstringsShouldPass) {
    const std::vector<std::string> subs = {"lo", "he"};
    validation::Verificxx v("hello");

    v.hasSubstrings(subs)
     .execute();

    ASSERT_TRUE(v.valid());
}

TEST(VerificxxTests, HasSubstringsShouldFail) {
    const std::vector<std::string> subs = {"xyz"};
    validation::Verificxx v("hello");

    v.hasSubstrings(subs)
     .execute();

    ASSERT_FALSE(v.valid());
}
