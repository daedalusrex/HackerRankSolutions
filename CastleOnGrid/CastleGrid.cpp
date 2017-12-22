#include <queue>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

static int gridsize = 0;

bool CellAllowed(vector<string> &grid, vector<vector<int>> &steps, pair<int, int> cell, int newstep)
{
	if (cell.first >= 0 && cell.first < gridsize && cell.second >= 0 && cell.second < gridsize)
	{
		char test = grid[cell.first].at(cell.second);
		if (test == '.' && (steps[cell.first][cell.second] == 0 || steps[cell.first][cell.second] >= newstep ))
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
	//&& allsteps[goalX][goalY] == 0
	while (!search.empty() )
	{

		pair<int, int> cell = search.front();
		search.pop();

		int steps = allsteps[cell.first][cell.second] + 1;

		//misread, should add all neighbors in a line, like a rook
		vector<pair<int, int>> neighbors;

		int move = 1;

		//Look to the North
		while (CellAllowed(grid, allsteps, make_pair(cell.first - move, cell.second),steps))
		{	neighbors.push_back(make_pair(cell.first - move, cell.second));
			move++;
		}
		move = 1;

		//Look to the  South
		while (CellAllowed(grid, allsteps, make_pair(cell.first + move, cell.second), steps))
		{
			neighbors.push_back(make_pair(cell.first + move, cell.second));
			move++;
		}
		move = 1;

		//Look to the East
		while (CellAllowed(grid, allsteps, make_pair(cell.first, cell.second - move), steps))
		{
			neighbors.push_back(make_pair(cell.first, cell.second - move));
			move++;
		}
		move = 1;

		//Look to the West
		while (CellAllowed(grid, allsteps, make_pair(cell.first, cell.second + move), steps))
		{
			neighbors.push_back(make_pair(cell.first, cell.second + move));
			move++;
		}
		
		

		
		for (vector<pair<int, int>>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
			if (CellAllowed(grid, allsteps, *it, steps))
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
