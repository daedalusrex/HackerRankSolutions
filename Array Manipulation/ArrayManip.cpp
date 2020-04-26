#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
Function Description

Complete the function arrayManipulation in the editor below. It must return an integer, the maximum value in the resulting array.

arrayManipulation has the following parameters:

n - the number of elements in your array
queries - a two dimensional array of queries where each queries[i] contains three integers, a, b, and k
https://www.hackerrank.com/challenges/crush/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays

Better solution involves only keeping track of the "elevation change" as you climb through the array. 
Then summing all of it gives you the height at any point

*/

vector<string> split_string(string);

// Complete the arrayManipulation function below.
unsigned long arrayManipulation(int n, vector<vector<int>> queries) {

    if (n < 1)
        return 0;

    long maxvalue = 0;
    long* arr = new long[n];
    memset(arr, 0, n*sizeof(long));

    for (int i = 0; i < queries.size(); i++)
    {
        unsigned int start_idx = queries[i][0]-1;
        unsigned int end_idx = queries[i][1]-1;
        long summand = queries[i][2];

        
        arr[start_idx] += summand;
        if (end_idx < (n - 1))
            arr[end_idx + 1] -= summand;
          

    }

    long climber = 0;
    for (int arr_idx = 0; arr_idx < n; arr_idx++)
    {
        climber += arr[arr_idx];
        arr[arr_idx] = climber;

        if (climber > maxvalue)
            maxvalue = climber;

    }
    return maxvalue;

}

int main()
{
    ofstream fout("result.txt");

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    unsigned long result = arrayManipulation(n, queries);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}