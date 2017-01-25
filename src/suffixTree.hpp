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
    /** Value of this node. */
    int charPosition;
    /** Edges from this node. */
    std::vector<TreeNode*> children;

    TreeNode(int _charPosition)
    {
        charPosition = _charPosition;
    }

    /**
     * @param value to be added to this node.
     * @return the node connected to this node by the new edge added.
     */
    TreeNode* InsertEdge(int position)
    {
        children.push_back(new TreeNode(position));
        return children[children.size() - 1];
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

};

class SuffixTree
{

public:

    /**
     * Constructor for a Suffix Tree.
     *
     * @param str String to construct its suffix tree.
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
     * @return the node and path degree of the maximum shared prefix with [str].
     */
    std::pair<unsigned int, TreeNode*> GetActiveNode(int from, const std::string& str) const;
};

#endif // SUFFIX_TREE_SUFFIXTREE_HPP