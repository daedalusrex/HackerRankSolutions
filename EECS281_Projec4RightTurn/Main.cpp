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
#include <filesystem>
#include <time.h>

#include "Algorithms_281_Proj4.h"
#include "Cost_Map.h"
#include "P1_Map_Fork.h"


using namespace std;



void RunAllTestsInFolder(string relative_path)
{
	ifstream fin;
	ofstream fout;
	
	vector<bool> results;
	for (const auto& entry : std::filesystem::directory_iterator(relative_path))
	{
		clock_t testcase_start = clock();
		std::cout << entry.path().filename().string() << "\n\n";
		fin.open(entry.path());

		string outfilename;
		outfilename = entry.path().filename().string();
		outfilename = "result/result_" + outfilename;
		fout.open(outfilename);


		int Rows, Cols;
		string In;
		fin >> In;
		int x = In.find("x");
		string row = In.substr(0, x);
		string col = In.substr(x + 1, In.size() - x);

		Cost_Map main_map(atoi(row.c_str()), atoi(col.c_str()));
		
		bool solved = false;

		if (!main_map.initialize_from_input(fin))
			fout << "ERROR Formatting incorrect in Input file\n";
		else
			solved = main_map.calculate_costs_dynamic_programing();

		if (solved)
		{
			main_map.print_map_to_output(fout);
			fout << "SOLVED THE MAP\n" << endl;
			fout << "Best Coast to get to Goal: " << main_map.goal_turn_cost() << endl;
		}
		else
		{
			fout << "NO SOLUTION FOUND\n";
			main_map.print_map_to_output(fout);
		}
		results.push_back(solved);
		//main_map.print_costmap_to_output(cout);

		clock_t testcase_finish = clock();
		fout << "Test Case Finished in seconds:" << (testcase_finish - testcase_start) / CLOCKS_PER_SEC << endl;
		fout << "Test Case execution in ticks:" << (testcase_finish - testcase_start) << endl;

		cout << "Test Case Finished in seconds:" << (testcase_finish - testcase_start) / CLOCKS_PER_SEC << endl;
		cout << "Test Case execution in ticks:" << (testcase_finish - testcase_start) << endl;

		fin.close();
		fout.close();

	}

	cout << "\n\n\n*******RESULTS******\n\n\n" << endl;
	int i = 0, successfulresults = 0;
	for (const auto& entry : std::filesystem::directory_iterator(relative_path))
	{
		if (results[i])
		{
			cout << "PASSED : ";
			successfulresults++;
		}
		else
			cout << "FAILED : ";

		cout << "Test Filename:" << entry.path().filename() << endl;

		if (strstr(entry.path().filename().string().c_str(), "fail") && !results[i])
			successfulresults++;
		i++;
	}

	cout << "\n\n\nFinal Tally\nSUCCESS:  " << successfulresults << "\nTOTAL OF: " << i << endl;
}



int main(void) {

		
	clock_t all_start = clock();
	

	RunAllTestsInFolder("input_test");

	clock_t all_done = clock();

	cout << "All test finished total seconds of:" << (all_done - all_start) / CLOCKS_PER_SEC << endl;
	cout << "All test execution in ticks of    :" << (all_done - all_start) << endl;



	//Generating test case for next attempt:
	/*if (create_random_map(1000, 1000, "10000_Test.txt", "Limits Testing ,Trees, far start and end", 8))
		cout << "New Test Map Created Successfully!" << endl;*/


	return 0;
}