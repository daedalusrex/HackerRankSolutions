#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
void nextMove(char player, vector <string> board) {
	//your logic here

	//Don't understand the task
	for (int i = 0; i < 29; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			if (board[i][j] == player)
			{
				cout << i << ' ' << j << endl;
			}



		}
	}
}
int main(void) {

	char player;
	vector <string> board;

	cin >> player;

	for (int i = 0; i<29; i++) {
		string s; cin >> s;
		board.push_back(s);
	}

	nextMove(player, board);

	return 0;
}
