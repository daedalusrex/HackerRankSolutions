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
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <filesystem>

#include "Map.h"

using namespace std;

void modify_map_with_backtrace(Map& maze, size_t* parent_map)
{
	size_t next = maze.get_goal_index();
	size_t parent = parent_map[maze.get_goal_index()];
	//size_t parent = parent_map[current];

	while (next != maze.get_start_index())
	{
		map_coordinates cor_next = maze.get_coordinates_from_index(next);
		map_coordinates cor_parent = maze.get_coordinates_from_index(parent);

		if (cor_next.row < cor_parent.row)
			maze.modify_cell(parent, 'n');
		else if (cor_next.row > cor_parent.row)
			maze.modify_cell(parent, 's');
		else if (cor_next.column < cor_parent.column)
			maze.modify_cell(parent, 'w');
		else if (cor_next.column > cor_parent.column)
			maze.modify_cell(parent, 'e');
		else if (cor_next.level < cor_parent.level)
			maze.modify_cell(parent, 'u');
		else if (cor_next.level > cor_parent.level)
			maze.modify_cell(parent, 'd');

		next = parent;
		parent = parent_map[parent];
	}
}


bool Solve_Map(Map& maze)
{
	queue<size_t> search;
	bool* visited = new bool[maze.get_map_size()];
	memset(visited, false, maze.get_map_size());
	size_t* parent_map = new size_t[maze.get_map_size()];
	memset(parent_map, (size_t)0, maze.get_map_size());

	search.push(maze.get_start_index());
	visited[maze.get_start_index()] = true;
	size_t neighbors[6];
	size_t current = 0;

	bool solved = false;
	while (!search.empty())
	{
		current = search.front();
		search.pop();

		if (current == maze.get_goal_index())
		{
			modify_map_with_backtrace(maze, parent_map);
			solved = true;
			break;
		}
			

		unsigned short valid = maze.get_neighbors_of_index(current, neighbors);
		for (int i = 0; i < valid; i++)
		{
			if (!visited[neighbors[i]]) {
				search.push(neighbors[i]);
				parent_map[neighbors[i]] = current;
				visited[neighbors[i]] = true;
			}
		}

	}

	delete[] visited;
	delete[] parent_map;
	
	return solved;
}


int main(void) {

	ifstream fin("input_tests/InSampleTest.txt");
	size_t side_length;
	size_t levels;
	fin >> side_length;
	fin >> levels;


	ofstream fout("output_tests/OutputBasic.txt");

	

	//later directions on how to access multiple files (run all tests at once)
	/*std::string path = "/path/to/directory";
	for (const auto& entry : fs::directory_iterator(path))
		std::cout << entry.path() << std::endl;*/

	Map testmap(levels, side_length, side_length);
	bool solved = false;

	if (!testmap.initialize_from_input(fin))
		fout << "Error in Input file";
	else
		solved = Solve_Map(testmap);

	testmap.print_map_to_output(fout);
	if (solved)
	{
		fout << "SOLVED THE MAP" << endl;
	}

	Map copy(testmap);

	//ofstream fout("output_tests/OutputBasic.txt");
	
	testmap.print_map_to_output(cout);
	copy.print_map_to_output(cout);
	
	return 0;
}