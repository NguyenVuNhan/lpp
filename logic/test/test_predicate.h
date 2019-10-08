#ifndef TEST_PREDICATE_H
#define TEST_PREDICATE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../src/proposition/predicate.h"

void testPredicateParse(string prop, string expectValue)
{
    Predicate tree(prop);
    EXPECT_EQ(expectValue, tree.getProposition()) << "Test case " << prop;
}

TEST(PredicateTest, testParse)
{
    testPredicateParse("!xAxy", "(!x.(Axy))");
    testPredicateParse(">(!x.(@y.(P(x,y))),@q.(!p.(P(p,q))))", "((!x.((@y.(Pxy))))>(@q.((!p.(Ppq)))))");
    testPredicateParse(">(!x.(!y.(!z.(&(O(x,y),&(O(y,z),&(G(x),~(G(z)))))))),!v.(!w.(&(O(v,w),&(G(v),~(G(w)))))))", "((!x.((!y.((!z.((Oxy&(Oyz&(Gx&~Gz)))))))))>(!v.((!w.((Ovw&(Gv&~Gw)))))))");
    testPredicateParse(">(|(!x.(P(x)),!x.(Q(x))),!x.(|(P(x),Q(x))))", "(((!x.(Px))|(!x.(Qx)))>(!x.((Px|Qx))))");
    testPredicateParse("|(>(&(@x.(!y.(Q(x,y))),!y.(P(y))),@x.(!y.(Q(x,y)))),!y.(P(y)))", "((((@x.((!y.(Qxy))))&(!y.(Py)))>(@x.((!y.(Qxy)))))|(!y.(Py)))");
    testPredicateParse(">(@q.(!p.(P(p,q))),!x.(@y.(P(x,y))))", "((@q.((!p.(Ppq))))>(!x.((@y.(Pxy)))))");
}

void testPredicateTautology(string prop, bool expect=true)
{
    Predicate tree(prop);
    if(expect)
        EXPECT_TRUE(tree.isTautology()) << "Test case " << prop;
    else
        EXPECT_FALSE(tree.isTautology()) << "Test case " << prop;
}

//void testPredicateTautology2(string prop)
//{
//    Predicate tree(prop);
//    EXPECT_TRUE(tree.isTautology()) << "Test case " << prop;
//    tree.exportProof("Test", "Test.dot");
//}

TEST(PredicateTest, testSchemanticTableaux)
{
//    testPredicateTautology("=(!x.(@y.(P(x,y))),@q.(!p.(P(p,q))))");
    testPredicateTautology(">(@x.(!y.(P(x,y))),!q.(@p.(P(p,q))))");
    testPredicateTautology(">(!x.(@y.(P(x,y))),@q.(!p.(P(p,q))))", false);
    testPredicateTautology(">(!x.(!y.(!z.(&(O(x,y),&(O(y,z),&(G(x),~(G(z)))))))),!v.(!w.(&(O(v,w),&(G(v),~(G(w)))))))");
    testPredicateTautology(">(|(!x.(P(x)),!x.(Q(x))),!x.(|(P(x),Q(x))))");
    testPredicateTautology("|(>(&(@x.(!y.(Q(x,y))),!y.(P(y))),@x.(!y.(Q(x,y)))),!y.(P(y)))");
    testPredicateTautology(">(@q.(!p.(P(p,q))),!x.(@y.(P(x,y))))");
}

#endif // TEST_PREDICATE_H
