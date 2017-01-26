/* ---------------------------------------------------------------------------
** suffixTree.cpp
** Implementation for Suffix Tree class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "suffixTree.hpp"

using namespace std;

// str must already be $ ... $
SuffixTree::SuffixTree(const string &str)
{
    mRootNode = new TreeNode(-1);
    // Constructs the tree with all the suffixes of the input string.
    // From 1 in order to don't save the path $ ... $
    for (unsigned int i = 1; i < str.size(); ++i)
    {
        // Node and degree of the maximum prefix shared in the tree.
        unsigned int alreadyInTree;
        TreeNode* pathNode;
        tie(alreadyInTree, pathNode) = GetActiveNode(i, str, str[i-1]);
        // Add the chars remaining to the suffix tree as a new branch.
        pathNode->DecideLeftDiverse(str[i-1]);
        for (unsigned int j = i + alreadyInTree; j < str.size(); ++j)
            pathNode = pathNode->InsertEdge(j, str[i-1]);
    }
}

TreeNode* SuffixTree::GetRoot() const
{
    return mRootNode;
}

pair<unsigned int, TreeNode*> SuffixTree::GetActiveNode(const int from, const string& str,
                                                        const char leftSymbol) const
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
        {
            currentNode->leftSymbols.push_back(leftSymbol);
            pathIndex++;
        }
        else break;
    }

    return make_pair(pathIndex, currentNode);
}