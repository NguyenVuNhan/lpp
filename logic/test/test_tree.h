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

void testTreeParse2(string prop, string expectValue)
{
    Tree tree(prop);
    EXPECT_EQ(expectValue, tree.getProposition()) << "Test case " << prop;
    cout << (tree.isTautology() ? "True" : "False");
    cout << (tree.getValue("P1F1X1R1T1Q1S1") ? "True" : "False");
}

TEST(TreeTest, testParse)
{
    testTreeParse("=( >(A,B), |( ~(A) ,B) )", "((A>B)=(~A|B))");
    testTreeParse("&(A,B)", "(A&B)");
    testTreeParse("|(&(B,C),&(A,~(B)))", "((B&C)|(A&~B))");
    testTreeParse("|(|(&(~(A),~(B)),&(A,B)),&(C,~(C)))", "(((~A&~B)|(A&B))|(C&~C))");
    testTreeParse("|(&(~(A),~(B)),&(A,C))", "((~A&~B)|(A&C))");
    testTreeParse("&(&(&(=(>(>(A,B),C),|(B,A)),>(B,&(C,B))),~C),>(=(=(C,&(C,|(B,C))),A),=(C,&(=(=(B,~B),A),~(>(C,|(C,A)))))))", "((((((A>B)>C)=(B|A))&(B>(C&B)))&~C)&(((C=(C&(B|C)))=A)>(C=(((B=~B)=A)&~(C>(C|A))))))");
    testTreeParse("=(=(>(~C,&(B,B)),=(>(A,>(B,A)),B)),>(>(B,=(&(&(C,B),B),B)),~(=(A,~A))))", "(((~C>(B&B))=((A>(B>A))=B))=((B>(((C&B)&B)=B))>~(A=~A)))");
    testTreeParse("&(C,>(|(&(A,C),|(C,>(A,A))),>(&(&(|(&(B,&(B,B)),~(B)),&(A,=(A,~(|(A,A))))),B),|(&(=(C,C),C),C))))", "(C&(((A&C)|(C|(A>A)))>(((((B&(B&B))|~B)&(A&(A=~(A|A))))&B)>(((C=C)&C)|C))))");
    testTreeParse("=(|(|(~(~(D)),~(A)),A),=(E,&(~(&(=(~(>(A,E)),~(D)),~(C))),C)))", "(((~~D|~A)|A)=(E=(~((~(A>E)=~D)&~C)&C)))");
    testTreeParse("=(|(|(~~E,~A),A),=(D,&(~(&(=(~(>(A,D)),~E),~C)),C)))", "(((~~E|~A)|A)=(D=(~((~(A>D)=~E)&~C)&C)))");
    testTreeParse("&(~(A),>(>(C,|(D,E)),~(B)))", "(~A&((C>(D|E))>~B))");
    testTreeParse("&(|(A,B),>(C,~(&(|(D,E),>(E,~(G))))))", "((A|B)&(C>~((D|E)&(E>~G))))");
    testTreeParse("|(&(|(%(=(B,D),B),~(%(=(B,&(B,%(D,C))),C))),~~C),=(|(>(&(D,D),|(A,B)),=(D,D)),|(D,D)))", "(((((B=D)%B)|~((B=(B&(D%C)))%C))&~~C)|((((D&D)>(A|B))|(D=D))=(D|D)))");
    testTreeParse(">(P,~(=(0,%(&(=(=(|(&(0,X),%(~(=(=(~(>(=(|(X,R),~(%(1,0))),0)),=(>(>(&(%(=(=(~(P),|(X,P)),P),&(&(%(Q,=(P,=(R,Q))),%(|(=(Q,|(R,>(%(=(&(=(0,~(0)),%(~(P),~(0))),S),Q),&(|(&(Q,~(|(%(=(&(=(>(|(~(X),~(|(P,&(1,>(|(S,Q),Q))))),1),1),P),S),X),X))),X),X)))),S),1)),0)),R),Q),S),X)),X)),R)),1),0),1),R))))", "(P>~(0=((((((0&X)|(~((~(((X|R)=~(1%0))>0)=(((((((~P=(X|P))=P)%(((Q%(P=(R=Q)))&(((Q=(R|(((((0=~0)&(~P%~0))=S)%Q)>(((Q&~(((((((~X|~(P|(1&((S|Q)>Q))))>1)=1)&P)=S)%X)|X))|X)&X))))|S)%1))&0))&R)>Q)>S)=X))=X)%R))=1)=0)&1)%R)))");

    // Contradiction
    testTreeParse("&(&(B,=(>(|(=(A,B),C),>(~(=(A,B)),>(A,>(A,B)))),~(B))),~(D))", "((B&((((A=B)|C)>(~(A=B)>(A>(A>B))))=~B))&~D)");
    testTreeParse("&(&(~(A),&(~(B),B)),~(>(=(B,B),~(A))))", "((~A&(~B&B))&~((B=B)>~A))");
    testTreeParse("~(&(>(A,&(>(>(|(C,C),&(C,|(C,=(B,A)))),|(|(C,C),A)),=(>(B,B),A))),>(~(>(B,A)),|(B,B))))", "~((A>((((C|C)>(C&(C|(B=A))))>((C|C)|A))&((B>B)=A)))&(~(B>A)>(B|B)))");
    testTreeParse("&(|(C,|(B,=(=(C,C),&(B,>(|(A,B),C))))),=(A,~(A)))", "((C|(B|((C=C)=(B&((A|B)>C)))))&(A=~A))");

    // Tautology
    testTreeParse(">(~(=(|(=(|(|(|(C,>(%(A,B),C)),C),D),|(%(&(C,~(A)),C),>(A,B))),A),>(C,%(A,C)))),%(C,%(&(|(&(&(A,&(C,C)),|(C,A)),~(~(A))),>(~(|(~(%(A,A)),A)),A)),|(%(A,=(%(%(A,|(D,B)),A),D)),|(~(%(&(B,D),|(B,B))),|(>(C,D),C))))))", "(~((((((C|((A%B)>C))|C)|D)=(((C&~A)%C)|(A>B)))|A)=(C>(A%C)))>(C%(((((A&(C&C))&(C|A))|~~A)&(~(~(A%A)|A)>A))%((A%(((A%(D|B))%A)=D))|(~((B&D)%(B|B))|((C>D)|C))))))");
    testTreeParse("|(>(~(>(|(C,C),B)),|(~(>(&(&(>(=(C,A),B),C),B),>(C,C))),C)),=(=(&(=(~(~(&(A,&(C,C)))),D),|(|(C,B),B)),|(&(=(>(C,C),B),C),&(A,C))),|(|(A,C),B))) ", "((~((C|C)>B)>(~(((((C=A)>B)&C)&B)>(C>C))|C))|((((~~(A&(C&C))=D)&((C|B)|B))=((((C>C)=B)&C)|(A&C)))=((A|C)|B)))");
    testTreeParse(">(&(>(~(B),A),C),>(~(B),=(&(B,>(B,=(A,&(B,B)))),=(C,~(C))))) ", "(((~B>A)&C)>(~B>((B&(B>(A=(B&B))))=(C=~C))))");
    testTreeParse(">(>(|(P,Q),R),|(>(P,R),>(Q,R)))", "(((P|Q)>R)>((P>R)|(Q>R)))");
    testTreeParse("|(&(|(>(>(>(B,B),C),B),~(=(=(B,B),~(=(B,>(>(&(C,B),&(B,&(B,=(=(C,&(C,C)),B)))),C)))))),=(=(&(=(|(A,C),|(B,C)),=(|(&(C,|(&(C,C),B)),B),&(>(C,B),>(|(A,C),=(B,B))))),|(B,C)),|(=(=(B,A),A),&(|(~(&(C,B)),A),B)))),|(B,~(&(C,|(B,&(C,|(B,&(>(A,~(A)),A))))))))", "((((((B>B)>C)>B)|~((B=B)=~(B=(((C&B)>(B&(B&((C=(C&C))=B))))>C))))&(((((A|C)=(B|C))&(((C&((C&C)|B))|B)=((C>B)&((A|C)>(B=B)))))=(B|C))=(((B=A)=A)|((~(C&B)|A)&B))))|(B|~(C&(B|(C&(B|((A>~A)&A)))))))");
    testTreeParse(">(&(C,&(|(&(C,A),=(>(>(B,>(~(A),A)),B),A)),=(|(A,B),|(B,A)))),C)", "((C&(((C&A)|(((B>(~A>A))>B)=A))&((A|B)=(B|A))))>C)");
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

void testTreeTautology(string prop)
{
    Tree tree(prop);
    EXPECT_TRUE(tree.isTautology()) << "Test case " << prop;
}

void testTreeContradiction(string prop)
{
    Tree tree(prop);
    EXPECT_FALSE(tree.isTautology()) << "Test case " << prop;
}

TEST(TreeTest, testSemanticTableaux)
{
    // Contradiction
    testTreeContradiction("&(&(B,=(>(|(=(A,B),C),>(~(=(A,B)),>(A,>(A,B)))),~(B))),~(D))");
    testTreeContradiction("&(&(~(A),&(~(B),B)),~(>(=(B,B),~(A))))");
    testTreeContradiction("~(&(>(A,&(>(>(|(C,C),&(C,|(C,=(B,A)))),|(|(C,C),A)),=(>(B,B),A))),>(~(>(B,A)),|(B,B))))");
    testTreeContradiction("&(|(C,|(B,=(=(C,C),&(B,>(|(A,B),C))))),=(A,~(A)))");

    // Tautology
    testTreeTautology(">(~(=(|(=(|(|(|(C,>(%(A,B),C)),C),D),|(%(&(C,~(A)),C),>(A,B))),A),>(C,%(A,C)))),%(C,%(&(|(&(&(A,&(C,C)),|(C,A)),~(~(A))),>(~(|(~(%(A,A)),A)),A)),|(%(A,=(%(%(A,|(D,B)),A),D)),|(~(%(&(B,D),|(B,B))),|(>(C,D),C))))))");
    testTreeTautology("|(>(~(>(|(C,C),B)),|(~(>(&(&(>(=(C,A),B),C),B),>(C,C))),C)),=(=(&(=(~(~(&(A,&(C,C)))),D),|(|(C,B),B)),|(&(=(>(C,C),B),C),&(A,C))),|(|(A,C),B))) ");
    testTreeTautology(">(&(>(~(B),A),C),>(~(B),=(&(B,>(B,=(A,&(B,B)))),=(C,~(C))))) ");
    testTreeTautology(">(>(|(P,Q),R),|(>(P,R),>(Q,R)))");
    testTreeTautology("|(&(|(>(>(>(B,B),C),B),~(=(=(B,B),~(=(B,>(>(&(C,B),&(B,&(B,=(=(C,&(C,C)),B)))),C)))))),=(=(&(=(|(A,C),|(B,C)),=(|(&(C,|(&(C,C),B)),B),&(>(C,B),>(|(A,C),=(B,B))))),|(B,C)),|(=(=(B,A),A),&(|(~(&(C,B)),A),B)))),|(B,~(&(C,|(B,&(C,|(B,&(>(A,~(A)),A))))))))");
    testTreeTautology(">(&(C,&(|(&(C,A),=(>(>(B,>(~(A),A)),B),A)),=(|(A,B),|(B,A)))),C)");
}
#endif // TEST_TREE_H
