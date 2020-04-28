/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/
#pragma once

#include "P1_Map_Fork.h"

class TurnCost_Map : public Map
{
private:
	unsigned short *cost_flat_map;

public:
	TurnCost_Map(size_t total_levels, size_t total_rows, size_t total_columns);
	~TurnCost_Map();



};

