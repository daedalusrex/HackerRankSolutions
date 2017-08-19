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



vector<int> array_left_rotation(vector<int> a, int n, int k) {

	//Need to do a mod of k and n since, this rotation thing rolls over, and then just do from index 1 to index 2, O(n) solution



	int shifts = k % n;



	vector<int> shifted(n, 0);



	int a_index = shifts;

	for (vector<int>::iterator it = shifted.begin(); it != shifted.end(); it++) {

		//Move along the final vector, with an index, but watch for end of original array



		if (a_index == a.size())

			a_index = 0;



		*it = a[a_index];

		a_index++;





	}





	return shifted;



}



int main() {

	int n;

	int k;

	cin >> n >> k;

	vector<int> a(n);

	for (int a_i = 0; a_i < n; a_i++) {

		cin >> a[a_i];

	}

	vector<int> output = array_left_rotation(a, n, k);

	for (int i = 0; i < n; i++)

		cout << output[i] << " ";

	cout << endl;

	return 0;

}