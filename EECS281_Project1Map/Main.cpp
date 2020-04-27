/*
EECS 281 Project 1
Post-Humous Optimization
April 2020
*/

#include <ctime>

#include <string>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <time.h>

#include "Map.h"
#include "Algorithms_281_Proj1.h"

using namespace std;

int main(void) {

	ifstream fin;
	ofstream fout;
	size_t side_length;
	size_t levels;
	//ifstream fin("input_tests/InSampleTest.txt");
	//ofstream fout("test_results_out/OutputBasic.txt");
	clock_t all_start = clock();
	vector<bool> results;

	//how to access multiple files (run all tests at once)
	std::string path = "input_tests";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		clock_t testcase_start = clock();
		std::cout << entry.path().filename().string() << "\n\n";
		fin.open(entry.path());
		//for a specific test
		//fin.open("input_tests/test0.txt");
		
		fin >> side_length;
		fin >> levels;
		bool solved = false;
		Map main_map(levels, side_length, side_length);
		
		//ofstream fout("output_tests/OutputBasic.txt");
		string outfilename;
		outfilename = entry.path().filename().string();
		outfilename = "test_results_out/results_" + outfilename;
		fout.open(outfilename);


		if (!main_map.initialize_from_input(fin))
			fout << "ERROR Formatting incorrect in Input file\n";
		else
			solved = Solve_Map(main_map);

		if (solved)
		{
			main_map.print_map_to_output(fout);
			fout << "SOLVED THE MAP\n" << endl;
			
		}
		else
		{
			fout << "NO SOLUTION FOUND\n";
			main_map.print_map_to_output(fout);
		}
		results.push_back(solved);

		clock_t testcase_finish = clock();
		fout << "Test Case Finished in seconds:" << (testcase_finish - testcase_start) / CLOCKS_PER_SEC << endl;
		fout << "Test Case execution in ticks:" << (testcase_finish - testcase_start) << endl;

		cout << "Test Case Finished in seconds:" << (testcase_finish - testcase_start) / CLOCKS_PER_SEC << endl;
		cout << "Test Case execution in ticks:" << (testcase_finish - testcase_start) << endl;

		fin.close();
		fout.close();

	}

	clock_t all_done = clock();

	cout << "All test finished total seconds of:" << (all_done - all_start) / CLOCKS_PER_SEC << endl;
	cout << "All test execution in ticks of    :" << (all_done - all_start) << endl;

	cout << "\n\n\n*******RESULTS******\n\n\n" << endl;
	int i = 0, successfulresults = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path))
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

	//Generating test case for next attempt:
	/*if (create_random_map(1000, 32, "0_Real_Big_Test.txt", "Limits Testing ,Trees, far start and end", 33))
		cout << "New Test Map Created Successfully!" << endl;*/


	return 0;
}