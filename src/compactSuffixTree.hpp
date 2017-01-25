/* ---------------------------------------------------------------------------
** compactSuffixTree.hpp
** Container for a compact suffix-tree. It has the necessary methods to get
** the longest repeated substring from the original string and it's maximal
** repetitive substrings in a reasonable time.
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
    int begin, end;

    /** Pointe to the parent node. */
    CompactTreeNode* parent;

    // TODO: Use this!
    /** True if this node is left-diverse. */
    bool isLeftDiverse = false;

    /** Edges from this node. */
    std::vector<CompactTreeNode*> children;

    /** Simple constructor. */
    CompactTreeNode(int _begin, int _end, CompactTreeNode* _parent)
    {
        begin = _begin;
        end = _end;
        parent = _parent;
    }
};

struct InnerNodeDepth
{
    CompactTreeNode* node;
    int depth;
    InnerNodeDepth(CompactTreeNode* _node, int _depth)
    {
        node = _node;
        depth = _depth;
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
     * @return Longest repeated substring. This is, the longest substring that appears in the
     * original string at least twice.
     */
    std::string GetLongestRepeatedSubstring();

    /**
     * Prints this Compact Suffix Tree in a LaTex-friendly format.
     */
    void Print();

private:

    /** Root node of the compact suffix tree. */
    CompactTreeNode* mRootNode;

    /** String represented by the suffix tree. */
    std::string mStoredString;

    /** Vector cantaining all inner nodes and their depths. Useful to find the longest repetition in linear time. */
    std::vector<InnerNodeDepth> mDepthInfo;

    /**
     * Constructs a CompactTreeNode hierarchy from a non-compact TreeNode. When the new root node created is not a leaf
     * it will be stored in the depthInfo vector together with its depth (accounting for its compact depth).
     *
     * @param node Non-compact tree node from which the compact tree hierarchy will be created.
     * @param depth Distance from the root to the new subtree root node that will be returned.
     * @return Pointer to the root of the compact subtree that corresponds with the TreeNode node.
     */
    CompactTreeNode* GetCompactTree(TreeNode* node, CompactTreeNode* parent, int depth);

    /**
     * Prints the tree in the format of LaTex's forest.
     * @param node root node from which it will be printed
     */
    void PrintFromNode(CompactTreeNode* node);
};

#endif // SUFFIX_TREE_COMPACTSUFFIXTREE_HPP