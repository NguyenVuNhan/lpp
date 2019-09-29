#ifndef TEST_TREE_H
#define TEST_TREE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/proposition/tree.h"

void testTreeParse(string prop, string expectValue)
{
    Tree tree(prop);
    EXPECT_EQ(expectValue, tree.getProposition()) << "Test case " << prop;
}

TEST(TreeTest, testParse)
{
//    Tree tree = Tree("=( >(A,B), |( ~(A) ,B) )");
//    string prop = tree.getProposition();
//    EXPECT_EQ("((A>B)=(~A|B))", prop);
    testTreeParse("=( >(A,B), |( ~(A) ,B) )", "((A>B)=(~A|B))");
    testTreeParse("&(A,B)", "(A&B)");
    testTreeParse("|(&(B,C),&(A,~(B)))", "((B&C)|(A&~B))");
    testTreeParse("|(|(&(~(A),~(B)),&(A,B)),&(C,~(C)))", "(((~A&~B)|(A&B))|(C&~C))");
    testTreeParse("|(&(~(A),~(B)),&(A,C))", "((~A&~B)|(A&C))");
    testTreeParse("&(&(&(=(>(>(A,B),C),|(B,A)),>(B,&(C,B))),~C),>(=(=(C,&(C,|(B,C))),A),=(C,&(=(=(B,~B),A),~(>(C,|(C,A)))))))",
            "((((((A>B)>C)=(B|A))&(B>(C&B)))&~C)&(((C=(C&(B|C)))=A)>(C=(((B=~B)=A)&~(C>(C|A))))))");
    testTreeParse("=(=(>(~C,&(B,B)),=(>(A,>(B,A)),B)),>(>(B,=(&(&(C,B),B),B)),~(=(A,~A))))",
            "(((~C>(B&B))=((A>(B>A))=B))=((B>(((C&B)&B)=B))>~(A=~A)))");
    testTreeParse("&(C,>(|(&(A,C),|(C,>(A,A))),>(&(&(|(&(B,&(B,B)),~(B)),&(A,=(A,~(|(A,A))))),B),|(&(=(C,C),C),C))))",
            "(C&(((A&C)|(C|(A>A)))>(((((B&(B&B))|~B)&(A&(A=~(A|A))))&B)>(((C=C)&C)|C))))");
    testTreeParse("=(|(|(~(~(D)),~(A)),A),=(E,&(~(&(=(~(>(A,E)),~(D)),~(C))),C)))",
            "(((~~D|~A)|A)=(E=(~((~(A>E)=~D)&~C)&C)))");
    testTreeParse("=(|(|(~~E,~A),A),=(D,&(~(&(=(~(>(A,D)),~E),~C)),C)))",
            "(((~~E|~A)|A)=(D=(~((~(A>D)=~E)&~C)&C)))");
    testTreeParse("&(~(A),>(>(C,|(D,E)),~(B)))", "(~A&((C>(D|E))>~B))");
    testTreeParse("&(|(A,B),>(C,~(&(|(D,E),>(E,~(G))))))", "((A|B)&(C>~((D|E)&(E>~G))))");
    testTreeParse("|(&(|(%(=(B,D),B),~(%(=(B,&(B,%(D,C))),C))),~~C),=(|(>(&(D,D),|(A,B)),=(D,D)),|(D,D)))",
            "(((((B=D)%B)|~((B=(B&(D%C)))%C))&~~C)|((((D&D)>(A|B))|(D=D))=(D|D)))");
    testTreeParse(">(P,~(=(0,%(&(=(=(|(&(0,X),%(~(=(=(~(>(=(|(X,R),~(%(1,0))),0)),=(>(>(&(%(=(=(~(P),|(X,P)),P),&(&(%(Q,=(P,=(R,Q))),%(|(=(Q,|(R,>(%(=(&(=(0,~(0)),%(~(P),~(0))),S),Q),&(|(&(Q,~(|(%(=(&(=(>(|(~(X),~(|(P,&(1,>(|(S,Q),Q))))),1),1),P),S),X),X))),X),X)))),S),1)),0)),R),Q),S),X)),X)),R)),1),0),1),R))))",
            "(P>~(0=((((((0&X)|(~((~(((X|R)=~(1%0))>0)=(((((((~P=(X|P))=P)%(((Q%(P=(R=Q)))&(((Q=(R|(((((0=~0)&(~P%~0))=S)%Q)>(((Q&~(((((((~X|~(P|(1&((S|Q)>Q))))>1)=1)&P)=S)%X)|X))|X)&X))))|S)%1))&0))&R)>Q)>S)=X))=X)%R))=1)=0)&1)%R)))");

}

TEST(TreeTest, testGetValue)
{
    Tree tree = Tree("=( >(A,B), |( ~(A) ,B) )");
    EXPECT_TRUE(tree.getValue("A1B0"));
}

TEST(TreeTest, testNadify)
{
    Tree tree = Tree("=( >(A,B), |( ~(A) ,B) )");
    Tree tree2 = Tree(tree.getTree()->nandify());
    EXPECT_EQ("(((A%(B%1))%(((A%1)%1)%(B%1)))%(((A%(B%1))%1)%((((A%1)%1)%(B%1))%1)))", tree2.getProposition());
}

TEST(TreeTest, testSemanticTableaux)
{
    Tree tree = Tree("=( >(A,B), |( ~(A) ,B) )");
    EXPECT_TRUE(tree.isTautology());
    tree.exportProof("Test", "Test.dot");
}
#endif // TEST_TREE_H
