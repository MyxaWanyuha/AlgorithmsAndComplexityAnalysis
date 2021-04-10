#include "pch.h"
#include "../AlgoritnsLab2/TreeSort.h"

TEST(TestTreeSort, Empty) {
    std::string s("");
    TreeSort(s);
    ASSERT_EQ(s, "");
}

TEST(TestTreeSort, OneSymbol) {
    std::string s("c");
    TreeSort(s);
    ASSERT_EQ(s, "c");
}

TEST(TestTreeSort, Letters) {
    std::string s("bac");
    TreeSort(s);
    ASSERT_EQ(s, "abc");
}

TEST(TestTreeSort, EqualLetters) {
    std::string s("ffffff");
    TreeSort(s);
    ASSERT_EQ(s, "ffffff");
}

TEST(TestTreeSort, Digits) {
    std::string s("312");
    TreeSort(s);
    ASSERT_EQ(s, "123");
}

TEST(TestTreeSort, DifferentCases) {
    std::string s("aABb");
    TreeSort(s);
    ASSERT_EQ(s, "ABab");
}

TEST(TestTreeSort, SpecialSymbol) {
    std::string s("aA!B");
    TreeSort(s);
    ASSERT_EQ(s, "!ABa");
}

TEST(TestTreeSort, SymbolsAndDigitsAndLettersInDifferentCases) {
    std::string s("a6!B");
    TreeSort(s);
    ASSERT_EQ(s, "!6Ba");
}
