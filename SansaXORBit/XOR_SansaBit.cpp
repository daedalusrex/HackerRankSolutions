#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int sansaXor(vector <int> arr) {
	// Complete this function
	//Need to xor each element and each sub array element
	// Luckily, xor is communtable and order does not matter
	//So should be able to keep a running sum and xor all things to that
	

	int xor_collect = arr[0];
	for (int i = 1; i < arr.size(); i++)
	{
		xor_collect ^= arr[i];
	}

	int xor_total = 0;

	for (int groupsize = 1; groupsize <= arr.size(); groupsize++)
	{
		int group_xor = 0;
		

		for (int ops = 0; ops < groupsize; ops++)
		{
			

			group_xor = arr[ops] ^ arr[ops + 1]



		}
	}
	

	return xor_total;
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
		int result = sansaXor(arr);
		cout << result << endl;
	}
	return 0;
}
