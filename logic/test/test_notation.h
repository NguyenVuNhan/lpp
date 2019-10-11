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
#include "../src/notation/multiand.h"
#include "../src/notation/multior.h"

TEST(NotationTest, getValue)
{
    shared_ptr<Node> a = make_shared<Value>("1");
    EXPECT_TRUE(a->getValue("")) << "\t--> Test class Value";

    a = make_shared<Variable>("A");
    EXPECT_TRUE(a->getValue("A1")) << "\t--> Test class Variable";

    list<shared_ptr<Node>> variables;
    variables.push_back(a);
    variables.push_back(make_shared<Variable>("B"));
    variables.push_back(make_shared<Variable>("C"));
    variables.push_back(make_shared<Variable>("D"));
    variables.push_back(make_shared<Variable>("E"));
    variables.push_back(make_shared<Variable>("F"));
    variables.push_back(make_shared<Variable>("G"));
    variables.push_back(make_shared<Variable>("H"));
    shared_ptr<Node> multiAnd = make_shared<MultiAnd>(variables);
    EXPECT_TRUE(multiAnd->getValue("A1B1C1D1E1F1G1H1")) << "\t--> Test class MultiAnd";

    list<shared_ptr<Node>> variables_2;
    variables.push_back(a);
    variables.push_back(make_shared<Negate>(make_shared<Variable>("B")));
    variables.push_back(make_shared<Negate>(make_shared<Variable>("C")));
    variables.push_back(make_shared<Negate>(make_shared<Variable>("D")));
    variables.push_back(make_shared<Negate>(make_shared<Variable>("E")));
    variables.push_back(make_shared<Negate>(make_shared<Variable>("F")));
    variables.push_back(make_shared<Negate>(make_shared<Variable>("G")));
    variables.push_back(make_shared<Negate>(make_shared<Variable>("H")));
    shared_ptr<Node> multiAnd_2 = make_shared<MultiAnd>(variables);
    EXPECT_FALSE(multiAnd_2->getValue("A1B1C1D1E1F1G1H1")) << "\t--> Test class MultiAnd";



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
    EXPECT_EQ("Aab", a->toString());

    a = make_shared<And>(make_shared<Variable>("a"), a);
    a->setVariable("a", "c");
    EXPECT_EQ("(c&Acb)", a->toString());
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

void test_getSTNodeChild(shared_ptr<Node> node, string expect_1, string expect_2,
                         string expect_3, string expect_4, string msg)
{
    shared_ptr<STNode> stnode = make_shared<STNode>(node);
    (*stnode->nodes.begin())->getSTNodeChild(stnode, 0);
    if(stnode->left != nullptr) ASSERT_EQ(expect_1, stnode->left->toString()) << msg;
    if(stnode->right != nullptr) ASSERT_EQ(expect_2, stnode->right->toString()) << msg;
    shared_ptr<STNode> neg_stnode = make_shared<STNode>(make_shared<Negate>(node));
    (*neg_stnode->nodes.begin())->getSTNodeChild(neg_stnode, 0);
    if(neg_stnode->left != nullptr) ASSERT_EQ(expect_3, neg_stnode->left->toString()) << msg + " - negated";
    if(neg_stnode->right != nullptr) ASSERT_EQ(expect_4, neg_stnode->right->toString()) << msg + " - negated";
}

TEST(NotationTest, getSTNodeChild)
{
    shared_ptr<Variable> A = make_shared<Variable>('A');
    shared_ptr<Variable> B = make_shared<Variable>('B');
    test_getSTNodeChild(make_shared<And>(A, B),
                        "{ ~A }", "{ ~B }", "{ A, B }", "", "A&B");
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
