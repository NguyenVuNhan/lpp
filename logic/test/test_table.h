#ifndef TEST_TABLE_H
#define TEST_TABLE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/table/truthtable.h"
#include "../src/table/simpletable.h"
#include "../src/table/rows.h"

template<typename T = Tree>
string getHash(T tree)
{
    TruthTable table(tree);
    return table.getHashCode();
}

void testHash(const string &expect, const string &prop)
{
    // Normal
    Tree tree(prop);
    EXPECT_EQ(expect, getHash(tree)) << "Normal: -" + prop;

    //nandify
    shared_ptr<Node> nandified_Tree = tree.getTree();
    EXPECT_EQ(expect, getHash(nandified_Tree)) << "Nandified: -" + prop;

    //Normalized
    TruthTable tmpTable(prop);
    Tree normalized_Tree = tmpTable.getNormalize();
    EXPECT_EQ(expect, getHash(normalized_Tree)) << "Normalized: -" + prop;
}

TEST(TableTest, testGetHash)
{
    testHash("B8", "|(&(B,C),&(A,~(B)))");
    testHash("E0", "|(&(A,C),&(B,&(A,~(C))))");
    testHash("C3", "|(|(&(~(A),~(B)),&(A,B)),&(C,~(C)))");
    testHash("A3", "|(&(~(A),~(B)),&(A,C))");
    testHash("CF", "|(|(~(A),B),&(C,~(C)))");
    testHash("11", "&(&(&(=(>(>(A,B),C),|(B,A)),>(B,&(C,B))),~(C)),>(=(=(C,&(C,|(B,C))),A),=(C,&(=(=(B,~(B)),A),~(>(C,|(C,A)))))))");
    testHash("DD", "=(=(>(~(C),&(B,B)),=(>(A,>(B,A)),B)),>(>(B,=(&(&(C,B),B),B)),~(=(A,~(A)))))");
    testHash("48", "=(%(>(~(C),&(B,B)),=(>(A,%(B,A)),B)),%(>(B,=(&(&(C,B),B),B)),~(=(A,~(A)))))");
    testHash("AA", "&(C,>(|(&(A,C),|(C,>(A,A))),>(&(&(|(&(B,&(B,B)),~(B)),&(A,=(A,~(|(A,A))))),B),|(&(=(C,C),C),C))))");
    testHash("A5A5", "=(|(|(~(~(D)),~(A)),A),=(E,&(~(&(=(~(>(A,E)),~(D)),~(C))),C)))");
    testHash("C3C3", "=(|(|(~(~(E)),~(A)),A),=(D,&(~(&(=(~(>(A,D)),~(E)),~(C))),C)))");
    testHash("10FF", "&(~(A),>(>(C,|(D,E)),~(B)))");
    testHash("8BFF8BFF8BFF0000", "&(|(A,B),>(C,~(&(|(D,E),>(E,~(G))))))");
    testHash("EEEE", "|(&(|(%(=(B,D),B),~(%(=(B,&(B,%(D,C))),C))),~(~(C))),=(|(>(&(D,D),|(A,B)),=(D,D)),|(D,D)))");
    testHash("3F0FFFFF", ">(P,~(=(0,%(&(=(=(|(&(0,X),%(~(=(=(~(>(=(|(X,R),~(%(1,0))),0)),=(>(>(&(%(=(=(~(P),|(X,P)),P),&(&(%(Q,=(P,=(R,Q))),%(|(=(Q,|(R,>(%(=(&(=(0,~(0)),%(~(P),~(0))),S),Q),&(|(&(Q,~(|(%(=(&(=(>(|(~(X),~(|(P,&(1,>(|(S,Q),Q))))),1),1),P),S),X),X))),X),X)))),S),1)),0)),R),Q),S),X)),X)),R)),1),0),1),R))))");
}

TEST(TableTest, testIsMatchPair)
{
    EXPECT_EQ(-1, Rows(3, true).is_match_pair(Rows(0, true)));
    EXPECT_NE(-1, Rows(3, true).is_match_pair(Rows(1, true)));
}

void testSimplify(const string &expect, const string &prop)
{
    SimpleTable table(prop);
    Tree tree = table.getNormalize();
    EXPECT_EQ(expect, getHash(tree)) << prop;
}

TEST(TableTest, testSimplify)
{
    testSimplify("B8", "|(&(B,C),&(A,~(B)))");
    testSimplify("E0", "|(&(A,C),&(B,&(A,~(C))))");
    testSimplify("48", "=(%(>(~(C),&(B,B)),=(>(A,%(B,A)),B)),%(>(B,=(&(&(C,B),B),B)),~(=(A,~(A)))))");

    SimpleTable table = SimpleTable("=( >(A,B), |( ~(A) ,B) )");
    EXPECT_EQ("1", table.getHashCode()) << "Test case =( >(A,B), |( ~(A) ,B) )";

    SimpleTable table2 = SimpleTable("||ABC");
    EXPECT_EQ("E", table2.getHashCode()) << "Test case ||ABC";
}

TEST(TableTest, testNormalize)
{
    TruthTable table = TruthTable("=( >(A,B), |( ~(A) ,B) )");
    Tree tree = table.getNormalize();
    EXPECT_EQ("((~A&~B)|(~A&B)|(A&~B)|(A&B))", tree.getProposition()) << "Test case =( >(A,B), |( ~(A) ,B) )";

    SimpleTable table2 = SimpleTable("||ABC");
    Tree tree2 = table2.getNormalize();
    EXPECT_EQ("(C|B|A)", tree2.getProposition()) << "Test case ||ABC";
}
#endif // TEST_TABLE_H
