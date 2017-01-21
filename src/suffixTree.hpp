/* ---------------------------------------------------------------------------
** suffixTree.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef SUFFIX_TREE_SUFFIXTREE_HPP
#define SUFFIX_TREE_SUFFIXTREE_HPP

#include <string>
#include <vector>

struct TreeNode
{
    // An edge is a char and a pointer to another node.
    std::vector<std::pair<char, TreeNode*>> edges;

    /**
     * @param edge to be added to this node.
     * @return the node connected to this node by the new edge added.
     */
    TreeNode* InsertEdge(const char edge)
    {
        TreeNode* connectedNode = new TreeNode;
        edges.push_back(std::make_pair(edge, connectedNode));
        return edges[edges.size() - 1].second;
    }

    /**
     * @param edge value to look for.
     * @param node This parameter will be updated to the node of the tree following
     *  by the desired edge, if it exists.
     * @return True if the edge with the desired value exists, false otherwise.
     */
    bool HasEdge(const char edge, TreeNode* &node)
    {
        // Check all the edges.
        for (const auto& currentEdge : edges)
        {
            // The edge value is the desired.
            if (currentEdge.first == edge)
            {
                node = currentEdge.second;
                return true;
            }
        }
        // No edge
        return false;
    }
};

class SuffixTree
{

public:

    /**
     * TODO: Add doc.
     * @param str
     * @return
     */
    SuffixTree(const std::string &str);

private:

    /** Root node of the suffix tree. */
    TreeNode* mRootNode;

    /**
     * @param str String to look for its maximum prefix.
     * @return the node and path degree of the maximum shared prefix with [str].
     */
    std::pair<unsigned int, TreeNode*> GetPathDegree(const std::string &str) const;
};

#endif // SUFFIX_TREE_SUFFIXTREE_HPP