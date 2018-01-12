#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

#define INT_MIN     (-2147483647 - 1) // minimum (signed) int value
#define INT_MAX       2147483647    // maximum (signed) int value

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */

	int N;
	//Gi, Bi
	vector<pair<int, int>> edges;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int Gi, Bi;
		cin >> Gi >> Bi;
		edges.push_back(make_pair(Gi, Bi));

		//need to transfer to adjacency list here
	}

	//adjacency list
	vector<vector<int>> nodes(2*N, vector<int>());

	for (pair<int,int> it : edges)
	{
		//Off by 1 index should be handled here
		nodes[it.first-1].push_back(it.second-1);
		nodes[it.second-1].push_back(it.first-1);
	}

	vector<bool> visited(2 * N, false);
	vector<vector<int>> disj_sets;
	int mini = INT_MAX;
	int maxi = INT_MIN;

	
	for (int i = 0; i < 2 * N; i++)
	{
		if (!visited[i])
		{
			vector<int> new_disj_Set;
			vector<int> search;
			search.push_back(i);
			new_disj_Set.push_back(i);
			visited[i] = true;

			while (!search.empty())
			{
				int current = search.back();
				search.pop_back();


				//add neighbors and mark as visted, and add them to new set
				for (vector<int>::iterator it = nodes[current].begin(); it != nodes[current].end(); it++)
				{
					if (!visited[*it])
					{
						search.push_back(*it);
						new_disj_Set.push_back(*it);
						visited[*it] = true;
					}
					
				}

			}

			if (new_disj_Set.size() > 1)
			{	//running min, max instead of looping through disj_sets
				mini = min(mini, (int)new_disj_Set.size());
				maxi = max(maxi, (int)new_disj_Set.size());
			}

		}
	}

	cout << mini << " " << maxi << endl;
	return 0;
}