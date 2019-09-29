#ifndef TEST_LOGIC_MANAGER_H
#define TEST_LOGIC_MANAGER_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/logic_manager.h"

//void testProposition(string prop, string expectValue)
//{
//    LogicManager lm(prop);
//    EXPECT_EQ(expectValue, lm.proposition) << "Test case " << prop;
//}

TEST(testLogicManager, testProposition)
{
//    testProposition("&(A,B)", "(A&B)");
//    testProposition("|(&(B,C),&(A,~(B)))", "((B&C)|(A&~B))");
//    testProposition("|(|(&(~(A),~(B)),&(A,B)),&(C,~(C)))", "(((~A&~B)|(A&B))|(C&~C))");
//    testProposition("|(&(~(A),~(B)),&(A,C))", "((~A&~B)|(A&C))");
//    testProposition("&(&(&(=(>(>(A,B),C),|(B,A)),>(B,&(C,B))),~C),>(=(=(C,&(C,|(B,C))),A),=(C,&(=(=(B,~B),A),~(>(C,|(C,A)))))))",
//            "((((((A>B)>C)=(B|A))&(B>(C&B)))&~C)&(((C=(C&(B|C)))=A)>(C=(((B=~B)=A)&~(C>(C|A))))))");
//    testProposition("=(=(>(~C,&(B,B)),=(>(A,>(B,A)),B)),>(>(B,=(&(&(C,B),B),B)),~(=(A,~A))))",
//            "(((~C>(B&B))=((A>(B>A))=B))=((B>(((C&B)&B)=B))>~(A=~A)))");
//    testProposition("&(C,>(|(&(A,C),|(C,>(A,A))),>(&(&(|(&(B,&(B,B)),~(B)),&(A,=(A,~(|(A,A))))),B),|(&(=(C,C),C),C))))",
//            "(C&(((A&C)|(C|(A>A)))>(((((B&(B&B))|~B)&(A&(A=~(A|A))))&B)>(((C=C)&C)|C))))");
//    testProposition("=(|(|(~(~(D)),~(A)),A),=(E,&(~(&(=(~(>(A,E)),~(D)),~(C))),C)))",
//            "(((~~D|~A)|A)=(E=(~((~(A>E)=~D)&~C)&C)))");
//    testProposition("=(|(|(~~E,~A),A),=(D,&(~(&(=(~(>(A,D)),~E),~C)),C)))",
//            "(((~~E|~A)|A)=(D=(~((~(A>D)=~E)&~C)&C)))");
//    testProposition("&(~(A),>(>(C,|(D,E)),~(B)))", "(~A&((C>(D|E))>~B))");
//    testProposition("&(|(A,B),>(C,~(&(|(D,E),>(E,~(G))))))", "((A|B)&(C>~((D|E)&(E>~G))))");
//    testProposition("|(&(|(%(=(B,D),B),~(%(=(B,&(B,%(D,C))),C))),~~C),=(|(>(&(D,D),|(A,B)),=(D,D)),|(D,D)))",
//            "(((((B=D)%B)|~((B=(B&(D%C)))%C))&~~C)|((((D&D)>(A|B))|(D=D))=(D|D)))");
//    testProposition(">(P,~(=(0,%(&(=(=(|(&(0,X),%(~(=(=(~(>(=(|(X,R),~(%(1,0))),0)),=(>(>(&(%(=(=(~(P),|(X,P)),P),&(&(%(Q,=(P,=(R,Q))),%(|(=(Q,|(R,>(%(=(&(=(0,~(0)),%(~(P),~(0))),S),Q),&(|(&(Q,~(|(%(=(&(=(>(|(~(X),~(|(P,&(1,>(|(S,Q),Q))))),1),1),P),S),X),X))),X),X)))),S),1)),0)),R),Q),S),X)),X)),R)),1),0),1),R))))",
//            "(((((B=D)%B)|~((B=(B&(D%C)))%C))&~~C)|((((D&D)>(A|B))|(D=D))=(D|D)))");

//    LogicManager lm(">(P,~(=(0,%(&(=(=(|(&(0,X),%(~(=(=(~(>(=(|(X,R),~(%(1,0))),0)),=(>(>(&(%(=(=(~(P),|(X,P)),P),&(&(%(Q,=(P,=(R,Q))),%(|(=(Q,|(R,>(%(=(&(=(0,~(0)),%(~(P),~(0))),S),Q),&(|(&(Q,~(|(%(=(&(=(>(|(~(X),~(|(P,&(1,>(|(S,Q),Q))))),1),1),P),S),X),X))),X),X)))),S),1)),0)),R),Q),S),X)),X)),R)),1),0),1),R))))");
//    EXPECT_EQ("(((((B=D)%B)|~((B=(B&(D%C)))%C))&~~C)|((((D&D)>(A|B))|(D=D))=(D|D)))", lm.proposition) << "Test case " << "(((((B=D)%B)|~((B=(B&(D%C)))%C))&~~C)|((((D&D)>(A|B))|(D=D))=(D|D)))";
//    Tree tree3 = Tree(">(P,~(=(0,%(&(=(=(|(&(0,X),%(~(=(=(~(>(=(|(X,R),~(%(1,0))),0)),=(>(>(&(%(=(=(~(P),|(X,P)),P),&(&(%(Q,=(P,=(R,Q))),%(|(=(Q,|(R,>(%(=(&(=(0,~(0)),%(~(P),~(0))),S),Q),&(|(&(Q,~(|(%(=(&(=(>(|(~(X),~(|(P,&(1,>(|(S,Q),Q))))),1),1),P),S),X),X))),X),X)))),S),1)),0)),R),Q),S),X)),X)),R)),1),0),1),R))))");
//    string prop = tree3.getProposition();
//    EXPECT_EQ("(P>~(0=((((((0&X)|(~((~(((X|R)=~(1%0))>0)=(((((((~P=(X|P))=P)%(((Q%(P=(R=Q)))&(((Q=(R|(((((0=~0)&(~P%~0))=S)%Q)>(((Q&~(((((((~X|~(P|(1&((S|Q)>Q))))>1)=1)&P)=S)%X)|X))|X)&X))))|S)%1))&0))&R)>Q)>S)=X))=X)%R))=1)=0)&1)%R)))", prop);
}

#endif // TEST_LOGIC_MANAGER_H
