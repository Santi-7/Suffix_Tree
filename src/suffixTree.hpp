/* ---------------------------------------------------------------------------
** suffixTree.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef SUFFIX_TREE_SUFFIXTREE_HPP
#define SUFFIX_TREE_SUFFIXTREE_HPP

#include <string>
#include <vector>

struct TreeNode
{
    /** Value of this node. */
    char value;
    /** Edges from this node. */
    std::vector<TreeNode*> children;

    TreeNode(char _value)
    {
        value = _value;
    }

    /**
     * @param value to be added to this node.
     * @return the node connected to this node by the new edge added.
     */
    TreeNode* InsertEdge(const char value)
    {
        children.push_back(new TreeNode(value));
        return children[children.size() - 1];
    }

    /**
     * @param value value to look for.
     * @param node This parameter will be updated to the node of the tree following
     *  by the desired edge, if it exists.
     * @return True if the edge with the desired value exists, false otherwise.
     */
    bool HasEdge(const char value, TreeNode* &node)
    {
        // Check all the children.
        for (const auto &currentEdge : children)
        {
            // The value value is the desired.
            if (currentEdge->value == value)
            {
                node = currentEdge;
                return true;
            }
        }
        // No value
        return false;
    }

    /**
     * TODO: Add doc.
     * @return
     */
    std::string Compact()
    {
        std::string retVal = "";
        TreeNode* tmpNode = this;
        while (tmpNode->children.size() == 1)
        {
            retVal += tmpNode->value;
            tmpNode = tmpNode->children[0];
        }
        return retVal + tmpNode->value;
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
    std::pair<unsigned int, TreeNode*> GetPathDegree(const std::string &str) const;
};

#endif // SUFFIX_TREE_SUFFIXTREE_HPP