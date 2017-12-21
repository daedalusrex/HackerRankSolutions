#include <bits/stdc++.h>
#include <queue>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

static int gridsize = 0;

bool CellAllowed(vector<string> &grid, vector<vector<int>> &steps, pair<int, int> cell)
{
	if (cell.first >= 0 && cell.first < gridsize && cell.second >= 0 && cell.second < gridsize)
	{
		char test = grid[cell.first].at(cell.second);
		if (test == '.' && steps[cell.first][cell.second] == 0)
			return true;
	}
	return false;
}

int minimumMoves(vector <string> grid, int startX, int startY, int goalX, int goalY) {

	//Clearly a BFS 
	queue<pair<int, int>> search;
	search.push(make_pair(startX, startY));

	//create new grid to keep of step counts
	vector<vector<int>> allsteps(gridsize, vector<int>(gridsize, 0));



	//plan is to rewrite each cell, with step value, stop and return when you get to goal
	while (!search.empty() && allsteps[goalX][goalY] == 0)
	{

		pair<int, int> cell = search.front();
		search.pop();

		int steps = allsteps[cell.first][cell.second] + 1;


		vector<pair<int, int>> neighbors;
		neighbors.push_back(make_pair(cell.first - 1, cell.second));
		neighbors.push_back(make_pair(cell.first + 1, cell.second));
		neighbors.push_back(make_pair(cell.first, cell.second - 1));
		neighbors.push_back(make_pair(cell.first, cell.second + 1));

		for (vector<pair<int, int>>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
			if (CellAllowed(grid, allsteps, *it))
			{
				search.push(make_pair(it->first, it->second));
				allsteps[it->first][it->second] = steps;
				//cout << "Cell(x,y) " << it->first << " " << it->second << " step" << allsteps[it->first][it->second] << endl;
			}
		}

	}

	return allsteps[goalX][goalY];

}

int main() {
	int n;
	cin >> n;
	gridsize = n;
	vector<string> grid(n);
	for (int grid_i = 0; grid_i < n; grid_i++) {
		cin >> grid[grid_i];
	}
	int startX;
	int startY;
	int goalX;
	int goalY;
	cin >> startX >> startY >> goalX >> goalY;

	int result = minimumMoves(grid, startX, startY, goalX, goalY);

	cout << result << endl;
	return 0;
}
