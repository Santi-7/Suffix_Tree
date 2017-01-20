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
    // An edge is a char and a pointer to another node.
    std::vector<std::pair<char, TreeNode*>> edges;
};

class SuffixTree
{

public:

    /**
     * TODO: Add doc.
     * @param str
     * @return
     */
    SuffixTree(const std::string &str);

private:

    /** Root node of the suffix tree. */
    TreeNode mRootNode;
};

#endif // SUFFIX_TREE_SUFFIXTREE_HPP