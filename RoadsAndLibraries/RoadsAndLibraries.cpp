#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

long roadsAndLibraries(int n, long c_lib, long c_road, vector < vector<int> > cities) {
	
	if (c_lib < c_road)
		return c_lib * n;
	
	vector<vector<int>>  roadmap(n, vector<int>());
	vector<bool> visited(n, false);
		
	//build adjacency lists, or mat
	for (int i = 0; i < cities.size(); i++)
	{
		roadmap[cities[i][0]-1].push_back(cities[i][1]-1);
		roadmap[cities[i][1]-1].push_back(cities[i][0]-1);
	}


	vector<vector<int>> disj_sets;

	//Seach for disjoint sets
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i]) continue;

		visited[i] = true;
		queue<int> search;
		vector<int> new_set;
		search.push(i);
		

		while (!search.empty())
		{
			new_set.push_back(search.front());
			for (auto it : roadmap[search.front()])
			{
				if (visited[it]) continue;
				
				search.push(it);
				visited[it] = true;
				
			}
			search.pop();
		}
		disj_sets.push_back(new_set);
	}

	long cost = 0;
	//build 1 library in every disj set
	cost += disj_sets.size() * c_lib;
	//build just enough roads to connect all cities
	for (auto it : disj_sets)
		cost += c_road * (it.size() - 1);

	return cost;
}

int main() {
	int q;
	cin >> q;
	for (int a0 = 0; a0 < q; a0++) {
		int n;
		int m;
		int c_lib;
		int c_road;
		cin >> n >> m >> c_lib >> c_road;
		vector< vector<int> > cities(m, vector<int>(2));
		for (int cities_i = 0; cities_i < m; cities_i++) {
			for (int cities_j = 0; cities_j < 2; cities_j++) {
				cin >> cities[cities_i][cities_j];
			}
		}
		long result = roadsAndLibraries(n, c_lib, c_road, cities);
		cout << result << endl;
	}
	return 0;
}