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

struct TreeNode
{
    // An edge is a string and a pointer to another node.
    std::vector<std::pair<std::string, TreeNode *>> edges;
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

private:

    /** Root node of the compact suffix tree. */
    TreeNode* mRootNode;
};

#endif // SUFFIX_TREE_COMPACTSUFFIXTREE_HPP