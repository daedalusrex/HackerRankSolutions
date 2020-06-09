#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
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
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

//https://www.hackerrank.com/challenges/merging-communities/problem
/*People connect with each other in a social network. A connection between Person  and Person  is represented as . When two persons belonging to different communities connect, the net effect is the merger of both communities which  and  belongs to.

At the beginning, there are  people representing  communities.Suppose personand connectedand laterand connected, then, , and will belong to the same community.

There are two type of queries :

communities containing personand merged(if they belong to different communities).

print the size of the community to which person  belongs.

Input Format

The first line of input will contain integersand, i.e.the number of peopleand the number of queries.
The next  lines will contain the queries.
*/

/*
Sample Input

3 6
Q 1
M 1 2
Q 2
M 2 3
Q 3
Q 2
Sample Output

1
2
3
3
*/
using namespace std;

class community {
public:
	community() : valid(true) {};
	unordered_set<unsigned int> members;
	//When communities are merged only one remains valid
	bool valid;
	unsigned int size() { return members.size(); }
};

void How_Many_Members_In_Community(unsigned int person, unsigned int peoplecount, community* group_communities, unordered_map<unsigned int, community*> &people_map)
{
	cout << people_map[person]->size() << endl;
}

void Merge_Communities_Of_People(unsigned int personA, unsigned int personB, unsigned int peoplecount, community* group_communities, unordered_map<unsigned int, community*> &people_map)
{
	//Do nothing if they are part of the same community (represented by identical pointers which are maintained during merge
	if (people_map[personA] == people_map[personB])
		return;

	//Quick Optimization
	community* Larger = people_map[personA];
	community* Smaller = people_map[personB];
	if (Smaller->size() > Larger->size())
	{
		Larger = Smaller;
		Smaller = people_map[personA];
	}
		

	//Place all people in smaller community into larger one
	//Simultaneosly Update pointer mapping in original structure
	for (auto it = Smaller->members.begin(); it != Smaller->members.end(); it++)
	{
		people_map[*it] = Larger;
		Larger->members.insert(*it);
	}
	Smaller->valid = false;



}


int main(void) {

	unsigned int N, Q;

	cin >> N >> Q;


	community* group_communities = new community[N+1];

	//an array of pointers to communities
	//community** people = new community*[N];
	
	unordered_map<unsigned int, community*> people_map;
	//might have been better to create an unordered_map<int,*community>

	//fill with increasing number 1 to N
	//iota(people, people+N, 1);

	//Initially each person has their own community
	for (unsigned int i = 1; i <= N; i++)
	{
		//people[i] = &group_communities[i];
		people_map.insert(make_pair(i, &group_communities[i]));
		group_communities[i].members.insert(i);
	}


	for (int i = 0; i < Q; i++)
	{
		char query; 
		cin >> query;
		int entry1, entry2;
		switch (query) {
		case 'Q':
			cin >> entry1;
			How_Many_Members_In_Community(entry1,N, group_communities, people_map);
			break;
		case 'M':
			cin >> entry1>> entry2;
			Merge_Communities_Of_People(entry1, entry2,N, group_communities, people_map);
			break;
		default:
			break;
		}
	}

	//create first the container of communities, size N. Each one has a number starting from 1

	//This container should be a map from community index to a the group of people in said community

	//Also there must be a way to 

	delete[] group_communities;
	


	return 0;

}