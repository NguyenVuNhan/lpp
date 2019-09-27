#ifndef TEST_TABLE_H
#define TEST_TABLE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/table/truthtable.h"
#include "../src/table/simpletable.h"
#include "../src/table/rows.h"

void test_getHash(const string &expect, const string &prop, const string &msg)
{
    TruthTable table = TruthTable(prop);

    EXPECT_EQ(expect, table.getHashCode()) << msg;
}

TEST(TableTest, testGetHash)
{
    test_getHash("F", "=( >(A,B), |( ~(A) ,B) )", "Test case default");
    test_getHash("8", "&AB", "Test case And");
    test_getHash("9", "=AB", "Test case Bi-implication");
    test_getHash("B", ">AB", "Test case Implication");
    test_getHash("7", "%AB", "Test case NAnd");
    test_getHash("1", "~A", "Test case Negate");
    test_getHash("E", "|AB", "Test case Or");
    test_getHash("A2", "&(|(A,~B),C)", "Test case &(|(A,~B),C)");
}

TEST(TableTest, testIsMatchPair)
{
    EXPECT_EQ(-1, Rows(3, true).is_match_pair(Rows(0, true)));
    EXPECT_NE(-1, Rows(3, true).is_match_pair(Rows(1, true)));
}

TEST(TableTest, testSimplify)
{
    SimpleTable table = SimpleTable("=( >(A,B), |( ~(A) ,B) )");
    EXPECT_EQ("1", table.getHashCode()) << "Test case =( >(A,B), |( ~(A) ,B) )";

    SimpleTable table2 = SimpleTable("||ABC");
    EXPECT_EQ("E", table2.getHashCode()) << "Test case ||ABC";
}

TEST(TableTest, testNormalize)
{
    TruthTable table = TruthTable("=( >(A,B), |( ~(A) ,B) )");
    Tree tree = table.getNormalize();
    EXPECT_EQ("((~A&~B)|(~A&B)|(A&~B)|(A&B))", tree.getProposition()) << "Test case =( >(A,B), |( ~(A) ,B) )";

    SimpleTable table2 = SimpleTable("||ABC");
    Tree tree2 = table2.getNormalize();
    EXPECT_EQ("(C|B|A)", tree2.getProposition()) << "Test case ||ABC";
}

#endif // TEST_TABLE_H
