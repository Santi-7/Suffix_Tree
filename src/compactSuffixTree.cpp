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
    newNode = new CompactTreeNode(begin, end, parent,0);
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

string CompactSuffixTree::GetLongestRepeatedSubstring() const
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
    cout << endl;
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

CompactSuffixTree::CompactSuffixTree(const std::string& str, bool fast)
{
    mStoredString = '$' + str + '$';
    mRootNode = new CompactTreeNode(-1,-1, nullptr, 0);
    for (int i = 1; i < mStoredString.size()-1; ++i)
    {
        Insert(mRootNode, i, i);
    }
    sort(mDepthInfo.begin(), mDepthInfo.end(),
            [](const InnerNodeDepth& a, const InnerNodeDepth& b ) -> bool{return a.depth > b.depth;});
}

void CompactSuffixTree::Insert(CompactTreeNode* root, const int from, const int pathFirstChar)
{
    CompactTreeNode* insertingBefore = root;
    int fitting = 0; // How many characters are already part of a node in the tree.
    int childIndex = -1;
    for (int i = 0; i < root->children.size(); ++i)
    {
        CompactTreeNode* child = root->children[i];
        if (mStoredString[child->begin] == mStoredString[from])
        {
            childIndex = i;
            insertingBefore = child;
            while (child->begin+fitting <= child->end &&
                    mStoredString[child->begin+fitting] == mStoredString[from+fitting]) fitting++;
            break;
        }
    }

    // The first [fitting] characters in the node [insertingBefore] are the same as the characters in mStoredString[[from]:]
    if (childIndex == -1)
    {
        // The new node is a new child of root
        CompactTreeNode* newNode = new CompactTreeNode(from, (int)mStoredString.size() - 1, root, pathFirstChar);
        root->children.push_back(newNode);
    }
    else if (insertingBefore->begin+fitting > insertingBefore->end)
    {
        if (!insertingBefore->isLeftDiverse and
                mStoredString[insertingBefore->originalPathFirstChar - 1] != mStoredString[pathFirstChar-1])
            insertingBefore->isLeftDiverse = true;
        Insert(insertingBefore, from + fitting, pathFirstChar);
    }
    else
    {
        // The new node shares part of the inner node [insertingBefore]
        CompactTreeNode* newNode =
                new CompactTreeNode(from, from + fitting - 1 , root, pathFirstChar,
                        insertingBefore->isLeftDiverse or
                                mStoredString[pathFirstChar-1] != mStoredString[insertingBefore->originalPathFirstChar - 1]);
        mDepthInfo.emplace_back(newNode, from + fitting - pathFirstChar);
        insertingBefore->begin += fitting;
        insertingBefore->parent = newNode;
        root->children[childIndex] = newNode;
        Insert(newNode, from + fitting, pathFirstChar);
        newNode->children.push_back(insertingBefore);
    }
}

std::vector<std::string> CompactSuffixTree::GetMaximalRepetitions() const
{
    vector<string> retVal;
    for (const InnerNodeDepth& depthInfo : mDepthInfo)
    {
        if (depthInfo.node->isLeftDiverse and depthInfo.node != mRootNode)
        {
            unsigned long a = (unsigned long) depthInfo.node->originalPathFirstChar;
            unsigned long b = (unsigned long) depthInfo.node->end;
            retVal.push_back(mStoredString.substr(a,b-a+1));
        }
    }
    return retVal;
}









































