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

#define MAX_DIMENSION 1000000
#define CHANCE_DOWN 1
#define CHANCE_UP 2

bool create_random_map(size_t side_length, size_t num_levels, string filename, string comment, unsigned int percent_woods)
{
	if (percent_woods > 100 || side_length > MAX_DIMENSION || num_levels > MAX_DIMENSION)
		return false;

	ofstream genout(filename);
	if (!genout.is_open())
		return false;

	genout << side_length << '\n' << num_levels << '\n';
	genout << '#' << comment << endl;
	genout << '#' << "percent of woods: " << percent_woods << endl;

	Map testcase_map(num_levels, side_length, side_length);

	srand(time(NULL));

	for (size_t i = 0; i < testcase_map.get_map_size(); i++)
	{
		int chance = rand() % 100 + 1;
		if (chance <= CHANCE_DOWN)
			testcase_map.modify_cell(i, 'v');
		else if (chance <= CHANCE_UP)
			testcase_map.modify_cell(i, '^');
		else if (chance <= percent_woods)
			testcase_map.modify_cell(i, 'X');
		else
			testcase_map.modify_cell(i, '.');

	}
	
	
	testcase_map.modify_cell(0, 'S');
	testcase_map.modify_cell(testcase_map.get_map_size()-1, 'O');

#if 0
	size_t position = 0;
	if (testcase_map.get_map_size() > RAND_MAX)
	{
		position = rand() * (testcase_map.get_map_size() / RAND_MAX);
		testcase_map.modify_cell(position, 'S');
		position = rand() * (testcase_map.get_map_size() / RAND_MAX);
		testcase_map.modify_cell(position, 'O');
	}
	else
	{
		position = rand() % testcase_map.get_map_size();
		testcase_map.modify_cell(position, 'S');
		position = rand() % testcase_map.get_map_size();
		testcase_map.modify_cell(position, 'O');
	}
#endif

	testcase_map.print_map_to_output(genout);

	return true;
}

void mark_all_visited(Map& maze, bool* visited)
{
	for (size_t i = 0; i < maze.get_map_size(); i++)
		(visited[i]) ? maze.modify_cell(i, '@') : NULL;
}

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

	if (!solved)
		mark_all_visited(maze, visited);

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
		std::cout << entry.path().filename().string() << "\n\n";
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

	cout << "All test finished total seconds of:" << (all_done - all_start) / CLOCKS_PER_SEC << endl;
	cout << "All test execution in ticks of    :" << (all_done - all_start) << endl;

	cout << "\n\n\n*******RESULTS******\n\n\n" << endl;
	int i = 0, successfulresults = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (results[i])
		{
			cout << "PASSED : ";
			successfulresults++;
		}
		else 
			cout << "FAILED : ";
		
		cout << "Test Filename:" << entry.path().filename() << endl;

		if (strstr(entry.path().filename().string().c_str(), "fail") && !results[i])
			successfulresults++;
		i++;
	}

	cout << "\n\n\nFinal Tally\nSUCCESS:  " << successfulresults << "\nTOTAL OF: " << i << endl;

	//Generating test case for next attempt:
	/*if (create_random_map(1000, 32, "0_Real_Big_Test.txt", "Limits Testing ,Trees, far start and end", 33))
		cout << "New Test Map Created Successfully!" << endl;*/


	return 0;
}