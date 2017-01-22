/* ---------------------------------------------------------------------------
** main.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <suffixTree.hpp>
#include <compactSuffixTree.hpp>

int main(int argc, char *argv[])
{
    SuffixTree suffixTree("banana");

    CompactSuffixTree compact(suffixTree.mRootNode);
    compact.Print();
}