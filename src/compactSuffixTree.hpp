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

enum Constructor {NLOGN, N2};

struct CompactTreeNode
{
    /** Value of this node. */
    int begin, end;

    /** True if this node is left-diverse. */
    bool isLeftDiverse = false;

    int originalPathFirstChar;

    /** Edges from this node. */
    std::vector<CompactTreeNode*> children;

    /** Simple constructor. */
    CompactTreeNode(int _begin, int _end, int _originalPathFirstChar = 0, bool _isLeftDiverse = false)
    {
        begin = _begin;
        end = _end;
        originalPathFirstChar = _originalPathFirstChar;
        isLeftDiverse = _isLeftDiverse;
    }

    ~CompactTreeNode()
    {
        for (CompactTreeNode* child : children) delete child;
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
    CompactSuffixTree(const std::string &str, Constructor constructor = NLOGN);

    /**
     * Constructor for a Compact Suffix Tree.
     *
     * @param rootNode Root node of this compact suffix tree.
     * @return A compact suffix tree with root node [rootNode].
     */
    CompactSuffixTree(CompactTreeNode* &rootNode);

    /**
     * Destructor. Frees the memory in use by the tree structure.
     */
    ~CompactSuffixTree();

    /**
     * @return Longest repeated substring. This is, the longest substring that appears in the
     * original string at least twice.
     */
    std::string GetLongestRepeatedSubstring() const;

    /**
     * @return Vector of strings containing the maximal repetitions in the original string.
     */
    std::vector<std::string> GetMaximalRepetitions() const;

    /**
     * Prints this Compact Suffix Tree in a LaTex-friendly format.
     */
    void Print();

private:

    /** Root node of the compact suffix tree. */
    CompactTreeNode* mRootNode;

    /** String represented by the suffix tree. */
    std::string mStoredString;

    /** Vector that contains a vector with all maximal inner nodes in it. */
    std::vector<CompactTreeNode*> mMaximalNodes;

    /** Tuple that contains a pointer to the node that represents the longest repeated substring in the tree.*/
    std::tuple<CompactTreeNode*, int> mLongestSubstring = std::make_tuple(nullptr, 0);

    /**
     * Constructs a CompactTreeNode hierarchy from a non-compact TreeNode. When the new root node created is not a leaf
     * it will be stored in the depthInfo vector together with its depth (accounting for its compact depth).
     *
     * @param node Non-compact tree node from which the compact tree hierarchy will be created.
     * @param depth Distance from the root to the new subtree root node that will be returned.
     * @return Pointer to the root of the compact subtree that corresponds with the TreeNode node.
     */
    CompactTreeNode* GetCompactTree(TreeNode* node, int depth);

    /**
     * Inserts a new suffix in the tree while keeping it compact.
     *
     * @param root Node in which the suffix is to be inserted.
     * @param from First character to insert in one of root's children.
     * @param pathFirstChar First character of the suffix that is being inserted. Recursive calls in this method
     *  keep this parameter intact. The first call should have from == pathFirstChar.
     */
    void Insert(CompactTreeNode* root, const int from, const int pathFirstChar);

    /**
     * Prints the tree in the format of LaTex's forest.
     * @param node root node from which it will be printed
     */
    void PrintFromNode(CompactTreeNode* node);

    /**
     * Updates the longest substring variable if necessary.
     * @param innerNode A new inner node in the tree.
     * @param depth Depth of the new node.
     */
    void CheckInnerNode(CompactTreeNode* innerNode, int depth);
};

#endif // SUFFIX_TREE_COMPACTSUFFIXTREE_HPP