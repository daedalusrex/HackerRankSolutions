#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector> 
#include <list>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cassert>

using namespace std; 



int main()
{
	int N, I;
	cin >> N >> I;
	vector<vector<int> > pairs(N);
	for (int i = 0; i < I; ++i) {
		int a, b;
		cin >> a >> b;
		pairs[a].push_back(b);
		pairs[b].push_back(a);
	}

	long long result = 0;

	/** Write code to compute the result using N,I,pairs **/
	

	vector<bool> visited(N, false);
	vector<vector<int>> countries;

	//for (vector<bool>::iterator it = visited.begin(); it != visited.end(); it++)	
	//{
		//If current node is already visited, continue to the next one
		//if (*it == true)
			//continue;
		//else
	for(int current_astro = 0; current_astro < visited.size(); current_astro++)
	{
		if (!visited[current_astro])
		{
			vector<int> new_country;
			vector<int> search;
			search.push_back(current_astro);

			while (!search.empty())
			{
				int cur_node = search.back();
				new_country.push_back(cur_node);
				visited[cur_node] = true;
				search.pop_back();

				for (auto pair_it : pairs[cur_node])
				{
					if (!visited[pair_it])
					{
						search.push_back(pair_it);
						visited[pair_it] = true;
					}
						
				}

				//Add children to search, if unvisted
				/*
				for (vector<int>::const_reverse_iterator rit = pairs[cur_node].rbegin();
														rit != pairs[cur_node].rend(); rit++)
				{
					if (!visited[*rit])
						search.push_back(*rit);
				}
				*/
			
			}

			countries.push_back(new_country);
		}
	}

	int numcountries = countries.size();


	long new_sum = 0;
	long new_result = 0;

	for (auto it : countries)
	{
		new_result += new_sum * it.size();
		new_sum += it.size();

	}

	/* //Not correct 
	for (vector<vector<int>>::iterator nation = countries.begin(); nation != countries.end(); nation++)
	{
		int foreign_pairs = 0;
		for (vector<int>::iterator citz = nation->begin(); citz != nation->end(); citz++)
		{
			for (vector<vector<int>>::iterator othernation = countries.begin(); othernation != countries.end(); othernation++)
			{
				if (othernation != nation)
					foreign_pairs += othernation->size();
			}
		}

		nation->clear();
		result += foreign_pairs;
	}
	*/

	cout << new_result << endl;
	return 0;
}
