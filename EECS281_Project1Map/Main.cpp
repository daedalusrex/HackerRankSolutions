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
#include <time.h>

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

	ifstream fin;
	ofstream fout;
	size_t side_length;
	size_t levels;
	//ifstream fin("input_tests/InSampleTest.txt");
	//ofstream fout("test_results_out/OutputBasic.txt");
	clock_t all_start = clock();
	vector<bool> results;

	//how to access multiple files (run all tests at once)
	std::string path = "input_tests";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		clock_t testcase_start = clock();
		std::cout << entry.path() << std::endl;
		fin.open(entry.path());
		//for a specific test
		//fin.open("input_tests/test0.txt");
		
		fin >> side_length;
		fin >> levels;
		bool solved = false;
		Map main_map(levels, side_length, side_length);
		
		//ofstream fout("output_tests/OutputBasic.txt");
		string outfilename;
		outfilename = entry.path().filename().string();
		outfilename = "test_results_out/results_" + outfilename;
		fout.open(outfilename);


		if (!main_map.initialize_from_input(fin))
			fout << "ERROR Formatting incorrect in Input file\n";
		else
			solved = Solve_Map(main_map);

		if (solved)
		{
			main_map.print_map_to_output(fout);
			fout << "SOLVED THE MAP\n" << endl;
			
		}
		else
		{
			fout << "NO SOLUTION FOUND\n";
			main_map.print_map_to_output(fout);
		}
		results.push_back(solved);

		clock_t testcase_finish = clock();
		fout << "Test Case Finished in seconds:" << (testcase_finish - testcase_start) / CLOCKS_PER_SEC << endl;
		fout << "Test Case execution in ticks:" << (testcase_finish - testcase_start) << endl;

		cout << "Test Case Finished in seconds:" << (testcase_finish - testcase_start) / CLOCKS_PER_SEC << endl;
		cout << "Test Case execution in ticks:" << (testcase_finish - testcase_start) << endl;

		fin.close();
		fout.close();

	}

	clock_t all_done = clock();

	cout << "All test finished total time of " << (all_done - all_start) / CLOCKS_PER_SEC << endl;

	cout << "\n\n\n*******RESULTS******\n\n\n" << endl;
	int i = 0, passed = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (results[i])
		{
			cout << "PASSED : ";
			passed++;
		}
		else 
			cout << "FAILED : ";
		
		cout << "Test Filename:" << entry.path().filename() << endl;
		i++;
	}

	cout << "\n\n\nFinal Tally\n\nPASSED: " << passed << "\nOut of :" << i + 1 << endl;
	return 0;
}