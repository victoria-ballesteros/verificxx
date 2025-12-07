//
// Created by victoria on 11/6/25.
//

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "../include/StringFixedRules.h"
#include "../include/Utils.h"

//
// Tests para StringFixedRules
//

// =========================
// isValidEmailAddress
// =========================

TEST(StringsFixedRulesTests, IsValidEmailAddressValid) {
    auto [ok, payload] = StringFixedRules::isValidEmailAddress("user@example.com");
    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

TEST(StringsFixedRulesTests, IsValidEmailAddressInvalid) {
    auto [ok, payload] = StringFixedRules::isValidEmailAddress("not-an-email");
    EXPECT_FALSE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

// =========================
// isAlphabetic
// =========================

TEST(StringsFixedRulesTests, IsAlphabeticValid) {
    auto [ok, payload] = StringFixedRules::isAlphabetic("HelloWorld");
    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::get<std::vector<char>>(payload).empty());
}

TEST(StringsFixedRulesTests, IsAlphabeticInvalid) {
    auto [ok, payload] = StringFixedRules::isAlphabetic("Hello123");
    EXPECT_FALSE(ok);

    auto errors = std::get<std::vector<char>>(payload);
    ASSERT_EQ(errors.size(), 3);
    EXPECT_EQ(errors[0], '1');
    EXPECT_EQ(errors[1], '2');
    EXPECT_EQ(errors[2], '3');
}

// =========================
// isNumeric
// =========================

TEST(StringsFixedRulesTests, IsNumericValid) {
    auto [ok, payload] = StringFixedRules::isNumeric("12345");
    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::get<std::vector<char>>(payload).empty());
}

TEST(StringsFixedRulesTests, IsNumericInvalid) {
    auto [ok, payload] = StringFixedRules::isNumeric("12A45");
    EXPECT_FALSE(ok);

    auto errors = std::get<std::vector<char>>(payload);
    ASSERT_EQ(errors.size(), 1);
    EXPECT_EQ(errors[0], 'A');
}

// =========================
// isAlphanumeric
// =========================

TEST(StringsFixedRulesTests, IsAlphanumericValid) {
    auto [ok, payload] = StringFixedRules::isAlphanumeric("Abc123");
    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::get<std::vector<char>>(payload).empty());
}

TEST(StringsFixedRulesTests, IsAlphanumericInvalid) {
    auto [ok, payload] = StringFixedRules::isAlphanumeric("Abc-123");
    EXPECT_FALSE(ok);

    auto errors = std::get<std::vector<char>>(payload);
    ASSERT_EQ(errors.size(), 1);
    EXPECT_EQ(errors[0], '-');
}

// =========================
// minLength
// =========================

TEST(StringsFixedRulesTests, MinLengthValid) {
    auto [ok, payload] = StringFixedRules::minLength("abcdef", 3);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

TEST(StringsFixedRulesTests, MinLengthInvalid) {
    auto [ok, payload] = StringFixedRules::minLength("ab", 3);
    EXPECT_FALSE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

// =========================
// maxLength
// =========================

TEST(StringsFixedRulesTests, MaxLengthValid) {
    auto [ok, payload] = StringFixedRules::maxLength("abc", 5);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

TEST(StringsFixedRulesTests, MaxLengthInvalid) {
    auto [ok, payload] = StringFixedRules::maxLength("abcdef", 5);
    EXPECT_FALSE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

// =========================
// IsFullLowercase
// =========================

TEST(StringsFixedRulesTests, IsFullLowercaseValid) {
    auto [ok, payload] = StringFixedRules::isFullLowercase("hello");
    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

TEST(StringsFixedRulesTests, IsFullLowercaseInvalid) {
    auto [ok, payload] = StringFixedRules::isFullLowercase("Hello");
    EXPECT_FALSE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

// =========================
// IsFullUppercase
// =========================

TEST(StringsFixedRulesTests, IsFullUppercaseValid) {
    auto [ok, payload] = StringFixedRules::isFullUppercase("HELLO");
    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

TEST(StringsFixedRulesTests, IsFullUppercaseInvalid) {
    auto [ok, payload] = StringFixedRules::isFullUppercase("Hello");
    EXPECT_FALSE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

// =========================
// hasSubstrings
// =========================

TEST(StringsFixedRulesTests, HasSubstringsValid) {
    std::vector<std::string> subs = {"abc", "123"};
    auto [ok, payload] = StringFixedRules::hasSubstrings("YYabcZZ123", subs);

    EXPECT_TRUE(ok);

    auto found = std::get<std::vector<std::string>>(payload);
    ASSERT_EQ(found.size(), 2);
    EXPECT_EQ(found[0], "abc");
    EXPECT_EQ(found[1], "123");
}

TEST(StringsFixedRulesTests, HasSubstringsInvalid) {
    std::vector<std::string> subs = {"abc", "123"};
    auto [ok, payload] = StringFixedRules::hasSubstrings("YYYZZZ", subs);

    EXPECT_FALSE(ok);

    auto found = std::get<std::vector<std::string>>(payload);
    EXPECT_TRUE(found.empty());
}

// =========================
// isOneOf
// =========================

TEST(StringsFixedRulesTests, IsOneOfValid) {
    std::vector<std::string> values = {"red", "green", "blue"};
    auto [ok, payload] = StringFixedRules::isOneOf("green", values);

    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}

TEST(StringsFixedRulesTests, IsOneOfInvalid) {
    std::vector<std::string> values = {"red", "green", "blue"};
    auto [ok, payload] = StringFixedRules::isOneOf("yellow", values);

    EXPECT_FALSE(ok);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(payload));
}
