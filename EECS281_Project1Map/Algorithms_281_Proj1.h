/*
EECS 281 Project 1
Post-Humous Optimization
April 2020
*/
#pragma once

#include "Map.h"


void mark_all_visited(Map& maze, bool* visited);

void modify_map_with_backtrace(Map& maze, size_t* parent_map);

bool create_random_map(size_t side_length, size_t num_levels, string filename, string comment, unsigned int percent_woods);

bool Solve_Map(Map& maze);

