/* ---------------------------------------------------------------------------
** main.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <compactSuffixTree.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
    CompactSuffixTree compact("HOLAPITHOLA");
    compact.Print();

    std::cout << std::endl << compact.GetLongestRepeatedSubstring();
}