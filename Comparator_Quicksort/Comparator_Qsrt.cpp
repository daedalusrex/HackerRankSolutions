#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

struct Player {
	string name;
	int score;
};


//returns true if left is less than right
bool less(Player &left, Player &right)
{
	// < 0 implies ptr1 is less
	// (strcmp ==0 ) implies equality
	// > 0 implies ptr 2 is less

	if (left.score < right.score) return true;
	if (left.score == right.score)
		if (strcmp(left.name.c_str(), right.name.c_str()) <= 0)
			return true;


	return false;
}

vector<Player> comparator(vector<Player> players) {


	//use quick sort, and maybe an extra comparator function

	//recursively partition and then quicksort each half


	


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
