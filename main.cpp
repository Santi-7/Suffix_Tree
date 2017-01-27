/* ---------------------------------------------------------------------------
** main.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <compactSuffixTree.hpp>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std::experimental;

tuple<long int, CompactSuffixTree*> timeConstruction(string& parameter, Constructor strategy)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    CompactSuffixTree* tmp = new CompactSuffixTree(parameter, strategy);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    return make_tuple(duration_cast<microseconds>(t2-t1).count(), tmp);
}

tuple<long int, string> timeLongestSubstring(const CompactSuffixTree& tree)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    string retVal = tree.GetLongestRepeatedSubstring();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    return make_tuple(duration_cast<microseconds>(t2-t1).count(), retVal);
}

tuple<long int, vector<string_view>> timeMaximalRepetitions(const CompactSuffixTree& tree)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    vector<string_view> retVal = tree.GetMaximalRepetitions();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    return make_tuple(duration_cast<microseconds>(t2-t1).count(), retVal);
}

/**
 * Prints the usage of the program.
 */
void PrintUsage()
{
    cout << "Usage: " << endl;
}

int main(int argc, char *argv[])
{
    // Wrong number of parameters.
    if (argc == 1)
    {
        PrintUsage();
        return 1;
    }

    // Read parameters.
    bool getLongest = false;
    bool getMaximals = false;
    bool time = false;
    bool print = false;
    Constructor strategy = NLOGN;
    for (int i = 1; i < argc; i++)
    {
        string tmpArg = string(argv[i]);
        if (tmpArg == "-l") getLongest = true;
        else if (tmpArg == "-m") getMaximals = true;
        else if (tmpArg == "--time") time = true;
        else if (tmpArg == "--print") print = true;
        else if (tmpArg == "--n2") strategy = N2;
        else if (tmpArg == "--nlogn") ;
        else
        {
            PrintUsage();
            return 1;
        }
    }

    // Input string.
    string input;
    getline(cin, input);

    // Execute the query vs the input string.
    if (time)
    {
        auto result = timeConstruction(input, strategy);
        CompactSuffixTree* tree(get<1>(result));
        long int treeBuildTime = get<0>(result);
        long int longestSubstrTime = 0L;
        long int maximalsTime = 0L;
        if (getLongest)
        {
            auto longest = timeLongestSubstring(*tree);
            longestSubstrTime = get<0>(longest);
        }
        if (getMaximals)
        {
            auto maximals = timeMaximalRepetitions(*tree);
            maximalsTime = get<0>(maximals);
        }
        cout << treeBuildTime << ' ' << longestSubstrTime << ' ' << maximalsTime << endl;
        delete tree;
    }
    else
    {
        CompactSuffixTree tree (input, strategy);
        if (getLongest)
        {
            cout << "The longest substring is: " << tree.GetLongestRepeatedSubstring() << endl;
        }
        if (getMaximals)
        {
            cout << "The maximals are: " << endl ;
            vector<string_view> maximals = tree.GetMaximalRepetitions();
            if (maximals.size() != 0)
            {
                for (int i = 0; i < maximals.size()-1; ++i)
                {
                    cout << maximals[i] << ", ";
                }
                cout << maximals.back() << endl;
            }
        }
        if (print)
        {
            tree.Print();
        }
    }
}