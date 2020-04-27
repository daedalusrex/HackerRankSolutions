/*
EECS 281 Project 1
Post-Humous Optimization
April 2020
*/
#include "Map.h"
#include <fstream>
#include <queue>
#include <time.h>


#define MAX_DIMENSION 1000000
#define CHANCE_DOWN 1
#define CHANCE_UP 2

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

void mark_all_visited(Map& maze, bool* visited)
{
	for (size_t i = 0; i < maze.get_map_size(); i++)
		(visited[i]) ? maze.modify_cell(i, '@') : NULL;
}


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
	testcase_map.modify_cell(testcase_map.get_map_size() - 1, 'O');

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

