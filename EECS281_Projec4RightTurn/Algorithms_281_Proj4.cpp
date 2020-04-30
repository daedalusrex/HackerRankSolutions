/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/
#include "Algorithms_281_Proj4.h"
#include "P1_Map_Fork.h"
#include <fstream>
#include <time.h>

#define MAX_DIMENSION 1000000

using namespace std;

bool create_random_map(size_t rows, size_t columns, string filename, string comment, unsigned int percent_woods)
{
	if (percent_woods > 100 || rows > MAX_DIMENSION || columns > MAX_DIMENSION)
		return false;

	ofstream genout(filename);
	if (!genout.is_open())
		return false;

	genout << rows << 'x' << columns << '\n';
	genout << '#' << comment << endl;
	genout << '#' << "percent of woods: " << percent_woods << endl;

	Map testcase_map(1, rows, columns);

	srand(time(NULL));

	for (size_t i = 0; i < testcase_map.get_map_size(); i++)
	{
		int chance = rand() % 100 + 1;
		if (chance <= percent_woods)
			testcase_map.modify_cell(i, 'X');
		else
			testcase_map.modify_cell(i, '.');

	}

#if 0
	testcase_map.modify_cell(0, 'S');
	testcase_map.modify_cell(testcase_map.get_map_size() - 1, 'G');
#endif 


	size_t position = 0;
	
	position = rand() % testcase_map.get_map_size();
	testcase_map.modify_cell(position, 'S');
	position = rand() % testcase_map.get_map_size();
	testcase_map.modify_cell(position, 'G');
	

	
	testcase_map.print_map_to_output(genout);

	return true;
}
