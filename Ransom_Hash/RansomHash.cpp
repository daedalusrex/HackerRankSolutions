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

bool ransom_note(vector<string> magazine, vector<string> ransom) {
	map<string, int> mag_words;
	map<string, int> rans_dict;
	
	for (auto mag : magazine)
	{
		if (mag_words.count(mag))
			mag_words[mag]++;
		else
			mag_words.insert(make_pair(mag, 1));

	}
		
	for (auto ran : ransom)
	{
		if (rans_dict.count(ran))
			rans_dict[ran]++;
		else
			rans_dict.insert(make_pair(ran, 1));

	}

	for (auto itran : rans_dict)
		if (!mag_words.count(itran.first) || mag_words[itran.first] < itran.second)
			return false;

	return true;
}

int main() {
	int m;
	int n;
	cin >> m >> n;
	vector<string> magazine(m);
	for (int magazine_i = 0; magazine_i < m; magazine_i++) {
		cin >> magazine[magazine_i];
	}
	vector<string> ransom(n);
	for (int ransom_i = 0; ransom_i < n; ransom_i++) {
		cin >> ransom[ransom_i];
	}
	if (ransom_note(magazine, ransom))
		cout << "Yes\n";
	else
		cout << "No\n";
	return 0;
}
