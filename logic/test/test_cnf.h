#ifndef TEST_CNF_H
#define TEST_CNF_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/cnf/cnf.h"
#include "../src/notation/negate.h"
#include "../src/table/truthtable.h"

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
    EXPECT_EQ("[ E, BDa, Bac, CDa, Cac ]", cnf->toString())
            << "Test case &(e,>(a,|(&(b,c),&(d,~c))))";
}

TEST_F(testICNF, isUseless)
{
    cnf = icnf.nodeToMultiAnd(cnf);
    cnf->variables.remove_if(I_CNF::isUseless);
    EXPECT_EQ("[ E, BDa, Bac, CDa ]", cnf->toString())
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
    EXPECT_EQ(expectReso, reso.resolution->toString()) << prop << " : " << v;
    EXPECT_EQ(expectSubtituReso, reso.subtituteSolution->toString());
}

TEST_F(testICNF, resolution)
{
    test_resolution("[ Cd, Cbd, bcd ]", "[ a ]", "[Adb,acd,Cbd,Cd]", 'A');
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

void testgetDavidPutnamFromTree(const string &prop, string expect = "")
{
    Tree tree(prop);
    CNF cnf(tree.getTree());
    string dvpn = cnf.getDavidPutnam();
    if(expect != "")
        EXPECT_EQ(dvpn, expect) << "David putnam: " + prop;
    if(dvpn != "UNSAT")
        EXPECT_TRUE(cnf.getValue(dvpn)) << "David putnam: " + prop;
    else
    {
        Tree negateTree(make_shared<Negate>(tree.getTree()));
        EXPECT_TRUE(negateTree.isTautology()) << "David putnam: " + prop;
    }
}
void testgetDavidPutnamFromTree2(const string &prop, string expect = "")
{
    Tree tree(prop);
    TruthTable table(tree);
    cout << table.getHashCode() << endl;
    CNF cnf(tree.getTree());
    TruthTable cnf_table(cnf.getTree());
    cout << cnf_table.getHashCode() << endl;
    cout << cnf.getProposition() << endl;
    string dvpn = cnf.getDavidPutnam();
    cout << dvpn << endl;
    if(expect != "")
        EXPECT_EQ(dvpn, expect) << "David putnam: " + prop;
    if(dvpn != "UNSAT")
        EXPECT_TRUE(cnf.getValue(dvpn)) << "David putnam: " + prop;
    else
    {
        Tree negateTree(make_shared<Negate>(tree.getTree()));
        EXPECT_TRUE(negateTree.isTautology()) << "David putnam: " + prop;
    }
}

TEST_F(testICNF, getDavidPutnam)
{
    CNF cnf = CNF("[CDE, CDEa,D,Ef,F]");
    string dvpn = cnf.getDavidPutnam();
    EXPECT_TRUE(cnf.getValue(dvpn));

    testgetDavidPutnamFromTree("&(E,>(A,|(&(B,C),&(D,~C))))");
    testgetDavidPutnamFromTree("=( >(A,B), |( ~(A) ,B) )");
    testgetDavidPutnamFromTree("&(A, B)");
    testgetDavidPutnamFromTree("|(&(B,C),&(A,~(B)))");
    testgetDavidPutnamFromTree("|(|(&(~(A),~(B)),&(A,B)),&(C,~(C)))");
    testgetDavidPutnamFromTree("|(&(~(A),~(B)),&(A,C))");
    testgetDavidPutnamFromTree("&(&(&(=(>(>(A,B),C),|(B,A)),>(B,&(C,B))),~C),>(=(=(C,&(C,|(B,C))),A),=(C,&(=(=(B,~B),A),~(>(C,|(C,A)))))))");
    testgetDavidPutnamFromTree("=(=(>(~C,&(B,B)),=(>(A,>(B,A)),B)),>(>(B,=(&(&(C,B),B),B)),~(=(A,~A))))");
    testgetDavidPutnamFromTree("&(C,>(|(&(A,C),|(C,>(A,A))),>(&(&(|(&(B,&(B,B)),~(B)),&(A,=(A,~(|(A,A))))),B),|(&(=(C,C),C),C))))");
    testgetDavidPutnamFromTree("=(|(|(~(~(D)),~(A)),A),=(E,&(~(&(=(~(>(A,E)),~(D)),~(C))),C)))");
    testgetDavidPutnamFromTree("=(|(|(~~E,~A),A),=(D,&(~(&(=(~(>(A,D)),~E),~C)),C)))");
    testgetDavidPutnamFromTree("&(~(A),>(>(C,|(D,E)),~(B)))");
    testgetDavidPutnamFromTree("&(|(A,B),>(C,~(&(|(D,E),>(E,~(G))))))");
    testgetDavidPutnamFromTree("|(&(|(%(=(B,D),B),~(%(=(B,&(B,%(D,C))),C))),~~C),=(|(>(&(D,D),|(A,B)),=(D,D)),|(D,D)))");
    testgetDavidPutnamFromTree(">(P,~(=(0,%(&(=(=(|(&(0,X),%(~(=(=(~(>(=(|(X,R),~(%(1,0))),0)),=(>(>(&(%(=(=(~(P),|(X,P)),P),&(&(%(Q,=(P,=(R,Q))),%(|(=(Q,|(R,>(%(=(&(=(0,~(0)),%(~(P),~(0))),S),Q),&(|(&(Q,~(|(%(=(&(=(>(|(~(X),~(|(P,&(1,>(|(S,Q),Q))))),1),1),P),S),X),X))),X),X)))),S),1)),0)),R),Q),S),X)),X)),R)),1),0),1),R))))");

    // Contradiction
    testgetDavidPutnamFromTree("&(&(B,=(>(|(=(A,B),C),>(~(=(A,B)),>(A,>(A,B)))),~(B))),~(D))", "UNSAT");
    testgetDavidPutnamFromTree("&(&(~(A),&(~(B),B)),~(>(=(B,B),~(A))))", "UNSAT");
    testgetDavidPutnamFromTree("~(&(>(A,&(>(>(|(C,C),&(C,|(C,=(B,A)))),|(|(C,C),A)),=(>(B,B),A))),>(~(>(B,A)),|(B,B))))", "UNSAT");
    testgetDavidPutnamFromTree("&(|(C,|(B,=(=(C,C),&(B,>(|(A,B),C))))),=(A,~(A)))", "UNSAT");

    // Tautology
    testgetDavidPutnamFromTree(">(~(=(|(=(|(|(|(C,>(%(A,B),C)),C),D),|(%(&(C,~(A)),C),>(A,B))),A),>(C,%(A,C)))),%(C,%(&(|(&(&(A,&(C,C)),|(C,A)),~(~(A))),>(~(|(~(%(A,A)),A)),A)),|(%(A,=(%(%(A,|(D,B)),A),D)),|(~(%(&(B,D),|(B,B))),|(>(C,D),C))))))");
    testgetDavidPutnamFromTree("|(>(~(>(|(C,C),B)),|(~(>(&(&(>(=(C,A),B),C),B),>(C,C))),C)),=(=(&(=(~(~(&(A,&(C,C)))),D),|(|(C,B),B)),|(&(=(>(C,C),B),C),&(A,C))),|(|(A,C),B))) ");
    testgetDavidPutnamFromTree(">(&(>(~(B),A),C),>(~(B),=(&(B,>(B,=(A,&(B,B)))),=(C,~(C))))) ");
    testgetDavidPutnamFromTree(">(>(|(P,Q),R),|(>(P,R),>(Q,R)))");
//    testgetDavidPutnamFromTree2("|(&(|(>(>(>(B,B),C),B),~(=(=(B,B),~(=(B,>(>(&(C,B),&(B,&(B,=(=(C,&(C,C)),B)))),C)))))),=(=(&(=(|(A,C),|(B,C)),=(|(&(C,|(&(C,C),B)),B),&(>(C,B),>(|(A,C),=(B,B))))),|(B,C)),|(=(=(B,A),A),&(|(~(&(C,B)),A),B)))),|(B,~(&(C,|(B,&(C,|(B,&(>(A,~(A)),A))))))))");
    testgetDavidPutnamFromTree(">(&(C,&(|(&(C,A),=(>(>(B,>(~(A),A)),B),A)),=(|(A,B),|(B,A)))),C)");
}

TEST(testCNFClass, parse)
{
    CNF cnf("[ E, BDa, Bca, CDa, Cca ]");
    EXPECT_EQ("[ E, BDa, Bca, CDa, Cca ]", cnf.getProposition());

    Tree cnf_2 = CNF("[A,B]");
    EXPECT_EQ("[ A, B ]", cnf_2.getTree()->toString());
}
#endif // TEST_CNF_H
