#include "Map.h"

Map::Map(size_t total_levels, size_t total_rows, size_t total_columns)
	: num_levels(total_levels), num_rows(total_rows), num_cols(total_columns),
	start_point(0), goal_point(0),
	level_area_size(num_rows * num_cols),
	total_map_size(level_area_size * num_levels)
{
	flat_map = new char[total_map_size+1];
	memset(flat_map, 'X', total_map_size);
	//added one extra char to hold null character so it can also be a c string
	flat_map[total_map_size] = '\0';
}

Map::~Map()
{
	delete[] flat_map;
}

Map::Map(const Map& old) : num_levels(old.num_levels), num_rows(old.num_rows),
	num_cols(old.num_cols), level_area_size(old.level_area_size), total_map_size(old.total_map_size),
	start_point(old.start_point), goal_point(old.goal_point)
{
	flat_map = new char[total_map_size+1];
	memcpy(flat_map, old.flat_map, total_map_size+1);
}

bool Map::initialize_from_input(istream &input)
{
	size_t current = 0;
	
	while (!input.eof())
	{	//boundary checking
		if (current + num_cols > total_map_size)
			return false;

		//if comment is detected then skip to the next line
		char nextchar = input.peek();
		if (nextchar == '#' || nextchar == '\n')
		{
			input.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
			
		////std::string style implementation
		//string line;
		//getline(input, line);
		//if (line.size() > num_cols)
			//return false;
		//memcpy(flat_map + current, line.c_str(), line.size());
		//current += line.size();

		//cstring classic implementation
		//this writes a null after the edge of memory, so addded an extra space for null termination
		input.getline(flat_map + current, num_cols + 1);
		//fail bit will be set if too many chars are read
		if (input.fail())
			return false;
		//Advance by the amount of characters read, should always be num_cols plus newline if succeed above
		current += input.gcount()-1;
	}
	
	//set start point
	char* point = strchr(flat_map, 'S');
	//Covers no start point fouund, or duplicates
	if (point == NULL || point != strrchr(flat_map, 'S'))
		return false;
	start_point = point - flat_map;

	//set goal point
	point = strchr(flat_map, 'O');
	//Covers no start point fouund, or duplicates
	if (point == NULL || point != strrchr(flat_map, 'O'))
		return false;
	goal_point = point - flat_map;

	//check if all characters are legal and allowed;
	//might be faster if using strbprk, but typing out the illegal string is more time consuming
	point = flat_map;
	while (*point != '\0')
	{
		switch (*point)
		{
		case '.':
		case 'X':
		case 'O':
		case 'S':
		case '^':
		case 'v':
			point++;
			break;
		default:
			return false;
		}
	}
	return true;
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


unsigned short Map::get_neighbors_of_index(size_t flat_position, size_t* neighbor_array)
{
	if (flat_position > total_map_size)
		return 0;
	
	map_coordinates origin = get_coordinates_from_index(flat_position);
	map_coordinates test = origin;
	unsigned short valid_index = 0;

	test.row--; //North
	if (point_is_traversable(test))	{
		neighbor_array[valid_index] = get_index_from_coordinates(test);
		valid_index++;
	}
	test = origin;
		
	test.column++; //East
	if (point_is_traversable(test))	{
		neighbor_array[valid_index] = get_index_from_coordinates(test);
		valid_index++;
	}
	test = origin;

	test.row++; //South
	if (point_is_traversable(test)) {
		neighbor_array[valid_index] = get_index_from_coordinates(test);
		valid_index++;
	}
	test = origin;

	test.column--; //West
	if (point_is_traversable(test)) {
		neighbor_array[valid_index] = get_index_from_coordinates(test);
		valid_index++;
	}
	test = origin;

	//Up
	if (flat_map[flat_position] == '^')
	{
		test.level--;
		if (point_is_traversable(test)) {
			neighbor_array[valid_index] = get_index_from_coordinates(test);
			valid_index++;
		}
		test = origin;
	}

	//Down
	if (flat_map[flat_position] == 'v')
	{
		test.level++;
		if (point_is_traversable(test)) {
			neighbor_array[valid_index] = get_index_from_coordinates(test);
			valid_index++;
		}
		test = origin;
	}


	return valid_index;
}

bool Map::modify_cell(size_t index, char newchar)
{
	if(index > total_map_size)
		return false;
	flat_map[index] = newchar;
	return true;
}

bool Map::point_is_traversable(map_coordinates point)
{
	if (point.level < num_levels && point.row < num_rows && point.column < num_cols)
	{
		switch (flat_map[get_index_from_coordinates(point)])
		{
		case '.':
		case 'O':
		case 'S':
		case '^':
		case 'v':
			return true;
		case 'X':
		default:
			return false;
		}
	}
	return false;
}
