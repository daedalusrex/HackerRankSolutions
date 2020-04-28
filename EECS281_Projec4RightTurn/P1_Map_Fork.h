/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/

#pragma once

#include <iostream>

struct map_coordinates
{
	size_t level;
	size_t row;
	size_t column;
	map_coordinates(size_t lev_, size_t row_, size_t col_)
		: level(lev_), row(row_), column(col_) {};
	map_coordinates() : level(0), row(0), column(0) {};
};

class Map
{
protected:
	const size_t num_levels;
	const size_t num_cols;
	const size_t num_rows;
	const size_t level_area_size;
	const size_t total_map_size;

	char* flat_map;

	//flat array index of the starting position, first occurence of char 'S'
	size_t start_point;
	//flat array index of the starting position, first occurence of char 'G'
	size_t goal_point;

	//Map() {};
public:
	//creates new map with given dimensions, allocates needed memory
	Map(size_t total_levels, size_t total_rows, size_t total_columns);
	~Map();
	Map(const Map& old);

	inline size_t get_map_size() { return total_map_size; }
	inline size_t get_start_index() { return start_point; }
	inline size_t get_goal_index() { return goal_point; }
	//uses input stream based on specs to fill in map with values for all chars
	bool initialize_from_input(std::istream& input);
	//takes the flat array index and returns coordinates based on 3D array indexing scheme
	inline map_coordinates get_coordinates_from_index(size_t flat_index);
	//takes coordinates and returns the flat array index
	inline size_t get_index_from_coordinates(map_coordinates input_coordinates);
	//takes coordinates and returns the flat array index
	inline size_t get_index_from_coordinates(size_t level, size_t row, size_t column);
	//prints out current map information with formatting to given output stream
	void print_map_to_output(std::ostream& output);
	//returns map coordinates of starting poisition, does not check if initialized
	inline map_coordinates get_start_coordinates() { return get_coordinates_from_index(start_point); }
	//returns map coordinates of goal position, does not check if initialized
	inline map_coordinates get_goal_coordinates() { return get_coordinates_from_index(goal_point); }
	//expects an array from caller, of max size 6 and fills with all valid neighbors flat indexes based on rules (limit of 6)
	//returns number of valid neighbors found
	unsigned short get_neighbors_of_index(size_t flat_position, size_t* neighbor_array);

	bool modify_cell(size_t index, char newchar);
protected:
	//Returns true only if test_point is within boundaries and has allowed char
	bool point_is_traversable(map_coordinates test_point);
};




