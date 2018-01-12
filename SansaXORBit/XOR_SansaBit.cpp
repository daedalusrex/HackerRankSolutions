#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int sansaXor(vector <int> arr) {
	//Due to properties of Xor, only care if 
	//there occurs an odd or even number of a particular element
	//xor only odds, as others will be zero
	
	int xor_total = 0, N = arr.size();

	for (int i = 1; i <= N; i++)
	{
		int occurences = i * (N - i + 1);
		if (occurences % 2 != 0)
			xor_total ^= arr[i - 1];
			
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
