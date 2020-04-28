/*
EECS 281 Project 4
Right Turn Only Map
Post-Humous Optimization
May 2020
*/

#include <string>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>

#include "Algorithms_281_Proj4.h"
#include "TurnCost_Map.h"
#include "P1_Map_Fork.h"


using namespace std;

int main(void) {

	Map test_old(10, 10, 10);
	
	TurnCost_Map test(10, 10, 10);

	test.initialize_from_input(cin);

}