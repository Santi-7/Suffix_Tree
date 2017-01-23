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

    /**
     * @return True if this node is a leaf in the compact suffix tree, false otherwise.
     */
    bool IsLeaf() const
    {
        return children.empty();
    }

    /**
     * TODO: Add doc.
     * @param path
     * @return
     */
    std::string GetLongestRepeatedSubstring(const std::string &path) const
    {
        std::string longest = path;
        for (CompactTreeNode* edge : children)
        {
            std::string longestEdge = edge->GetLongestRepeatedSubstring(path + value);
            if (longestEdge.size() > longest.size())
                longest = longestEdge;
        }
        return longest;
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
     * Constructor for a Compact Suffix Tree.
     *
     * @param rootNode Root node of this compact suffix tree.
     * @return A compact suffix tree with root node [rootNode].
     */
    CompactSuffixTree(CompactTreeNode* &rootNode);


    /**
     * @return The longest repeated substring of the string represented by this tree.
     */
    std::string GetLongestRepeatedSubstring();

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