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
//#define INT_MAX       2147483647    // maximum (signed) int value

struct edge {
	int dist;
	int node_A;
	int node_B;

	edge() : dist(-1), node_A(-1), node_B(-1) {}
	edge(int distance, int nodeA, int nodeB) : dist(distance), node_A(nodeA), node_B(nodeB) {}
};

//OO Concept, and then can build my special adjaceny list
class node {
public:
	int index; //not sure of this one (position of label)
	int s_dist;

	vector<int> nodes;
	vector<edge*> edges;

	node() : index(0), s_dist(INT_MAX), nodes(), edges() {}
};

//concern regarding the way I'm using memory and if priority queue would update if node changes
struct comp_s_cost
{
	bool operator()(const node* left, const node* right)
	{
		return left->s_dist > right->s_dist;
	}
};

void calc_shortest_paths(int start,vector<node> &adj_list)
{
	adj_list[start].s_dist = 0;
	int size = adj_list.size();
	vector<bool> visited(size, false);
	priority_queue<node*, vector<node*>, comp_s_cost> search;
	search.push(&adj_list[start]);
	
	while(!search.empty())
	{
		node *current = search.top();
		search.pop();
		if (visited[current->index]) continue;

		visited[current->index] = true;

		//for (edge* it : adj_list[current->index].edges)
		for(vector<edge*>::iterator it = adj_list[current->index].edges.begin(); it != adj_list[current->index].edges.end(); it++)
		{
			//have an edge, and its dist
			int far_node = (*it)->node_B;
			if ((*it)->node_B == current->index)
				far_node = (*it)->node_A;


			

			//if(edge dist + curret s_dist < far_node_s_dist
			int newpath_dist = (*it)->dist + current->s_dist;
			if (newpath_dist < adj_list[far_node].s_dist)
			{
				//far node s_dist = edge dist + current s_dist
				adj_list[far_node].s_dist = newpath_dist;
			}

			//if(not visited add it), pretty sure this is wrong
			if (!visited[far_node])
				search.push(&adj_list[far_node]);
		}
	}
	
	//print a single line consisting space separated integers denoting the shortest distance 
	//from starting position in increasing order of their labels. (1-N)
	//For unreachable nodes (INT MAX), print -1
	//for auto it adj_list cout it.s_dist
	//for (auto it : adj_list)
	for(vector<node>::iterator it = adj_list.begin(); it != adj_list.end(); it++)
	{
		if ((*it).index == start) continue;

		int nextout = (*it).s_dist;
		if (nextout == INT_MAX)
			nextout = -1;

		cout << nextout << " ";

	}
	cout << endl;
}

int not_main() {
	int t;
	cin >> t;
	for (int a0 = 0; a0 < t; a0++) {
		int n;
		int m;
		cin >> n >> m;

		vector<node> adj_list(n);

		for (int i = 0; i < n; i++)
			adj_list[i].index = i;


		for (int a1 = 0; a1 < m; a1++) {
			int x;
			int y;
			int r;
			cin >> x >> y >> r;

			//fill in graph, first make zero based
			x--;
			y--;
			edge *new_connection = new edge(r, x, y);
			adj_list[x].nodes.push_back(y);
			adj_list[x].edges.push_back(new_connection);
			adj_list[y].nodes.push_back(x);
			adj_list[y].edges.push_back(new_connection);


		}
		int s;
		cin >> s;

		calc_shortest_paths(s - 1, adj_list);

		//clean up dynamic pointers
	}

	return 0;
}

			/* The next like 40 lines I added to attempt to optimize the map. 
			I do not like it because it is convulted and confusing
			I think I will attempt to restart, and recreate all data structs
			*/
			
			/*			
			bool edge_already_exists = false;

			//scan and prune nodes
			for (vector<edge*>::iterator it = adj_list[x].edges.begin(); it != adj_list[x].edges.end(); it++)
			{
				//This edge already exists
				if ((x == (*it)->node_A && y == (*it)->node_B) ||
					(y == (*it)->node_A && x == (*it)->node_B))
				{
					edge_already_exists = true;
					//new edge is shorter than one already present
					if (r < (*it)->dist)
					{
						//delete old edge, insert new edge, do not push back new node
						for (vector<edge*>::iterator yit = adj_list[y].edges.begin(); yit != adj_list[y].edges.end(); yit++)
						{
							if (*yit == *it)
								yit = adj_list[y].edges.erase(yit);
						}
						it = adj_list[x].edges.erase(it);
					
					
						adj_list[x].edges.push_back(new_connection);
						adj_list[y].edges.push_back(new_connection);

					}
					else
					{
						//kill new edge do nothing

					}

					break;
				}




			}

			if (!edge_already_exists)
			{
				adj_list[x].nodes.push_back(y);
				adj_list[x].edges.push_back(new_connection);
				adj_list[y].nodes.push_back(x);
				adj_list[y].edges.push_back(new_connection);
			}
			

		}
		*/