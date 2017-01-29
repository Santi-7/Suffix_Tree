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
 * Prints an usage message on how to use this program.
 */
void PrintUsage()
{
    cout << "Usage: ./Repeticiones [OPTION]... \n"
            "\tWhen the command starts type the string you want to build the tree and get information about.\n"
            "\tOptionally you can just redirect a file to stdin or use a pipe.\n"
            "\n"
            "Options:\n"
            "\t-l : get the longest repeated substring in the input string.\n"
            "\t-m : get all the maximal repetitions in the input string.\n"
            "\t--nlogn : default algorithm, builds the compact suffix tree directly from the input string.\n"
            "\t--n2 : builds the compact suffix tree from an auxiliary extended tree."
            "\t--print : print the suffix tree in a LaTeX-friendly format.\n"
            "\t--time : override behaviour to get the time it takes to run each of the selected options of the program.\n"
            "\tThe format for the --time option is:\n"
            "\t\t tree_build_time longest_substring_time maximal_repetitions_time\n"
            "\tKeep in mind that time will always be measured for the tree build but not so for the other options, those have to be manually selected.\n"
            "\tAll time is measured in microseconds.\n";
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