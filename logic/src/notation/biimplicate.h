#ifndef BIIMPLICATION_H
#define BIIMPLICATION_H

#include "node.h"

class BiImplicate : public Node
{
public:
    explicit BiImplicate(shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr);
    ~BiImplicate() override;

    // Node interface
public:
    bool getValue(string valList) override;
    RULES getSTRuleName(bool isNegation) override;
    shared_ptr<Node> nandify(bool isNegation) override;
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    shared_ptr<Node> copy() override;
};

#endif // BIIMPLICATION_H
