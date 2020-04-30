/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/
#include "Cost_Map.h"
#include <queue>

using namespace std;

Cost_Map::Cost_Map(size_t total_rows, size_t total_columns)
	: Map(1,total_rows,total_columns)
{	
	cost_flat_map = new unsigned short[total_map_size];
	memset(cost_flat_map, USHRT_MAX, sizeof(unsigned short)*total_map_size);
}

Cost_Map::~Cost_Map()
{
	delete[] cost_flat_map;
}

size_t Cost_Map::get_adjacent_cell_index_in_direction(Direction direction, size_t point)
{
	//represents failure to get an adjacent cell, will fail any index access function
	size_t result_index = SIZE_MAX;

	if (point > total_map_size)
		return result_index;
	
	//boundaries must be checked. 
	//the previous map worked because values were handled differently, and checked each
	//struct data pt, did not use index math, but relied on rollover, had "extra" calls)
	//unclear if more performant, but should use less cpu ops, because fewere checks/calls
	//would need to measure it
	switch (direction)
	{
	case N:
		(point / num_cols == 0) ? NULL : result_index = point - num_cols;
		break;
	case E:
		(point % num_cols == num_cols - 1) ? NULL : result_index = point + 1;
		break;
	case S:
		(point / num_cols == num_rows - 1) ? NULL : result_index = point + num_cols;
		break;
	case W:
		(point % num_cols == 0) ? NULL : result_index = point - 1;
		break;
	default:
		break;
	}

	return result_index;
}

inline size_t Cost_Map::get_adjacent_cell_index_in_direction(Direction direction, map_coordinates point)
{
	return get_adjacent_cell_index_in_direction(direction, get_index_from_coordinates(point));
}

unsigned short Cost_Map::manhattan_distance_to_goal(size_t point)
{
	size_t distance = USHRT_MAX;
	if (point_is_traversable(point))
	{
		long long temp = (point / num_cols) - (goal_point / num_cols);
		(temp < 0) ? temp *= -1 : NULL;
		distance = temp;
		temp = (point % num_cols) - (goal_point % num_cols);
		(temp < 0) ? temp *= -1 : NULL;
		distance += temp;
	}

	(distance > USHRT_MAX) ? distance = USHRT_MAX : NULL;
	return (unsigned short)distance;
}

inline unsigned short Cost_Map::manhattan_distance_to_goal(map_coordinates point)
{
	return manhattan_distance_to_goal(get_index_from_coordinates(point));
}

bool Cost_Map::calculate_costs_dynamic_programing()
{
	//this is not good style, function needs to be refactored
	vector<Direction> starting_directions;
	starting_directions.push_back(Direction(N));
	starting_directions.push_back(Direction(E));
	starting_directions.push_back(Direction(S));
	starting_directions.push_back(Direction(W));


	for (int i = 0; i < starting_directions.size(); i++)
	{
		queue<size_t> search; 
		queue<size_t> next_turn_search;
		Direction current_direction = starting_directions.at(i);
		search.push(start_point);
		unsigned short current_turn_cost = 0;
		cost_flat_map[start_point] = 0;

		do
		{
			queue<size_t> empty;
			next_turn_search = empty;
			while (!search.empty())
			{
				size_t index = search.front();
				(cost_flat_map[index] > current_turn_cost) ? cost_flat_map[index] = current_turn_cost : NULL;
				search.pop();

				size_t forward_index = get_adjacent_cell_index_in_direction(current_direction, index);
				while (point_is_traversable(forward_index))
				{
					//Forward cell is reachable, so it has same as current cost
					(cost_flat_map[forward_index] > current_turn_cost) ? cost_flat_map[forward_index] = current_turn_cost : NULL;

					size_t look_right = get_adjacent_cell_index_in_direction(right_turn_relative(current_direction), forward_index);
					if (point_is_traversable(look_right) && cost_flat_map[look_right] > current_turn_cost+1)
						next_turn_search.push(look_right);//this is wrong, fix later, needs two queues..

					//look forward to continue this no cost check
					forward_index = get_adjacent_cell_index_in_direction(current_direction, forward_index);
				}
			}
			search = next_turn_search;
			current_direction = right_turn_relative(current_direction);
			current_turn_cost++;
		} while (!next_turn_search.empty());
	}

	mark_all_visited_cells();

	//Solution found, there is some cost to get to the goal
	if (cost_flat_map[goal_point] != USHRT_MAX)
		return true;

	return false;
}

Direction right_turn_relative(Direction current)
{
	switch (current)
	{
	case N:
		return E;
	case E:
		return S;
	case S:
		return W;
	case W:
		return N;
	}
	return current;	
}

void Cost_Map::print_costmap_to_output(ostream& output)
{	
	for (size_t r = 0; r < num_rows; r++) {
		for (size_t c = 0; c < num_cols; c++) {
			output << cost_flat_map[get_index_from_coordinates(0, r, c)] << '\t';
		}
		output << "\n";
	}
}

void Cost_Map::mark_all_visited_cells()
{
	for (size_t i = 0; i < total_map_size; i++)
	{
		if (cost_flat_map[i] != USHRT_MAX)
			flat_map[i] = 'p';
	}
}

