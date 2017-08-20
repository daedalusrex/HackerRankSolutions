
#include <map>
#include <vector>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <queue>

using namespace std;


int degreeOfArray(vector < int > arr) {

	//Calculate the degree of the original array
	//use a map to keep track of each repeating value

	map<int, int> el_degrees;

	for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++)
	{
		//if we have seen this before, increase its count in the map
		if (el_degrees.count(*it) == 1)
			el_degrees[*it]++;
		else //else create new entry
			el_degrees.insert(pair<int, int>(*it, 1));
		
	}
	

	//Go through the map and find the the largest degree/frequency
	int arr_deg = 0;
	for (map<int, int>::iterator m_it = el_degrees.begin(); m_it != el_degrees.end(); m_it++)
	{
		if (m_it->second >= arr_deg)
			arr_deg = m_it->second;
		
	}

	//Go through again, and save the keys of all elements that the same degree
	vector<int> largest_degrees;
	for (map<int, int>::iterator m_it = el_degrees.begin(); m_it != el_degrees.end(); m_it++)
	{
		if (m_it->second == arr_deg)
			largest_degrees.push_back(m_it->first);
	}
	
	//By definition, there will be at least one subarray, which will be the original array size
	int sub_size = arr.size();

	//Scan through the list of known largest degrees, form a left and right index
	//then keep them if their size is the least encountered size
	for (vector<int>::iterator ld_it = largest_degrees.begin(); ld_it != largest_degrees.end(); ld_it++)
	{
		int my_ele = *ld_it;
		int left = 0, right = 0;
		int seen = 0;
		for (int i = 0; i < arr.size(); i++)
		{
			
			if (arr[i] == my_ele)
			{
				//First index in the array that we see this value
				if (seen == 0)
				{
					left = i;
					seen = 1;
				}
			
				//We see it again, but haven't seen all of them yet
				else if (seen < arr_deg)
				{
					seen++;
					//this is the last one, so this index is the right
					if (seen == arr_deg)
					{
						right = i;
					}
						
				}
					
				
			}
				

		}

		
		// Calc new subarray size, if it is smaller, than it is the new smallest subarray
		if ((1 + right - left) < sub_size) 
			sub_size = (1 + right - left);
	}



	return sub_size;
}


int main(void)
{
	int my_n = 0; 

	vector<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(1);

	my_n = degreeOfArray(arr);

	return 0;
}