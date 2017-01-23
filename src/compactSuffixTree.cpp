/* ---------------------------------------------------------------------------
** compactSuffixTree.cpp
** Implementation for Compact Suffix Tree class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "compactSuffixTree.hpp"

#include <iostream>

using namespace std;

CompactSuffixTree::CompactSuffixTree(const string &str)
{
    SuffixTree baseTree(str);
    mRootNode = GetCompactTree(baseTree.GetRoot());
}

CompactSuffixTree::CompactSuffixTree(CompactTreeNode* &rootNode)
: mRootNode(rootNode)
{}

CompactTreeNode* CompactSuffixTree::GetCompactTree(TreeNode* node)
{
    CompactTreeNode* newNode;
    string compacted = node->Compact();
    if (compacted != "")
    {
        newNode = new CompactTreeNode(compacted);
        for (int i = 0; i < compacted.size()-1; ++i)
        {
            node = node->children[0];
        }
        for (int i = 0; i < node->children.size(); ++i)
        {
            newNode->children.push_back(GetCompactTree(node->children[i]));
        }
    }
    else
    {
        return nullptr;
    }
    return newNode;
}

string CompactSuffixTree::GetLongestRepeatedSubstring()
{
    return mRootNode->GetLongestRepeatedSubstring("");
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
        for (char c : node->value)
        {
            if (c == '$')
            {
                cout << "\\$";
            }
            else cout << c;
        }
        cout << " ]\n";
    }
    else
    {
        cout << "[";
        for (char c : node->value)
        {
            if (c == '$')
            {
                cout << "\\$";
            }
            else cout << c;
        }
        cout << ' ';
        for (int i = 0; i < node->children.size(); ++i)
        {
            PrintFromNode(node->children[i]);
        }
        cout << " ] ";
    }
}