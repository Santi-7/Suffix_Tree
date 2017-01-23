/* ---------------------------------------------------------------------------
** compactSuffixTree.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef SUFFIX_TREE_COMPACTSUFFIXTREE_HPP
#define SUFFIX_TREE_COMPACTSUFFIXTREE_HPP

#include "suffixTree.hpp"

#include <string>
#include <vector>

struct CompactTreeNode
{
    /** Value of this node. */
    std::string value;
    /** Edges from this node. */
    std::vector<CompactTreeNode*> children;

    CompactTreeNode(std::string _value)
    {
        value = _value;
    }
};

class CompactSuffixTree
{

public:

    /**
     * Constructor for a Compact Suffix Tree.
     *
     * @param str String to construct its compact suffix tree.
     * @return A compact suffix tree of [str].
     */
    CompactSuffixTree(const std::string &str);

    /**
     * Prints this Compact Suffix Tree.
     */
    void Print();

private:

    /** Root node of the compact suffix tree. */
    CompactTreeNode* mRootNode;

    /**
     * TODO: Add doc.
     * @param node
     * @return
     */
    CompactTreeNode* GetCompactTree(TreeNode* node);

    /**
     * TODO: Add doc.
     * @param node
     */
    void PrintFromNode(CompactTreeNode* node);
};

#endif // SUFFIX_TREE_COMPACTSUFFIXTREE_HPP