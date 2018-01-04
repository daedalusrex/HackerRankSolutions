// TheCoinChangeProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

long getWays(long n, vector < long > c) {
	// Complete this function
	vector<vector<long>> All_ways(n+1, vector<long>(c.size(),0));

	for (int k = 0; k < c.size(); k++)
		All_ways[0][k] = 1;

	//Iteratively build up from n = 0, and c of zero to all the way
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < c.size(); j++)
		{
			//each number of ways, is equal to the number of ways I can make it with less coins, 
			//plus number of ways I can make i-Coin Value
			// plus 1 if I can make it with this coin value

			long sum = 0;
			if (j >= 1)
				sum += All_ways[i][j - 1];

			//less one of current coin
			int targ_n = i - c[j];

			if (targ_n >= 0)
				sum += All_ways[targ_n][j];

			//Hmm, but if I exactly hit zero, shouldn't I add one additional way?
			//if(targ_n == 0)
			//  sum += 1;
			All_ways[i][j] = sum;
		}


	}

	return  All_ways[n][c.size()-1];

}

int main() {
	int n;
	int m;
	cin >> n >> m;
	vector<long> c(m);
	for (int c_i = 0; c_i < m; c_i++) {
		cin >> c[c_i];
	}
	// Print the number of ways of making change for 'n' units using coins having the values given by 'c'
	long ways = getWays(n, c);

	cout << ways << endl;
	return 0;
}

