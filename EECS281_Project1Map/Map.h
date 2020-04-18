#pragma once

#include <string>
#include <cstring>
#include <iostream>

using namespace std;

struct map_coordinates
{
	size_t level;
	size_t row;
	size_t column;
	map_coordinates(size_t lev_, size_t row_, size_t col_) 
		: level(lev_), row(row_), column(col_) {};
};

class Map
{
private:
	size_t num_levels;
	size_t num_cols;
	size_t num_rows;
	size_t level_area_size;
	
	char* flat_map;
	size_t start_point;
	size_t goal_point;


	Map() {};

public:
	Map(size_t level_side_length, size_t level_number);
	~Map();
	Map(const Map& old_map);

	void initialize_from_input(istream input);
	inline map_coordinates get_coordinates_from_index(size_t flat_index);
	inline size_t get_index_from_coordinates(map_coordinates input_coordinates);
	inline size_t get_index_from_coordinates(size_t level, size_t row, size_t column);
	void print_map_to_output(ostream output);
	inline map_coordinates get_start_coordinates() { return get_coordinates_from_index(start_point); }
	inline map_coordinates get_goal_coordinates() { return get_coordinates_from_index(goal_point); }
	void get_neighbors_of_index(size_t falt_index, size_t* neighbor_array);
};

