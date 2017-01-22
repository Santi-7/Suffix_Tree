/* ---------------------------------------------------------------------------
** compactSuffixTree.cpp
** Implementation for Compact Suffix Tree class.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include "compactSuffixTree.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

CompactSuffixTree::CompactSuffixTree(const string &str)
{

}

string compact(TreeNode* node)
{
    bool isCompactable = true;
    string retVal = "";
    TreeNode* tmpNode = node;
    while (tmpNode->children.size() != 0)
    {
        if (tmpNode->children.size() > 1)
        {
            isCompactable = false;
            break;
        }
        retVal += tmpNode->value;
        tmpNode = tmpNode->children[0];
    }
    if (isCompactable) return retVal + tmpNode->value;
    else return "";
};

CompactTreeNode* getCompactTree(TreeNode* node)
{
    CompactTreeNode* newNode;
    string compacted = compact(node);
    if (compacted == "")
    {
        string tmp(1,node->value);
        newNode = new CompactTreeNode(tmp);
        for (int i = 0; i < node->children.size(); ++i)
        {
            newNode->children.push_back(getCompactTree(node->children[i]));
        }
    }
    else
    {
        newNode = new CompactTreeNode(compacted);
    }
    return newNode;
}

CompactSuffixTree::CompactSuffixTree(TreeNode* treeRoot)
{
    mRootNode = getCompactTree(treeRoot);
}

void PrintFromNode(CompactTreeNode* node)
{
    if (node->children.size() == 0)
    {
        cout << "[.";
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
        cout << "[.";
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

void CompactSuffixTree::Print()
{
    PrintFromNode(mRootNode);
}
