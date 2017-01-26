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

template <class F, typename P>
tuple<long int, F> timeConstruction(P parameter)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    F tmp(parameter);
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

/*tuple<long int, vector<string>> timeMaximalRepetitions(const CompactSuffixTree& tree)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //vector<string> retVal = tree.GetMaximalRepetitions();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    return make_tuple(duration_cast<microseconds>(t2-t1).count(), retVal);
}*/

void PrintUsage()
{
    cout << "Usage: " << endl;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        PrintUsage();
        return 1;
    }
    bool getLongest = false;
    bool getMaximals = false;
    bool time = false;
    bool print = false;
    for (int i = 1; i < argc; i++)
    {
        string tmpArg = string(argv[i]);
        if (tmpArg == "-l") getLongest = true;
        else if (tmpArg == "-m") getMaximals = true;
        else if(tmpArg == "--time") time = true;
        else if(tmpArg == "--print") print = true;
        else
        {
            PrintUsage();
            return 1;
        }
    }

    string input;
    getline(cin, input);
    if (time)
    {
        auto result = timeConstruction<CompactSuffixTree>(input);
        CompactSuffixTree tree(get<1>(result));
        long int treeBuildTime = get<0>(result);
        long int longestSubstrTime = 0L;
        long int maximalsTime = 0L;
        if (getLongest)
        {
            auto longest = timeLongestSubstring(tree);
            longestSubstrTime = get<0>(longest);
        }
        if (getMaximals)
        {

        }
        if (print)
        {
            tree.Print();
            cout << endl;
        }
        cout << treeBuildTime << ' ' << longestSubstrTime << ' ' << maximalsTime << endl;
    }
    else
    {
        CompactSuffixTree tree (input, false);
        if (getLongest)
        {
            auto longest = timeLongestSubstring(tree);
            cout << "The longest substring is: " << get<1>(longest) << endl;
        }
        if (getMaximals)
        {
            cout << "The maximals are: " << endl ;
        }
        if (print)
        {
            tree.Print();
            cout << endl;
        }
    }
}