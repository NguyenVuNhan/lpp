#ifndef TEST_PREDICATE_H
#define TEST_PREDICATE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/proposition/predicate.h"

TEST(PropositionTest, testParse)
{
    Predicate tree2 = Predicate("!xAxy");
    string prop = tree2.getProposition();
    EXPECT_EQ("(!x.A(x,y))", prop);
}

#endif // TEST_PREDICATE_H
