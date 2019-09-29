#ifndef TEST_CNF_H
#define TEST_CNF_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/cnf/cnf.h"

class testICNF : public ::testing::Test
{
    Tree tree = Tree("&(E,>(A,|(&(B,C),&(D,~C))))");
protected:
    I_CNF icnf;
    Node *cnf;

    testICNF()
    {
        cnf = icnf.generateCNF(tree.getTree());
    }

    ~testICNF()
    {
        delete cnf;
    }
};

TEST_F(testICNF, generateCNF)
{
    EXPECT_EQ("(E&((BDa&Bca)&(CDa&Cca)))", cnf->toString())
            << "Test case &(e,>(a,|(&(b,c),&(d,~c))))";
}

TEST_F(testICNF, nodeToMultiAnd)
{
    cnf = icnf.nodeToMultiAnd(cnf);
    EXPECT_EQ("[ E, BDa, Bca, CDa, Cca ]", cnf->toString())
            << "Test case &(e,>(a,|(&(b,c),&(d,~c))))";
}

TEST_F(testICNF, isUseless)
{
    cnf = icnf.nodeToMultiAnd(cnf);
    cnf->variables.remove_if(I_CNF::isUseless);
    EXPECT_EQ("[ E, BDa, Bca, CDa ]", cnf->toString())
            << "Test case &(e,>(a,|(&(b,c),&(d,~c))))";
}

template<typename T>
void test_list(list<T> l1, list<T> l2)
{
    EXPECT_EQ(l1.size(), l2.size()) << "Can not compare two list with diference size";
    for(auto it1 = l1.begin(), it2 = l2.begin();
        it1 != l1.end() && it2 != l2.end(); it1++, it2++)
        EXPECT_EQ(*it1, *it2);
}

TEST_F(testICNF, resolution)
{
    cnf = icnf.nodeToMultiAnd(cnf);
    cnf->variables.remove_if(I_CNF::isUseless);
    list<string> cnfStr;
    for(auto e : cnf->variables)
        cnfStr.push_back(e->toString());

    Resolution reso = icnf.resolution(cnfStr, 'c');
    test_list(reso.resolution, {"BaD", "E", "BDa"});

    list<string> tmpCNFlist;
    tmpCNFlist.push_back("PW");
    tmpCNFlist.push_back("rV");
    tmpCNFlist.push_back("pR");
    tmpCNFlist.push_back("tu");
    tmpCNFlist.push_back("Uw");
    tmpCNFlist.push_back("pv");
    tmpCNFlist.push_back("Ps");
    tmpCNFlist.push_back("ST");
    Resolution r2 = icnf.resolution(tmpCNFlist, 'p');
}

TEST(testCNFClass, parse)
{
    CNF cnf("[ E, BDa, Bca, CDa, Cca ]");
    EXPECT_EQ("[ E, BDa, Bca, CDa, Cca ]", cnf.getProposition());

}
#endif // TEST_CNF_H
