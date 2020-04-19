#include "Map.h"

Map::Map(size_t total_levels, size_t total_rows, size_t total_columns)
	: num_levels(total_levels), num_rows(total_rows), num_cols(total_columns),
	start_point(0), goal_point(0),
	level_area_size(num_rows * num_cols),
	total_map_size(level_area_size * num_levels)
{
	flat_map = new char[total_map_size];
	memset(flat_map, 'X', total_map_size);
}

Map::~Map()
{
	delete[] flat_map;
}

Map::Map(const Map& old) : num_levels(old.num_levels), num_rows(old.num_rows),
	num_cols(old.num_cols), level_area_size(old.level_area_size), total_map_size(old.total_map_size),
	start_point(old.start_point), goal_point(old.goal_point)
{
	flat_map = new char[total_map_size];
	memcpy(flat_map, old.flat_map, total_map_size);
}

void Map::initialize_from_input(istream &input)
{
}

inline map_coordinates Map::get_coordinates_from_index(size_t flat_index)
{
	size_t lev,row,col;
	//finds the 0 based level(first dimension) index by dividing the size of each area (or 2D section), relies on integer truncation
	lev = flat_index / level_area_size;
	//finds the 0 based row(second dimension) index by first only looking at remainder (within the right 2D array) and dividing by each row width
	row = (flat_index % level_area_size) / num_cols;
	//finds the column (last dimension) index by getting the remainder based on column width
	col = flat_index % num_cols;	
	return map_coordinates(lev,row,col);
}

inline size_t Map::get_index_from_coordinates(map_coordinates input)
{
	/* 	3D array arithmateic, move first by largest chunk (number of 2D arrays times 2D array size
	Then move by number of rows times row size
	then move finally by last array number of columns within the row */
	return size_t(input.level * level_area_size + input.row * num_cols + input.column);
}

inline size_t Map::get_index_from_coordinates(size_t level, size_t row, size_t column)
{
	//exactly the same as with other input but build this way for LCV convenience
	return size_t(level * level_area_size + row * num_cols + column);
}

void Map::print_map_to_output(ostream &output)
{
	//a couple problems are here because the input they have is sort of backwards intetnionally
	//for now design decision is to create the map in the order they gave an so on and when printing
	//or doing the logic just translate a little bit, since it really only matters during the output
	for (size_t l = 0; l < num_levels; l++)	{
		output << "#level " << num_levels - l << endl;
		for (size_t r = 0; r < num_rows; r++)	{
			for (size_t c = 0; c < num_cols; c++)	{
				output << flat_map[get_index_from_coordinates(l, r, c)];
			}
			output << "\n";
		}
	}
}

void Map::get_neighbors_of_index(size_t flat_position, size_t* neighbor_array, unsigned short valid_neighbors)
{//TODO
}

bool Map::point_is_traversable(map_coordinates test_point)
{
	return false;
}
