/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/
#include "TurnCost_Map.h"

TurnCost_Map::TurnCost_Map(size_t total_levels, size_t total_rows, size_t total_columns)
	: Map(total_levels,total_rows,total_columns)
{
	if (total_levels > 1)
	{
		cost_flat_map = NULL;
		return;
	}
		
	cost_flat_map = new unsigned short[total_map_size];
}

TurnCost_Map::~TurnCost_Map()
{
	delete[] cost_flat_map;
}


