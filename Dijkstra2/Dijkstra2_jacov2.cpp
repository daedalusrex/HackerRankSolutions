#include <map>
#include <queue>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

struct comp_s_dist {

	bool operator()(const pair<int, int> &left, const pair<int, int> &right)
	{
		//to make a min heap, need to return true if left is greater than right
		return left.first > right.first;
	}

};


void calc_shortest_paths(int start, int nodes, map<int,int> adj_list[]) {
	//array of distance to start (init with intmax)
	vector<int> s_dist(nodes, INT_MAX);
	
	//array of visited (init all false)
	vector<bool> visited(nodes, false);
	
	//Mark start node with correct distance
	s_dist[start] = 0;
	
	//heap of distance from s to node index, comparator above
	//push additional s_dist node pair, only if you update s_dist
	//when pop skip if visited
	priority_queue < pair<int, int>, vector<pair<int, int>>, comp_s_dist> search;

	search.push(make_pair(0, start));

	while (!search.empty())
	{
		int current_node = search.top().second;
		search.pop();
		if (visited[current_node]) continue;

		visited[current_node] = true;

		//go through all adjacent nodes, at most n, and skip if already visited
		for (map<int, int>::iterator it = adj_list[current_node].begin(); it != adj_list[current_node].end(); it++)
		{
			int newdist = it->second + s_dist[current_node];
			if (newdist < s_dist[it->first])
			{
				s_dist[it->first] = newdist;

				//update priority queue with new lower distance value map to node
				search.push(make_pair(s_dist[it->first], it->first));

			}
		}
	}

	//print stuff out, iterate through sdist
	for (vector<int>::iterator it = s_dist.begin(); it != s_dist.end(); it++)
	{
		if (it - s_dist.begin() == start) continue;
		int output = *it;
		if (output == INT_MAX) output = -1;
		cout << output << " ";
	}
	cout << endl;

}

int main() {
	int t;
	cin >> t;
	for (int a0 = 0; a0 < t; a0++) {
		int n;
		int m;
		cin >> n >> m;

		//adjacency list
		//an array[n], of map[node_index] = edge weight
		map<int, int> *adj_list = new map<int, int>[n];
		

		for (int a1 = 0; a1 < m; a1++) {
			int x, y, r;
			cin >> x >> y >> r;

			//fill in graph, first make zero based
			x--;
			y--;

			//adjlist fill, optimize for edge length, only insert if less
			//if edge doesn't exist, or is less, than insert/modify new length 
			//(undirected symetric, so only check one)
			if (adj_list[x].count(y) == 0 || adj_list[x][y] > r)
			{
				adj_list[x][y] = r;
				adj_list[y][x] = r;
			}

		}
		int s;
		cin >> s;
		calc_shortest_paths(s - 1, n, adj_list);

		//clean up dynamic pointers
		delete[] adj_list;
	}
	return 0;
}
