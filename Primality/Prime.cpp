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


int main() {
	int p;
	cin >> p;

	
	for (int a0 = 0; a0 < p; a0++) {
		int n;
		cin >> n;

		//sqrt is upper limit
		double sqroot = sqrt(n);

		int counter = 2;
		while (counter <= sqroot)
		{
			if (n % counter == 0)
			{
				cout << "Not prime" << endl;
				break;
			}
			
			counter++;
		}
		
		if (!(n %counter == 0))
			cout << "Prime" << endl;

	}
	return 0;
}
