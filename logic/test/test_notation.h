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
    shared_ptr<Node> a = make_shared<Value>("1");
    EXPECT_TRUE(a->getValue("")) << "\t--> Test class Value";

    a = make_shared<Variable>("A");
    EXPECT_TRUE(a->getValue("A1")) << "\t--> Test class Variable";

    a = make_shared<And>(a, make_shared<Variable>("B"));
    EXPECT_FALSE(a->getValue("A1B0")) << "\t--> Test class And";

    a = make_shared<BiImplicate>(a, make_shared<Value>("1"));
    EXPECT_FALSE(a->getValue("A1B0")) << "\t--> Test class BiImplicate";

    a = make_shared<Implicate>(a, make_shared<Value>("0"));
    EXPECT_TRUE(a->getValue("A1B0")) << "\t--> Test class Implication";

    a = make_shared<NAnd>(make_shared<Value>("1"), a);
    EXPECT_FALSE(a->getValue("A1B0")) << "\t--> Test class NAnd";

    a = make_shared<Negate>(a);
    EXPECT_TRUE(a->getValue("A1B0")) << "\t--> Test class Negation";

    a = make_shared<Or>(a, make_shared<Value>("1"));
    EXPECT_TRUE(a->getValue("A1B0")) << "\t--> Test class Or";
}

TEST(NotationTest, setVariable)
{
    shared_ptr<Node> a = make_shared<Statement>("A", list<shared_ptr<Node> >({make_shared<Variable>("c"), make_shared<Variable>("b")}));
    a->setVariable("c", "a");
    EXPECT_EQ("A(a,b)", a->toString());

    a = make_shared<And>(make_shared<Variable>("a"), a);
    a->setVariable("a", "c");
    EXPECT_EQ("(c&A(c,b))", a->toString());
}

TEST(NotationTest, getSTRuleName)
{
    // -----------------------------------------------------
    //  alpha rule
    // -----------------------------------------------------
    shared_ptr<Node> node = make_shared<And>(make_shared<Variable>("P"), make_shared<Variable>("Q"));
    EXPECT_EQ(ALPHA, node->getSTRuleName()) << "Alpha rule - And";

    node = make_shared<Negate>(make_shared<Or>(make_shared<Variable>("P"), make_shared<Variable>("Q")));
    EXPECT_EQ(ALPHA, node->getSTRuleName()) << "Alpha rule - Or";

    node = make_shared<Negate>(make_shared<Implicate>(make_shared<Variable>("P"), make_shared<Variable>("Q")));
    EXPECT_EQ(ALPHA, node->getSTRuleName()) << "Alpha rule - Implication";

    // -----------------------------------------------------
    //  beta rule
    // -----------------------------------------------------
    node = make_shared<Negate>(make_shared<And>(make_shared<Variable>("P"), make_shared<Variable>("Q")));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - And";

    node = make_shared<Or>(make_shared<Variable>("P"), make_shared<Variable>("Q"));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - Or";

    node = make_shared<Implicate>(make_shared<Variable>("P"), make_shared<Variable>("Q"));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - Implication";

    node = make_shared<BiImplicate>(make_shared<Variable>("P"), make_shared<Variable>("Q"));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - Bi-implicate";

    node = make_shared<Negate>(make_shared<BiImplicate>(make_shared<Variable>("P"), make_shared<Variable>("Q")));
    EXPECT_EQ(BETA, node->getSTRuleName()) << "Beta rule - Bi-implicate";

    // -----------------------------------------------------
    //  delta rule
    // -----------------------------------------------------
    node = make_shared<Exists>(make_shared<Variable>("x"), make_shared<Statement>("A", list<shared_ptr<Node>>({make_shared<Variable>("x"), make_shared<Variable>("y")})));
    EXPECT_EQ(DELTA, node->getSTRuleName()) << "Delta rule - Exist";

    node = make_shared<Negate>(make_shared<ForAll>(make_shared<Variable>("x"), make_shared<Statement>("A", list<shared_ptr<Node>>({make_shared<Variable>("x"), make_shared<Variable>("y")}))));
    EXPECT_EQ(DELTA, node->getSTRuleName()) << "Delta rule - For all";

    // -----------------------------------------------------
    //  gamma rule
    // -----------------------------------------------------
    node = make_shared<Negate>(make_shared<Exists>(make_shared<Variable>("x"), make_shared<Statement>("A", list<shared_ptr<Node>>({make_shared<Variable>("x"), make_shared<Variable>("y")}))));
    EXPECT_EQ(GAMMA, node->getSTRuleName()) << "Gamma rule - Exist";

    node = make_shared<ForAll>(make_shared<Variable>("x"), make_shared<Statement>("A", list<shared_ptr<Node>>({make_shared<Variable>("x"), make_shared<Variable>("y")})));
    EXPECT_EQ(GAMMA, node->getSTRuleName()) << "Gamma rule - For all";
}

TEST(NotationTest, nandify)
{
    shared_ptr<Node> node = make_shared<And>(make_shared<Variable>("A"), make_shared<Variable>("B"));
    shared_ptr<Node> nandifiedNode = node->nandify();
    EXPECT_EQ("((A%B)%1)", nandifiedNode->toString()) << node->toString();

    node = make_shared<BiImplicate>(node, make_shared<Value>("1"));
    nandifiedNode = node->nandify();
    EXPECT_EQ("((((A%B)%1)%1)%((((A%B)%1)%1)%0))", nandifiedNode->toString()) << node->toString();

    node = make_shared<Implicate>(node, make_shared<Value>("0"));
    nandifiedNode = node->nandify();
    EXPECT_EQ("(((((A%B)%1)%1)%((((A%B)%1)%1)%0))%1)", nandifiedNode->toString()) << node->toString();

    node = make_shared<NAnd>(make_shared<Value>("1"), node);
    nandifiedNode = node->nandify();
    EXPECT_EQ("(1%(((((A%B)%1)%1)%((((A%B)%1)%1)%0))%1))", nandifiedNode->toString()) << node->toString();

    node = make_shared<Negate>(node);
    nandifiedNode = node->nandify();
    EXPECT_EQ("((1%(((((A%B)%1)%1)%((((A%B)%1)%1)%0))%1))%1)", nandifiedNode->toString()) << node->toString();

    node = make_shared<Or>(node, make_shared<Value>("0"));
    nandifiedNode = node->nandify();
    EXPECT_EQ("((((1%(((((A%B)%1)%1)%((((A%B)%1)%1)%0))%1))%1)%1)%1)", nandifiedNode->toString()) << node->toString();
}

void test_cnfFilter(const string &expect, shared_ptr<Node> root, const string &msg)
{
    shared_ptr<Node> tmp = root->cnfFilter();
    EXPECT_EQ(expect, tmp->toString()) << msg;
}

TEST(NotationTest, cnfFilter)
{
    shared_ptr<Node> a = make_shared<Value>("1");
    test_cnfFilter("1", a, "\t--> Test class Value");

    a = make_shared<Variable>("A");
    test_cnfFilter("A", a, "\t--> Test class Variable");

    a = make_shared<And>(a, make_shared<Variable>("B"));
    test_cnfFilter("(A&B)", a, "\t--> Test class And");

    a = make_shared<BiImplicate>(a, make_shared<Value>("1"));
    test_cnfFilter("(A&B)", a, "\t--> Test class BiImplicate");

    a = make_shared<Implicate>(a, make_shared<Value>("0"));
    test_cnfFilter("(~A|~B)", a, "\t--> Test class Implication");

    a = make_shared<NAnd>(make_shared<Value>("1"), a);
    test_cnfFilter("(A&B)", a, "\t--> Test class NAnd");

    a = make_shared<Negate>(a);
    test_cnfFilter("(~A|~B)", a, "\t--> Test class Negation");

    a = make_shared<Or>(a, make_shared<Value>("1"));
    test_cnfFilter("1", a, "\t--> Test class Or");

    a = make_shared<And>(make_shared<Variable>('E'),
                make_shared<Implicate>(make_shared<Variable>('A'),
                              make_shared<Or>(make_shared<And>(make_shared<Variable>('B'),
                                              make_shared<Variable>('C')
                                              ),
                                      make_shared<And>(make_shared<Variable>('D'),
                                              make_shared<Negate>(make_shared<Variable>('C'))
                                              )
                                      )
                              )
                );
    test_cnfFilter("(E&(~A|((B&C)|(D&~C))))", a, "\t--> Test E&(A>((B&C)&(D&~C)))");
}

#endif // TEST_NOTATIONTEST_H
