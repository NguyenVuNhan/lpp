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

    tree = Predicate("!xAxy");
//    prop = tree.getProposition();
//    EXPECT_EQ("!x.A(x,y)", prop);
}

#endif // TEST_TREE_H
