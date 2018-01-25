#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;


//N is less than 100
#define N_LIMIT 100

//might need to transform to longs
long cube[N_LIMIT][N_LIMIT][N_LIMIT] = { 0 };
int N = 0;
bool cube_valid = true;

void clear_cube()
{
	memset(cube, 0U, sizeof(int) * N_LIMIT * N_LIMIT * N_LIMIT);
}

void update_entry(int x, int y , int z, int W) 
{
	cube_valid = false;

	cube[x][y][z] = W;
}

void refresh_cube() 
{
	//Push the value from each cell, into the 3 dimensions it will be summed, and do so in order
	for (int k = 0; k < N-1; k++)
	{
		for (int j = 0; j < N-1; j++)
		{
			for (int i = 0; i < N-1; i++)
			{
				cube[i+1][j][k] += cube[i][j][k];
				cube[i][j+1][k] += cube[i][j][k];
				cube[i][j][k+1] += cube[i][j][k];
			}
		}
	}
}

long answer_query(int x1, int y1, int z1, int x2, int y2, int z2) 
{	//only update cube before after an entry updated between queries
	if (!cube_valid)
		refresh_cube();

	//Need to use pre-summed coordinates, and subtract smaller boxes
	//figured this out by playing with foam blocks
	return (cube[x2][y2][z2] + cube[x1][y1][z2] + cube[x1][y2][z1] + cube[x2][y1][z1]
		  - cube[x1][y2][z2] - cube[x2][y1][z2] - cube[x2][y2][z1] - cube[x1][y1][z1]);
}


int main() {
	//Handle input
	int T; 
	cin >> T;
	for (int testc = 0; testc < 50; testc++)
	{
		int M;
		cin >> N >> M;
		for (int M_entry = 0; M_entry < M; M_entry++)
		{
			string op;
			cin >> op;
			if (op == "UPDATE")
			{
				int x, y, z, W;
				cin >> x >> y >> z >> W; 
				x--; y--; z--;
				update_entry(x, y, z, W);
			}

			if (op == "QUERY")
			{
				int x1, y1, z1, x2, y2, z2;
				cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
				x1--; y1--; z1--; x2--; y2--; z2--;
				cout << answer_query(x1, y1, z1, x2, y2, z2) << endl;
			}
		}

		clear_cube();
	}

	return 0;
}
