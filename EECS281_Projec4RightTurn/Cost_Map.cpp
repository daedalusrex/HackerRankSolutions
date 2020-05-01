/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/
#include "Cost_Map.h"
#include <queue>
#include <algorithm>

using namespace std;

bool not_max_pred(unsigned short test);

Cost_Map::Cost_Map(size_t total_rows, size_t total_columns)
	: Map(1,total_rows,total_columns)
{	
	cost_flat_map = new Group_Pose_Costs[total_map_size];
	//memset(cost_flat_map, USHRT_MAX, sizeof(unsigned short)*total_map_size);
}

Cost_Map::~Cost_Map()
{
	delete[] cost_flat_map;
}

size_t Cost_Map::next_index_in_direction(Direction direction, size_t point)
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

inline size_t Cost_Map::next_index_in_direction(Direction direction, map_coordinates point)
{
	return next_index_in_direction(direction, get_index_from_coordinates(point));
}

unsigned short Cost_Map::manhattan_distance_to_goal(size_t point)
{
	size_t distance = USHRT_MAX;
	if (point_is_traversable(point))
	{
		//llabs(point / num_cols - goal_point / num_cols);
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
	//this is not good style, function needs to be refactored, more abstraction
	vector<Direction> starting_directions;
	starting_directions.push_back(Direction(N));
	starting_directions.push_back(Direction(E));
	starting_directions.push_back(Direction(S));
	starting_directions.push_back(Direction(W));


	for (int i = 0; i < starting_directions.size(); i++)
	{
		//represents points to check that can be reached in x turns
		queue<size_t> next_turn_search;
		queue<size_t> search; 
		Direction cur_dir = starting_directions.at(i);
		search.push(start_point);
		unsigned short cur_turn_cost = 0;
		cost_flat_map[start_point].cost[cur_dir] = 0;

		do
		{
			queue<size_t> reset;
			next_turn_search = reset;
			while (!search.empty())
			{
				size_t index = search.front();
				search.pop();

				//if the currnetly searched node had a higher previous turn cost to get here, then overwrite with this
				if (cost_flat_map[index].cost[cur_dir] > cur_turn_cost)
					cost_flat_map[index].cost[cur_dir] = cur_turn_cost;
				//previous is not updated, because it is done during the peek right part of the search

				//search all cell that are in the same direction as this orientation 
				Pose previous_pose(index, cur_dir);
				size_t forward_index = next_index_in_direction(cur_dir, index);
				while (point_is_traversable(forward_index))
				{
					//test if the turning right should add a new point to the next search round 
					Direction right_turn = right_turn_relative(cur_dir);
					size_t right_location = next_index_in_direction(right_turn, forward_index);
					Pose peek_right(right_location, right_turn);

					if (point_is_traversable(peek_right.location)) {
						if (cost_flat_map[peek_right.location].cost[peek_right.direction] > (cur_turn_cost + 1))
						{
							next_turn_search.push(peek_right.location);
							cost_flat_map[peek_right.location].cost[peek_right.direction] = (cur_turn_cost + 1);
							cost_flat_map[peek_right.location].previous_pose[peek_right.direction] = Pose(forward_index, cur_dir);
						}
					}


					//Forward cell is reachable, so if has greater as current cost, update it with new path
					if (cost_flat_map[forward_index].cost[cur_dir] > cur_turn_cost) {
						cost_flat_map[forward_index].cost[cur_dir] = cur_turn_cost;
						cost_flat_map[forward_index].previous_pose[cur_dir] = previous_pose;
					}
			

					//look forward to continue to connect all cells that can be reached at no cost
					previous_pose = Pose(forward_index, cur_dir);
					forward_index = next_index_in_direction(cur_dir, forward_index);
				}
			}
			search = next_turn_search;
			cur_dir = right_turn_relative(cur_dir);
			cur_turn_cost++;
		} while (!next_turn_search.empty());
	}

	mark_all_visited_cells();

	//Solution found, there is some cost to get to the goal
	//if (cost_flat_map[goal_point] != USHRT_MAX)
	if(any_of(cost_flat_map[goal_point].cost, cost_flat_map[goal_point].cost+(NUM_DIRECTIONS),not_max_pred))
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
			//output << cost_flat_map[get_index_from_coordinates(0, r, c)] << '\t';
			output << min_element(cost_flat_map[get_index_from_coordinates(0, r, c)].cost,
				cost_flat_map[get_index_from_coordinates(0, r, c)].cost+NUM_DIRECTIONS);
		}
		output << "\n";
	}
}

unsigned short Cost_Map::goal_turn_cost()
{
	return *min_element(cost_flat_map[goal_point].cost, cost_flat_map[goal_point].cost + NUM_DIRECTIONS);
}

bool not_max_pred(unsigned short test) {
	return test != USHRT_MAX;
}
//wrong
void Cost_Map::mark_all_visited_cells()
{
	for (size_t i = 0; i < total_map_size; i++)
	{
		//if (cost_flat_map[0].cost[0] != USHRT_MAX)
		if(any_of(cost_flat_map[i].cost, cost_flat_map[i].cost+NUM_DIRECTIONS, not_max_pred))	
			flat_map[i] = 'p';
	}
}

Group_Pose_Costs::Group_Pose_Costs()
{
	memset(cost, USHRT_MAX, NUM_DIRECTIONS * sizeof(unsigned short));
}
