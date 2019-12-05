#ifndef CNF_H
#define CNF_H
/*! \file cnf.h
 *  \brief Conjunction normal form solver.
 */

#include "../notation/multiand.h"
#include "../proposition/tree.h"
#include "../src/logging.h"

/*!
 * \brief The Reso struct. Contain resolution and SubtituteResolution
 */
struct Reso
{
    /*!
     * \brief resolution
     */
    shared_ptr<Node> resolution = make_shared<MultiAnd>();
    /*!
     * \brief subtitute resolution
     */
    shared_ptr<Node> subtituteSolution = make_shared<MultiAnd>();
};

/*!
 * \brief The Public interface of CNF
 */
struct I_CNF
{
    /*!
     * \brief Solve non-janus based on MulitiAnd node and variable v
     * \param[in] node - MultiAnd Node pointer to find janus
     * \param[out] node - node will be filter out if janus have found
     * \param v - String represent for current variable
     * \return String contains founded janus <br>
     *         Emplty string if janus not found
     */
    string solveNonJanus(shared_ptr<Node> node, char v);
    /*!
     * \brief Resolution based on MulitiAnd node and variable v
     * \param node
     * \param v
     * \return Reso, contain node Resolution and Subtitute Resolution
     */
    Reso resolution(shared_ptr<Node> node, char v);
    /*!
     * \brief Check if node is useless
     * \param node - MultiOr node
     * \return True  - if node is useless <br>
     *         False - if node is not useless
     */
    static bool isUseless(shared_ptr<Node> node);
    /*!
     * \brief Convert node to MultiAnd, remove douplicate element and sort element
     *        This function are being used after generateCNF
     * \param node - node to convert
     * \return MultiAnd node, with deep of 3
     * \sa Node::getLeaf, I_CNF::generateCNF
     */
    shared_ptr<Node> nodeToMultiAnd(shared_ptr<Node> node);
    /*!
     * \brief generate CNF form based on originTree,
     *        originTree will be changed, to prevent lost data, use deep copy of Node
     * \param originTree - Node pointer, origin tree to convert to CNF
     * \return CNF tree
     * \sa Node::copy
     */
    shared_ptr<Node> generateCNF(shared_ptr<Node> originTree);
protected:
    /*!
     * \brief Check if Node contains Janus
     * \param node - Node pointer to check for Janus
     * \return True  - If Janus found <br>
     *         False - If Janus not found
     */
    bool findJanus(shared_ptr<Node> node);
    /*!
     * \brief get unique list of node
     * \param[in] l - list of node contains douplicate member
     * \param[out] l - list of node contains unique member only
     */
    void getUniqueList(list<shared_ptr<Node> > &l);
private:
    /*!
     * \brief check if node contain variable v
     * \param nodes - Node, node to check
     * \param v - String, variable v
     * \return True  - if node contains variable v <br>
     *         False - if node does not contains variable v
     */
    bool isContain(shared_ptr<Node> nodes, string v);
    /*!
     * \brief merge two Node::variables list.
     *        This function use for MultiOr, used by I_CNF::resolution
     * \param node1 - first node
     * \param node2 - second node
     * \param v - string of variable v, upper case
     * \param not_v - string of variable v, lowercase
     * \return merged Node
     */
    shared_ptr<Node> mergeNode(shared_ptr<Node> node1, shared_ptr<Node> node2, string v, string not_v);
};

/*!
 * \brief The CNF class
 */
class CNF : protected I_CNF,
            public Tree
{
public:
    /*!
     * \brief CNF constructor, generate CNF of normal tree
     * \param otherTree - tree to be convert to cnf form
     */
    CNF(shared_ptr<Node> otherTree);
    /*!
     * \brief CNF constructor, parse a CNF tree
     * \param prop - proposition
     */
    CNF(string prop="");
    ~CNF() override;
    //! @copydoc Tree::getDavidPutnam()
    string getDavidPutnam() override;
    list<string> getListVariable() override;

private:
    /*!
     * \brief parse cnf proposition
     * \param prop - cnf string of proposition
     * \return MultiAnd represent proposition
     */
    shared_ptr<Node> parse(string prop);
    /*!
     * \brief get MultiOr base on proposition
     * \param prop - cnf string of proposition
     * \return MultiOr represent proposition
     */
    shared_ptr<Node> getMultiOr(string prop);
    /*!
     * \brief get David Putnam, this function is used by a public function
     * \param tree - cnf tree
     * \param pos - current variable position
     * \param[out] result - string, represent Devaid Putname result
     */
    void getDavidPutnam(shared_ptr<Node> tree, uint pos, string &result);
};

#endif // CNF_H
