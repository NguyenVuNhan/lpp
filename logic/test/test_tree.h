#ifndef TEST_TREE_H
#define TEST_TREE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/proposition/tree.h"
#include "../src/proposition/predicate.h"

TEST(TreeTest, testParse)
{
    Tree tree = Tree("=( >(A,B), |( ~(A) ,B) )");
    string prop = tree.getProposition();
    EXPECT_EQ("((A>B)=(~A|B))", prop);

    Predicate tree2 = Predicate("!xAxy");
    prop = tree2.getProposition();
    EXPECT_EQ("(!x.A(x,y))", prop);
}

TEST(TreeTest, testGetValue)
{
    Tree tree = Tree("=( >(A,B), |( ~(A) ,B) )");
    EXPECT_TRUE(tree.getValue("A1B0"));
}

TEST(TreeTest, testNadify)
{
    Tree tree = Tree("=( >(A,B), |( ~(A) ,B) )");
    Tree tree2 = Tree(tree.getTree()->nandify());
    EXPECT_EQ("(((A%(B%1))%(((A%1)%1)%(B%1)))%(((A%(B%1))%1)%((((A%1)%1)%(B%1))%1)))", tree2.getProposition());
}

TEST(TreeTest, testSemanticTableaux)
{
    Tree tree = Tree("=( >(A,B), |( ~(A) ,B) )");
    EXPECT_TRUE(tree.isTautology());
}
#endif // TEST_TREE_H
