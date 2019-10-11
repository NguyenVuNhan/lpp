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
    shared_ptr<Node> cnf;

    testICNF()
    {
        cnf = icnf.generateCNF(tree.getTree());
    }

    ~testICNF()
    {
        cnf.reset();
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

void test_resolution(const string &expectReso, const string &expectSubtituReso,
                     const string &prop, const char &v)
{
    I_CNF icnf;
    CNF cnf(prop);
    Reso reso = icnf.resolution(cnf.getTree(), v);
    EXPECT_EQ(expectReso, reso.resolution->toString());
    EXPECT_EQ(expectSubtituReso, reso.subtituteSolution->toString());
}

TEST_F(testICNF, resolution)
{
    test_resolution("[ bcd, Cbd, Cd ]", "[ A ]", "[Adb,acd,Cbd,Cd]", 'A');
}

void test_nonJanus(const string &expectNode, const string &expectNonjanus,
                     const string &prop, const char &v)
{
    I_CNF icnf;
    CNF cnf(prop);
    string non_janus = icnf.solveNonJanus(cnf.getTree(), v);
    EXPECT_EQ(expectNode, cnf.getProposition());
    EXPECT_EQ(expectNonjanus, non_janus);
}

TEST_F(testICNF, solveNonJanus)
{
    test_nonJanus("[ CDE, D, Ef, F ]", "A0", "[CDE, CDEa,D,Ef,F]", 'A');
}

TEST_F(testICNF, getDavidPutnam)
{
    Tree tree("&(E,>(A,|(&(B,C),&(D,~C))))");
    CNF cnf(tree.getTree());
    string dvpn = cnf.getDavidPutnam();
    cout << dvpn << endl;
    EXPECT_TRUE(cnf.getValue(dvpn));

    cnf = CNF("[CDE, CDEa,D,Ef,F]");
    dvpn = cnf.getDavidPutnam();
    cout << dvpn << endl;
    EXPECT_TRUE(cnf.getValue(dvpn));
}

TEST(testCNFClass, parse)
{
    CNF cnf("[ E, BDa, Bca, CDa, Cca ]");
    EXPECT_EQ("[ E, BDa, Bca, CDa, Cca ]", cnf.getProposition());
    Tree cnf_2 = CNF("[A,B]");

    EXPECT_EQ("[ A, B ]", cnf_2.getTree()->toString());

}
#endif // TEST_CNF_H
