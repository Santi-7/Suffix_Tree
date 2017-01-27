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

CompactSuffixTree::CompactSuffixTree(const std::string& str, Constructor constructor)
{
    mStoredString = '$' + str + '$';
    if (constructor == NLOGN)
    {
        mRootNode = new CompactTreeNode(-1,-1, 0);
        for (int i = 1; i < mStoredString.size()-1; ++i)
        {
            Insert(mRootNode, i, i);
        }
    }
    else if (constructor == N2)
    {
        SuffixTree baseTree(mStoredString);
        mRootNode = GetCompactTree(baseTree.GetRoot(), 0);
    }
}

CompactSuffixTree::CompactSuffixTree(CompactTreeNode* &rootNode)
: mRootNode(rootNode)
{}

CompactTreeNode* CompactSuffixTree::GetCompactTree(TreeNode* node, int depth)
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
    newNode = new CompactTreeNode(begin, end, node->pathFirstChar, node->isLeftDiverse);
    if (node->children.size() > 0 and node->isLeftDiverse and depth != 0)
    {
        mMaximalNodes.push_back(newNode);
    }
    for (int i = 0; i < node->children.size(); ++i)
    {
        newNode->children.push_back(GetCompactTree(node->children[i], depth + (end - begin) + 1));
    }
    // Check if this inner node is deeper than the last recorded and if it is update the variable.
    if (newNode->children.size() != 0) CheckInnerNode(newNode, depth + (end - begin));
    return newNode;
}

string CompactSuffixTree::GetLongestRepeatedSubstring() const
{
    if (get<0>(mLongestSubstring) != nullptr)
    {
        unsigned long a = (unsigned long) get<0>(mLongestSubstring)->originalPathFirstChar;
        unsigned long b = (unsigned long) get<0>(mLongestSubstring)->end;
        return mStoredString.substr(a, b-a+1);
    }
    else return "";
}

void CompactSuffixTree::Print()
{
    cout << "\\begin{forest}\n";
    PrintFromNode(mRootNode);
    cout << "\n\\end{forest}\n";
}

void CompactSuffixTree::PrintFromNode(CompactTreeNode* node)
{
    if (node->children.size() == 0)
    {
        cout << "[";
        if (mStoredString[node->originalPathFirstChar-1] == '$') cout << "\\$";
        else cout << mStoredString[node->originalPathFirstChar-1];
        if (node->isLeftDiverse) cout << '+';
        else cout << '-';
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
        if (mStoredString[node->originalPathFirstChar-1] == '$') cout << "\\$";
        else cout << mStoredString[node->originalPathFirstChar-1];
        if (node->isLeftDiverse) cout << '+';
        else cout << '-';
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
        CompactTreeNode* newNode = new CompactTreeNode(from, (int)mStoredString.size() - 1, pathFirstChar);
        root->children.push_back(newNode);
    }
    else if (insertingBefore->begin+fitting > insertingBefore->end)
    {
        if (!insertingBefore->isLeftDiverse and
                mStoredString[insertingBefore->originalPathFirstChar - 1] != mStoredString[pathFirstChar-1])
        {
            insertingBefore->isLeftDiverse = true;
            mMaximalNodes.push_back(insertingBefore);
        }
        Insert(insertingBefore, from + fitting, pathFirstChar);
    }
    else
    {
        // The new node shares part of the inner node [insertingBefore]
        CompactTreeNode* newNode =
                new CompactTreeNode(from, from + fitting - 1, pathFirstChar,
                        insertingBefore->isLeftDiverse or
                                mStoredString[pathFirstChar-1] != mStoredString[insertingBefore->originalPathFirstChar - 1]);
        // If the new node is left diverse it represents a maximal repetition.
        if (newNode->isLeftDiverse) mMaximalNodes.push_back(newNode);
        CheckInnerNode(newNode, from + fitting - pathFirstChar);
        // Set the old inner node as a child of this new node and not of the root.
        insertingBefore->begin += fitting;
        root->children[childIndex] = newNode;
        newNode->children.push_back(insertingBefore);
        Insert(newNode, from + fitting, pathFirstChar);
    }
}

std::vector<std::string> CompactSuffixTree::GetMaximalRepetitions() const
{
    vector<string> retVal;
    for (const CompactTreeNode* node : mMaximalNodes)
    {
        unsigned long a = (unsigned long) node->originalPathFirstChar;
        unsigned long b = (unsigned long) node->end;
        retVal.push_back(mStoredString.substr(a, b-a+1));
    }
    // Sorted to be able to compare the results from the NLOGN and N2 constructors.
    sort(retVal.begin(), retVal.end());
    return retVal;
}

CompactSuffixTree::~CompactSuffixTree()
{
    delete mRootNode;
}

void CompactSuffixTree::CheckInnerNode(CompactTreeNode *innerNode, int depth)
{
    if (depth > get<1>(mLongestSubstring))
    {
        mLongestSubstring = make_tuple(innerNode, depth);
    }
}
