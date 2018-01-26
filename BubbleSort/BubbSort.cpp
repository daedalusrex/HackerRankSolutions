#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int a_i = 0; a_i < n; a_i++) {
		cin >> a[a_i];
	}


	int swap_count = 0;
	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n - 1; j++) {
			// Swap adjacent elements if they are in decreasing order
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
				swap_count++;
			}
		}

	}

	cout << "Array is sorted in " << swap_count << " swaps.\n";
	cout << "First Element: " << a[0] << endl;
	cout << "Last Element: " << a[a.size() - 1] << endl;




	return 0;
}