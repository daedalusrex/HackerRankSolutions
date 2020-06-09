/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/
#pragma once

#include "P1_Map_Fork.h"


enum Direction	{
	N,E,S,W,NUM_DIRECTIONS
};

Direction right_turn_relative(Direction current);

struct Pose {
	size_t location;
	Direction direction;
	Pose(size_t loc, Direction dir) : location(loc), direction(dir) {};
	Pose() : location(0), direction(N) {};
};

struct Group_Pose_Costs {
	//cost (num turns) to get to the current pose (location and orientation), based on direction index
	unsigned short cost[NUM_DIRECTIONS];
	//represents the lowest cost location and orienation that enqueued this spot
	Pose previous_pose[NUM_DIRECTIONS];
	Group_Pose_Costs();
};

class Cost_Map : public Map
{
private:
	Group_Pose_Costs*  cost_flat_map;

public:
	Cost_Map(size_t total_rows, size_t total_columns);
	~Cost_Map();

	unsigned short get_neighbors_of_index(size_t flat_position, size_t* neighbor_array);
		
	size_t next_index_in_direction(Direction direction, size_t point);
	inline size_t next_index_in_direction(Direction direction, map_coordinates point);
		
	unsigned short manhattan_distance_to_goal(size_t index);
	inline unsigned short manhattan_distance_to_goal(map_coordinates point);


	bool calculate_costs_dynamic_programing();
	void print_costmap_to_output(std::ostream& output);
	unsigned short goal_turn_cost();

	void mark_all_visited_cells();

	void reset_all_costs() {}
	void calculate_optimial_solution_BnB() {}
};

