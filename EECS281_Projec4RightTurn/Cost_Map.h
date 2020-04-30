/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/
#pragma once

#include "P1_Map_Fork.h"


enum Direction	{
	N,E,S,W
};

Direction right_turn_relative(Direction current);

class Cost_Map : public Map
{
private:
	unsigned short *cost_flat_map;

public:
	Cost_Map(size_t total_rows, size_t total_columns);
	~Cost_Map();

	unsigned short get_neighbors_of_index(size_t flat_position, size_t* neighbor_array);
		
	size_t get_adjacent_cell_index_in_direction(Direction direction, size_t point);
	inline size_t get_adjacent_cell_index_in_direction(Direction direction, map_coordinates point);
		
	unsigned short manhattan_distance_to_goal(size_t index);
	inline unsigned short manhattan_distance_to_goal(map_coordinates point);


	bool calculate_costs_dynamic_programing();
	void print_costmap_to_output(std::ostream& output);
	inline unsigned short goal_turn_cost() { return cost_flat_map[goal_point]; }

	void mark_all_visited_cells();
};

