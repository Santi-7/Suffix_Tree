/* ---------------------------------------------------------------------------
** compactSuffixTree.cpp
** Implementation for Compact Suffix Tree class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "compactSuffixTree.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

CompactSuffixTree::CompactSuffixTree(const string &str)
{
    mStoredString = '$' + str + '$';
    SuffixTree baseTree(mStoredString);
    mRootNode = GetCompactTree(baseTree.GetRoot(), nullptr, 0);
    // Sort the node depth vector to have the deepest node first.
    sort(mDepthInfo.begin(), mDepthInfo.end(),
            [](const InnerNodeDepth& a, const InnerNodeDepth& b ) -> bool{return a.depth > b.depth;});
}

CompactSuffixTree::CompactSuffixTree(CompactTreeNode* &rootNode)
: mRootNode(rootNode)
{}

CompactTreeNode* CompactSuffixTree::GetCompactTree(TreeNode* node, CompactTreeNode* parent, int depth)
{
    CompactTreeNode* newNode;
    int begin = node->charPosition, end;
    // Advance the node until an inner node is reached
    while (node->children.size() == 1)
    {
        node = node->children[0];
    }
    end = node->charPosition;
    // Create the compact node
    newNode = new CompactTreeNode(begin, end, parent);
    if (node->children.size() > 0)
    {
        mDepthInfo.emplace_back(newNode, depth + (end - begin));
    }
    for (int i = 0; i < node->children.size(); ++i)
    {
        newNode->children.push_back(GetCompactTree(node->children[i], newNode, depth + (end - begin) + 1));
    }
    return newNode;
}

string CompactSuffixTree::GetLongestRepeatedSubstring()
{
    string tmp;
    CompactTreeNode* tmpNode = mDepthInfo.front().node;
    int currDepth = mDepthInfo.front().depth;

    tmp.reserve((unsigned int) currDepth);
    while(tmpNode != nullptr && tmpNode->parent != nullptr)
    {
        unsigned int begin = (unsigned int) tmpNode->begin, size = (unsigned int)tmpNode->end - begin + 1;
        tmp = mStoredString.substr(begin, size) + tmp;
        tmpNode = tmpNode->parent;
    }
    return tmp;
}

void CompactSuffixTree::Print()
{
    PrintFromNode(mRootNode);
}

void CompactSuffixTree::PrintFromNode(CompactTreeNode* node)
{
    if (node->children.size() == 0)
    {
        cout << "[";
        for (int i = node->begin; i <= node->end; ++i)
        {
            if (mStoredString[i] == '$')
            {
                cout << "\\$";
            }
            else cout << mStoredString[i];
        }
        cout << " ]\n";
    }
    else
    {
        cout << "[";
        for (int i = node->begin; i <= node->end; ++i)
        {
            if (mStoredString[i] == '$')
            {
                cout << "\\$";
            }
            else cout << mStoredString[i];
        }
        cout << ' ';
        for (int i = 0; i < node->children.size(); ++i)
        {
            PrintFromNode(node->children[i]);
        }
        cout << " ] ";
    }
}
