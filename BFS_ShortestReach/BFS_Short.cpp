#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class Graph {
private:
	vector<vector<int>> adj_lists;

public:
	Graph(int n) : adj_lists(n) {

	}

	void add_edge(int u, int v) {
		adj_lists[u].push_back(v);
		adj_lists[v].push_back(u);
	}

	vector<int> shortest_reach(int start) {
		vector<int> calced_dists(adj_lists.size(), 0);

		queue<int> parents;
		parents.push(start);

		while (!parents.empty())
		{
			queue<int> children;
			
			//for every node at this distance, find their children, and calc their distance
			while (!parents.empty())
			{
				int padre = parents.front();
				parents.pop();

				//iterate through all adjacent nodes to this parent
				for (vector<int>::iterator it = adj_lists[padre].begin(); it != adj_lists[padre].end(); it++)
				{
					//If we haven't seen this node before, (cycle detection)
					if (calced_dists[*it] == 0 && *it != start)
					{
						//This nodes distance is 1 step larger, and add it to the next layer of children
						calced_dists[*it] = calced_dists[padre] + 6;
						children.push(*it);
					}
				}

				
			}

			
			//As with all things, the next generation must take the place of the first
			parents = children;

		}
			

		//Check for any 0's and !S-node they are disconnected therefore -1
		//iterate through and erase s
		//calced_dists.erase(calced_dists.begin() + start);

		for (vector<int>::iterator it = calced_dists.begin(); it != calced_dists.end(); ++it)
		{
			if (*it == 0)
				*it = -1;

		}


		return calced_dists;
	}

};

int main() {
	int queries;
	cin >> queries;

	for (int t = 0; t < queries; t++) {

		int n, m;
		cin >> n;
		// Create a graph of size n where each edge weight is 6: 
		Graph graph(n);
		cin >> m;
		// read and set edges
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--, v--;
			// add each edge to the graph
			graph.add_edge(u, v);
		}
		int startId;
		cin >> startId;
		startId--;
		// Find shortest reach from node s
		vector<int> distances = graph.shortest_reach(startId);

		for (int i = 0; i < distances.size(); i++) {
			if (i != startId) {
				cout << distances[i] << " ";
			}
		}
		cout << endl;
	}

	return 0;
}
 