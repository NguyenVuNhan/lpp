#ifndef TEST_CNF_H
#define TEST_CNF_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/cnf/cnf.h"

class TestCNF : public ::testing::Test
{
    Tree tree = Tree("&(E,>(A,|(&(B,C),&(D,~C))))");
protected:
    I_CNF icnf;
    Node *cnf;

    TestCNF()
    {
        cnf = icnf.generateCNF(tree.getTree());
    }

    ~TestCNF()
    {
        delete cnf;
    }
};

TEST_F(TestCNF, generateCNF)
{
    EXPECT_EQ("(E&((BDa&Bca)&(CDa&Cca)))", cnf->toString())
            << "Test case &(e,>(a,|(&(b,c),&(d,~c))))";
}

TEST_F(TestCNF, nodeToMultiAnd)
{
    cnf = icnf.nodeToMultiAnd(cnf);
    EXPECT_EQ("[ E, BDa, Bca, CDa, Cca ]", cnf->toString())
            << "Test case &(e,>(a,|(&(b,c),&(d,~c))))";
}

TEST_F(TestCNF, isUseless)
{
    cnf = icnf.nodeToMultiAnd(cnf);
    cnf->variables.remove_if(I_CNF::isUseless);
    EXPECT_EQ("[ E, BDa, Bca, CDa ]", cnf->toString())
            << "Test case &(e,>(a,|(&(b,c),&(d,~c))))";
}

TEST_F(TestCNF, resolution)
{
    cnf = icnf.nodeToMultiAnd(cnf);
    cnf->variables.remove_if(I_CNF::isUseless);
    list<string> cnfStr;
    for(auto e : cnf->variables)
        cnfStr.push_back(e->toString());

    Resolution reso = icnf.resolution(cnfStr, 'c');
    for(auto e : reso.resolution)
        cout << e << endl;

}
#endif // TEST_CNF_H
