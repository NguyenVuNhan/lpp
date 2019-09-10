#ifndef TEST_NOTATIONTEST_H
#define TEST_NOTATIONTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

// Include all notation
#include "../src/notation/and.h"
#include "../src/notation/biimplicate.h"
#include "../src/notation/exists.h"
#include "../src/notation/forall.h"
#include "../src/notation/implicate.h"
#include "../src/notation/nand.h"
#include "../src/notation/negate.h"
#include "../src/notation/or.h"
#include "../src/notation/value.h"
#include "../src/notation/variable.h"
#include "../src/notation/statement.h"

TEST(NotationTest, getValue)
{
    Node *a = new Value("1");
    EXPECT_TRUE(a->getValue("")) << "\t--> Test class Value";
    delete a;

    a = new Variable("A");
    EXPECT_TRUE(a->getValue("A1")) << "\t--> Test class Variable";

    a = new And(a, new Variable("B"));
    EXPECT_FALSE(a->getValue("A1B0")) << "\t--> Test class And";

    a = new BiImplicate(a, new Value("1"));
    EXPECT_FALSE(a->getValue("A1B0")) << "\t--> Test class BiImplicate";

    a = new Implicate(a, new Value("0"));
    EXPECT_TRUE(a->getValue("A1B0")) << "\t--> Test class Implication";

    a = new NAnd(new Value("1"), a);
    EXPECT_FALSE(a->getValue("A1B0")) << "\t--> Test class NAnd";

    a = new Negate(a);
    EXPECT_TRUE(a->getValue("A1B0")) << "\t--> Test class Negation";

    a = new Or(a, new Value("1"));
    EXPECT_TRUE(a->getValue("A1B0")) << "\t--> Test class Or";

    delete a;
}

TEST(NotationTest, setVariable)
{
    Node *a = new Statement("A", list<Node *>({new Variable("c"), new Variable("b")}));
    a->setVariable("c", "a");
    EXPECT_EQ("A(a,b)", a->toString());

    a = new And(new Variable("a"), a);
    a->setVariable("a", "c");
    EXPECT_EQ("(c&A(c,b))", a->toString());

    delete a;
}

TEST(NotationTest, getSTRuleName)
{
    // -----------------------------------------------------
    //  alpha rule
    // -----------------------------------------------------
    Node *node = new And(new Variable("P"), new Variable("Q"));
    EXPECT_EQ(ALPHA, node->getSTRuleName()) << "Alpha rule - And";
    delete node;

    node = new Negate(new Or(new Variable("P"), new Variable("Q")));
    EXPECT_EQ(ALPHA, node->getSTRuleName()) << "Alpha rule - Or";
    delete node;

    node = new Negate(new Implicate(new Variable("P"), new Variable("Q")));
    EXPECT_EQ(ALPHA, node->getSTRuleName()) << "Alpha rule - Implication";
    delete node;

    // -----------------------------------------------------
    //  beta rule
    // -----------------------------------------------------
    node = new Negate(new And(new Variable("P"), new Variable("Q")));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - And";
    delete node;

    node = new Or(new Variable("P"), new Variable("Q"));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - Or";
    delete node;

    node = new Implicate(new Variable("P"), new Variable("Q"));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - Implication";
    delete node;

    node = new BiImplicate(new Variable("P"), new Variable("Q"));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - Bi-implicate";
    delete node;

    node = new Negate(new BiImplicate(new Variable("P"), new Variable("Q")));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - Bi-implicate";
    delete node;

    // -----------------------------------------------------
    //  delta rule
    // -----------------------------------------------------
    node = new Exists(new Variable("x"), new Statement("A", {new Variable("x"), new Variable("y")}));
    EXPECT_EQ(DELTA, node->getSTRuleName()) << "Delta rule - Exist";
    delete node;

    node = new Negate(new ForAll(new Variable("x"), new Statement("A", {new Variable("x"), new Variable("y")})));
    EXPECT_EQ(DELTA, node->getSTRuleName()) << "Delta rule - For all";
    delete node;

    // -----------------------------------------------------
    //  gamma rule
    // -----------------------------------------------------
    node = new Negate(new Exists(new Variable("x"), new Statement("A", {new Variable("x"), new Variable("y")})));
    EXPECT_EQ(GAMMA, node->getSTRuleName()) << "Gamma rule - Exist";
    delete node;

    node = new ForAll(new Variable("x"), new Statement("A", {new Variable("x"), new Variable("y")}));
    EXPECT_EQ(GAMMA, node->getSTRuleName()) << "Gamma rule - For all";
    delete node;
}

TEST(NotationTest, nandify)
{
    Node *node = new And(new Variable("A"), new Variable("B"));
    Node *nandifiedNode = node->nandify();
    EXPECT_EQ("((A%B)%1)", nandifiedNode->toString()) << node->toString();

    node = new BiImplicate(node, new Value("1"));
    nandifiedNode = node->nandify();
    EXPECT_EQ("((((A%B)%1)%1)%((((A%B)%1)%1)%0))", nandifiedNode->toString()) << node->toString();

    node = new Implicate(node, new Value("0"));
    nandifiedNode = node->nandify();
    EXPECT_EQ("(((((A%B)%1)%1)%((((A%B)%1)%1)%0))%1)", nandifiedNode->toString()) << node->toString();

    node = new NAnd(new Value("1"), node);
    nandifiedNode = node->nandify();
    EXPECT_EQ("(1%(((((A%B)%1)%1)%((((A%B)%1)%1)%0))%1))", nandifiedNode->toString()) << node->toString();

    node = new Negate(node);
    nandifiedNode = node->nandify();
    EXPECT_EQ("((1%(((((A%B)%1)%1)%((((A%B)%1)%1)%0))%1))%1)", nandifiedNode->toString()) << node->toString();

    node = new Or(node, new Value("0"));
    nandifiedNode = node->nandify();
    EXPECT_EQ("((((1%(((((A%B)%1)%1)%((((A%B)%1)%1)%0))%1))%1)%1)%1)", nandifiedNode->toString()) << node->toString();

    delete node;
}

#endif // TEST_NOTATIONTEST_H
