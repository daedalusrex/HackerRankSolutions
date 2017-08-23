//#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;


//Use size of string as first choice, then if equal go digit by digit
bool big_lessthan(string &left, string &right)
{
	if (left.size() < right.size()) return true;

	if (left.size() > right.size()) return false;

	int digit = 0;

	while (left[digit] == right[digit] && digit < left.size())
		digit++;

	if (left[digit] < right[digit])
		return true;

	return false;

}



int main() {
	int n;
	cin >> n;
	vector<string> unsorted(n);
	for (int unsorted_i = 0; unsorted_i < n; unsorted_i++) {
		cin >> unsorted[unsorted_i];
	}
	

	//rely on the STD sort algorithm and pass in predicate
	sort(unsorted.begin(), unsorted.end(), big_lessthan);

	for (vector<string>::iterator it = unsorted.begin(); it != unsorted.end(); it++)
		cout << *it << endl;

	return 0;
}