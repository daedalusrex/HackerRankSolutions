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
Sample Input

3
{[()]}
{[(])}
{{[[(())]]}}
Sample Output

YES
NO
YES
Explanation

The string {[()]} meets both criteria for being a balanced string, so we print YES on a new line.
The string {[(])} is not balanced because the brackets enclosed by the matched pair { and } are not balanced: [(]).
The string {{[[(())]]}} meets both criteria for being a balanced string, so we print YES on a new line.
*/

bool isOpener(char a_in) {
    return (a_in == '(' || a_in == '{' || a_in == '[');
}

bool isCloser(char a_in) {
    return (a_in == ')' || a_in == '}' || a_in == ']');
}

bool matchesOpener(char opener, char closer)
{
    switch (opener)
    {
    case '(':
        return closer == ')';
    case '{':
        return closer == '}';
    case '[':
        return closer == ']';
    default:
        break;
    }
    return false;
}

// Complete the isBalanced function below.
string isBalanced(string s) {

    stack<char> sequence; 

    if (isCloser(s[0]))
        return "NO";

    for (int i = 0; i < s.size(); i++)
    {
        if (isOpener(s[i]))
            sequence.push(s[i]);
        else if (isCloser(s[i]))
        {
            if (sequence.empty())
                return "NO";
            else if (matchesOpener(sequence.top(), s[i]))
                sequence.pop();
            else
                return "NO";
        }
    }

    if (sequence.size() != 0)
        return "NO";

    return "YES";
}

int main()
{
    ofstream fout("BalancedBrakets.txt");
    ifstream fin("BracketsTestInput.txt");

    int t;
    fin >> t;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(fin, s);

        string result = isBalanced(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
