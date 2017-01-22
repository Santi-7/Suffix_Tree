/* ---------------------------------------------------------------------------
** suffixTree.cpp
** Implementation for Suffix Tree class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "suffixTree.hpp"

#include <tuple>

using namespace std;

SuffixTree::SuffixTree(const string &str)
{
    mRootNode = new TreeNode(' ');
    // Copy of the parameter.
    string copy = "$" + str + "$";
    // Constructs the tree with all the suffixes of the input string.
    for (unsigned int i = 0; i < copy.size(); ++i)
    {
        // Node and degree of the maximum prefix shared in the tree.
        unsigned int pathDegree;
        TreeNode* pathNode;
        tie(pathDegree, pathNode) = GetPathDegree(copy.substr(i));
        // Add the chars remaining to the suffix tree as a new branch.
        for (unsigned int j = i + pathDegree; j < copy.size(); ++j)
            pathNode = pathNode->InsertEdge(copy[j]);
    }
}

pair<unsigned int, TreeNode*> SuffixTree::GetPathDegree(const string &str) const
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
        if (currentNode->HasEdge(str[pathIndex], currentNode))
            pathIndex++;
        else break;
    }

    return make_pair(pathIndex, currentNode);
}