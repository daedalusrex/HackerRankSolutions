#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
using namespace std;


//N is less than 100
#define N_LIMIT 100

//might need to transform to longs
long sum_cube[N_LIMIT][N_LIMIT][N_LIMIT] = { 0 };
long entry_cube[N_LIMIT][N_LIMIT][N_LIMIT] = { 0 };
int N = 0;
bool cube_valid = true;



void clear_cube()
{
	memset(entry_cube, 0U, sizeof(long) * N_LIMIT * N_LIMIT * N_LIMIT);
	cube_valid = false;
}

void update_entry(int x, int y , int z, int W) 
{
	cube_valid = false;

	entry_cube[x][y][z] = W;
}

void refresh_cube() 
{	//this will only work the first time, because afterwards, sums must change
	//might need a second cube
	//Push the value from each cell, into the 3 dimensions it will be summed, and do so in order

	memcpy(sum_cube, entry_cube, sizeof(long) * N_LIMIT * N_LIMIT * N_LIMIT);


	for (int i = 1; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				sum_cube[i][j][k] += sum_cube[i - 1][j][k];

	for (int i = 0; i < N; i++)
		for (int j = 1; j < N; j++)
			for (int k = 0; k < N; k++)
				sum_cube[i][j][k] += sum_cube[i][j - 1][k];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 1; k < N; k++)
				sum_cube[i][j][k] += sum_cube[i][j][k-1];

	cube_valid = true;
}

long answer_query(int x1, int y1, int z1, int x2, int y2, int z2) 
{	//only update cube before after an entry updated between queries
	if (!cube_valid)
		refresh_cube();

	//Need to use pre-summed coordinates, and subtract smaller boxes
	//figured this out by playing with foam blocks
	return (sum_cube[x2][y2][z2] + sum_cube[x1][y1][z2] + sum_cube[x1][y2][z1] + sum_cube[x2][y1][z1]
		  - sum_cube[x1][y2][z2] - sum_cube[x2][y1][z2] - sum_cube[x2][y2][z1] - sum_cube[x1][y1][z1]);
}


int main() {
	//Handle input
	ifstream fin("SampleTestCase.txt");

	int T; 
	fin >> T;
	for (int testc = 0; testc < T; testc++)
	{
		int M;
		fin >> N >> M;
		for (int M_entry = 0; M_entry < M; M_entry++)
		{
			string op;
			fin >> op;
			if (op == "UPDATE")
			{
				int x, y, z, W;
				fin >> x >> y >> z >> W; 
				x--; y--; z--;
				update_entry(x, y, z, W);
			}

			if (op == "QUERY")
			{
				int x1, y1, z1, x2, y2, z2;
				fin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
				x1--; y1--; z1--; x2--; y2--; z2--;
				cout << answer_query(x1, y1, z1, x2, y2, z2) << endl;
			}
		}

		clear_cube();
	}

	return 0;
}
