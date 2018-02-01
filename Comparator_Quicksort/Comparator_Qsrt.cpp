#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <string.h>
#include "Comparator_Qsrt.h"
using namespace std;

struct Player {
	string name;
	int score;
};

//returns true if left is greater than right
bool left_greater(Player &left, Player &right)
{
	if (left.score > right.score) return true;
	if (left.score == right.score)
		if (strcmp(left.name.c_str(), right.name.c_str()) <= 0)
			return true;

	return false;
}


void quicksort(vector<Player> &players, int left, int right)
{
	if (left >= right) return;
	
	int i = left;
	int j = right - 1;

	Player partition = players[right];

	while (i < j)
	{
		while (left_greater(players[i], partition) && i < (right-1))
			i++;

		while (left_greater(partition, players[j]) && j > left)
			j--;
		

		if(i < j && left_greater(players[j], players[i]))
			swap(players[i], players[j]);
	}
	
	//replace partition in correct location
	if (left_greater(partition, players[i]))
		swap(players[i], players[right]);
	else
		i = right;

	quicksort(players, left, i-1);
	quicksort(players, i+1, right);
}


vector<Player> comparator(vector<Player> players) {
	quicksort(players, 0, players.size() - 1);
	//easiest trick would be to sort() array
	return players;
}

int main() {

	int n;
	cin >> n;
	vector< Player > players;
	string name;
	int score;
	for (int i = 0; i < n; i++) {
		cin >> name >> score;
		Player p1;
		p1.name = name, p1.score = score;
		players.push_back(p1);
	}

	vector<Player > answer = comparator(players);
	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i].name << " " << answer[i].score << endl;
	}
	return 0;
}
