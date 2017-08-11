#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
void partition(vector <int>  ar) {
	// Enter code for partitioning and printing here. 

	int part = ar[0];
	int front = 0;
	

	vector<int> lesspart;
	vector<int> equalpart;
	vector<int> greaterpart;

	while (front < ar.size())
	{
		if (ar[front] < part)
			lesspart.push_back(ar[front]);

		if (ar[front] == part)
			equalpart.push_back(ar[front]);

		if (ar[front] > part)
			greaterpart.push_back(ar[front]);

		front++;
	}


	for (vector<int>::iterator it = lesspart.begin(); it != lesspart.end(); ++it)
		cout << *it << " ";

	for (vector<int>::iterator it = equalpart.begin(); it != equalpart.end(); ++it)
		cout << *it << " ";

	for (vector<int>::iterator it = greaterpart.begin(); it != greaterpart.end(); ++it)
		cout << *it << " ";
}

int main(void) {
	vector <int>  _ar;
	int _ar_size;
	cin >> _ar_size;

	for (int _ar_i = 0; _ar_i<_ar_size; _ar_i++) {
		int _ar_tmp;
		cin >> _ar_tmp;
		_ar.push_back(_ar_tmp);
	}

	partition(_ar);


	cin >> _ar_size;
	return 0;
}
