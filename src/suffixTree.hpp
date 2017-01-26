/* ---------------------------------------------------------------------------
** suffixTree.hpp
** Container for a suffix tree.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef SUFFIX_TREE_SUFFIXTREE_HPP
#define SUFFIX_TREE_SUFFIXTREE_HPP

#include <string>
#include <vector>
#include <tuple>

struct TreeNode
{
    /** Sentinel value of a left symbol, to decide when it's uninitialized. */
    static constexpr char LEFT_SYMBOL_SENTINEL = 0;

    /** Value of this node. */
    int charPosition;
    /** Edges from this node. */
    std::vector<TreeNode*> children;

    /** True if this node is left-diverse. */
    bool isLeftDiverse = false;
    /** A left symbol of a node, saved to determine if it's a left-diverse node. With just
     * one symbol we can already decide if it's a left-diverse node. */
    char leftSymbol = LEFT_SYMBOL_SENTINEL;

    TreeNode(int _charPosition)
    {
        charPosition = _charPosition;
    }

    /**
     * Sets the left symbol to the new value if it's still uninitialized.
     * @param leftSymbol New value for the left symbol.
     */
    void SetLeftSymbol(const char leftSymbol)
    {
        if (this->leftSymbol == LEFT_SYMBOL_SENTINEL)
            this->leftSymbol = leftSymbol;
    }

    /**
     * @param value to be added to this node.
     * @param leftSymbol Left Symbol of the new node.
     * @return the node connected to this node by the new edge added.
     */
    TreeNode* InsertEdge(const int position, const char leftSymbol)
    {
        children.push_back(new TreeNode(position));
        TreeNode* newNode = children[children.size() - 1];
        newNode->leftSymbol = leftSymbol;
        return newNode;
    }

    /**
     * @param value value to look for.
     * @param node This parameter will be updated to the node of the tree following
     *  by the desired edge, if it exists.
     * @return True if the edge with the desired value exists, false otherwise.
     */
    bool HasEdge(const char value, TreeNode* &node, const std::string& word)
    {
        // Check all the children.
        for (const auto &currentEdge : children)
        {
            // The value value is the desired.
            if (word[currentEdge->charPosition] == value)
            {
                node = currentEdge;
                return true;
            }
        }
        // No value
        return false;
    }

    /**
     * Marks isLeftDiverse as true if this node is now left diverse with the new leftSymbol.
     * @param leftSymbol to compare if the node is left diverse.
     */
    void DecideLeftDiverse(const char leftSymbol)
    {
        if (this->leftSymbol != leftSymbol)
            isLeftDiverse = true;
        else
            this->leftSymbol = leftSymbol;
    }
};

class SuffixTree
{

public:

    /**
     * Constructor for a Suffix Tree.
     *
     * @param str String to construct its suffix tree. Must contain special characters around it to make sure the tree
     *  is built correctly. Not enforced for flexibility, which makes it fragile too.
     *  The first character won't be stored!
     * @return A suffix tree of [str].
     */
    SuffixTree(const std::string &str);

    /**
     * @return The root node of this suffix tree.
     */
    TreeNode* GetRoot() const;

private:

    /** Root node of the suffix tree. */
    TreeNode* mRootNode;

    /**
     * @param str String to look for its maximum prefix.
     * @param leftSymbol Left Symbol of the new substring.
     * @return the node and path degree of the maximum shared prefix with [str].
     */
    std::pair<unsigned int, TreeNode*> GetActiveNode(const int from, const std::string &str,
                                                     const char leftSymbol) const;
};

#endif // SUFFIX_TREE_SUFFIXTREE_HPP