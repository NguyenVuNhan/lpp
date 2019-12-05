#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "../proposition/tableaux/enum.h"
#include "../proposition/tableaux/stnode.h"
#include "../utils.h"

using namespace std;

class Node : public enable_shared_from_this<Node>
{
private:
    int id = -1;

protected:
    shared_ptr<Node> orSimplify(shared_ptr<Node> l, shared_ptr<Node> r);
    shared_ptr<Node> andSimplify(shared_ptr<Node> l, shared_ptr<Node> r);

public:
    bool isRulesReturned = false;
    shared_ptr<Node> left = nullptr;
    shared_ptr<Node> right = nullptr;
    list<shared_ptr<Node>> variables;
    string notation = "1";

    explicit Node(shared_ptr<Node> left = nullptr, shared_ptr<Node> right = nullptr);
    virtual ~Node();
    /*!
     * \brief travel tree and produce a graph
     * \param out File output stream
     * \param rootId Parrent Id, equal to -1 by default if there is no parent
     */
    void treeTraveler(ofstream &out, int rootId = -1);
    /*!
     * \brief get proposition prefix formular
     * \return string of prefix proposition
     */
    virtual string toStringPrefix();
    /*!
     * \brief get proposition infix formular
     * \return string of infix proposition
     */
    virtual string toString();
    /*!
     * \brief get proposition value
     * \param valList - string contains proposition variable and their value. <br>
     *        e.g. "A1B0C1"
     * \return proposition value
     */
    virtual bool getValue(string valList);
    /*!
     * \brief nandify proposition
     * \param isNegation - check if this node parent is Negation
     * \return nandified tree
     */
    virtual shared_ptr<Node> nandify(bool isNegation = false);
    /*!
     * \brief get semantic taubleux rule name
     * \param isNegation - check if this node parent is Negation
     * \return RULES - semantic taubleaux rule name
     */
    virtual RULES getSTRuleName(bool isNegation = false);
    /*!
     * \brief get semantic taubleaux node child (STNode.left and STNode.right)
     * \param[in] root - STNode
     * \param[out] root - STNode contains child
     * \param pos - position of child Node of STNode::nodes list
     * \param isNegation - check if this node parent is Negation
     */
    virtual void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation = false);
    /*!
     * \brief change variable name recursively
     * \param fromVariable - variable name to change
     * \param toVariable - new variable name
     */
    virtual void setVariable(string fromVariable, string toVariable);
    /*!
     * \brief in this function node will be
     *      - Remove bi-implicate
     *      - Remove implicate
     *      - Doing the morgan
     * \param isNegation - check if this node parent is Negation
     * \return node has been cnf filtered
     */
    virtual shared_ptr<Node> cnfFilter(bool isNegation = false);
    /*!
     * \brief cnf distribution - this function will be called after setVariable
     * \return node that applied distribution rule
     */
    virtual shared_ptr<Node> cnfDistribution();
    /*!
     * \brief get leaf of current Node
     * \param[in] listNode - empty list of shared_ptr<Node>
     * \param[out] listNode - list of shared_ptr<Node>
     */
    virtual void getLeaf(list<shared_ptr<Node>> &listNode);
    /*!
     * \brief deep copy node
     * \return a deep copy of node
     */
    virtual shared_ptr<Node> copy();
    /*!
     * \brief containedSpecialNode
     * \return True if Node is Statement otherwise False
     */
    virtual bool containedSpecialNode();
};
#endif // NODE_H
