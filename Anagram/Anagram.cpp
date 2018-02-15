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

int number_needed(string a, string b) {

	int a_count[26] = { 0 };
	int b_count[26] = { 0 };

	for (char it : a)
		a_count[it - 'a']++;

	for (char it : b)
		b_count[it - 'a']++;

	int deletions = 0;
	for (int i = 0; i < 26; i++)
		deletions += abs(a_count[i] - b_count[i]);

	return deletions;

}

int main() {
	string a;
	cin >> a;
	string b;
	cin >> b;
	cout << number_needed(a, b) << endl;
	return 0;
}