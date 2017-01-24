/* ---------------------------------------------------------------------------
** main.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <compactSuffixTree.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <typename F, typename P>
void benchmark(F function, P parameter)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    function(parameter);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    long int elapsed = duration_cast<microseconds>(t2-t1).count();
    cout << "The function run in: " << elapsed << " microseconds.\n";
}

template <typename F>
void benchmark(F function)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    function();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    long int elapsed = duration_cast<microseconds>(t2-t1).count();
    cout << "The function run in: " << elapsed << " microseconds.\n";
}

template <class F, typename P>
void benchmark(P parameter)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    F *tmp = new F(parameter);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    long int elapsed = duration_cast<microseconds>(t2-t1).count();
    cout << "The constructor run in: " << elapsed << " microseconds creating object at: " << tmp << " .\n";
}

int main(int argc, char *argv[])
{
    CompactSuffixTree compact("abcdefghijk");
    compact.Print();
    std::cout << std::endl << compact.GetLongestRepeatedSubstring();
}