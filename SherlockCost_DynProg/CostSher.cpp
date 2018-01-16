#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;



int cost(vector <int> arr) {
	

	int n = arr.size();
	int high = 0, low = 0;
	for (int i = 1; i < arr.size() - 1; i++)
	{
		int highLowdiff = abs(arr[i - 1] - 1);
		int lowhighdiff = abs(arr[i] - 1);

		int low_nex = max(low, high + highLowdiff);
		int hi_nex = max(high, low + lowhighdiff);

		low = low_nex;
		high = hi_nex;
	}


	return max(high, low);
}

int main() {
	int t;
	cin >> t;
	for (int a0 = 0; a0 < t; a0++) {
		int n;
		cin >> n;
		vector<int> arr(n);
		for (int arr_i = 0; arr_i < n; arr_i++) {
			cin >> arr[arr_i];
		}
		int result = cost(arr);
		cout << result << endl;
	}
	return 0;
}