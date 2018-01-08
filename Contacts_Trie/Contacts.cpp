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

//trie data structure

class t_node
{
public:
	t_node(char c) : data(c),is_word(false), num_prefix(0) {};
	t_node() :data('\0'), is_word(false), num_prefix(0) {};

	char data;
	//could do a vector of children? , at most 26 letters
	//could do some cool ascii indexing stuff
	//root might neeed to be a list of 26 nodes?

	//get's incremented every insert
	int num_prefix;

	bool is_word;
	vector<t_node*> children;
	//t_node * childs[26];



};



int main() {
	int n;
	//Init trie
	t_node root();

	cin >> n;
	for (int a0 = 0; a0 < n; a0++) {
		string op;
		string contact;
		cin >> op >> contact;

		if(op == "add")
			//do addition

		if(op == "find")
			//do find

	}
	return 0;
}
