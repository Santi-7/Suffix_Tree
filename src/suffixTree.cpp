/* ---------------------------------------------------------------------------
** suffixTree.cpp
** Implementation for Suffix Tree class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "suffixTree.hpp"

using namespace std;

SuffixTree::SuffixTree(const string &str)
{
    mRootNode = new TreeNode(-1);
    // Copy of the parameter.
    // Constructs the tree with all the suffixes of the input string.
    for (unsigned int i = 0; i < str.size(); ++i)
    {
        // Node and degree of the maximum prefix shared in the tree.
        unsigned int alreadyInTree;
        TreeNode* pathNode;
        tie(alreadyInTree, pathNode) = GetActiveNode(i, str);
        // Add the chars remaining to the suffix tree as a new branch.
        for (unsigned int j = i + alreadyInTree; j < str.size(); ++j)
            pathNode = pathNode->InsertEdge(j);
    }
}

TreeNode* SuffixTree::GetRoot() const
{
    return mRootNode;
}

pair<unsigned int, TreeNode*> SuffixTree::GetActiveNode(int from, const string& str) const
{
    // Return values.
    unsigned int pathIndex = 0;
    TreeNode* currentNode = mRootNode;
    // We have not analyzed all the string.
    /*
     * This is a private method, and we control all the [str] values. We know
     * we won't overflow (find a prefix equivalent to [str]) the str index.
     *
     * When the method should go to a public API, make:
     *
     *   while (str.size()-1 > pathIndex)
     */
    while (true)
    {
        // Current node has an edge with the current char examined.
        if (currentNode->HasEdge(str[from+pathIndex], currentNode, str))
            pathIndex++;
        else break;
    }

    return make_pair(pathIndex, currentNode);
}