/* ---------------------------------------------------------------------------
** compactSuffixTree.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef SUFFIX_TREE_COMPACTSUFFIXTREE_HPP
#define SUFFIX_TREE_COMPACTSUFFIXTREE_HPP

#include <string>
#include <vector>
#include "suffixTree.hpp"

struct CompactTreeNode
{
    std::string value;
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
     * TODO: Add doc.
     * @param str
     * @return
     */
    CompactSuffixTree(const std::string &str);

    CompactSuffixTree(TreeNode* treeRoot);

    void Print();

private:

    /** Root node of the compact suffix tree. */
    CompactTreeNode* mRootNode;
};

#endif // SUFFIX_TREE_COMPACTSUFFIXTREE_HPP