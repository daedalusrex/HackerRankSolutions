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

using namespace std;

int SumVector(vector<int> &v)
{
	int sum = 0;
	for (auto &n : v)
		sum += n;

	return sum;
}


class BlockStack
{
public:
	BlockStack(vector<int> &v)
		: vec(v)
	{
		sum = SumVector(vec);
	}

	void RemoveTopBlock()
	{
		if (StackEmpty())
			return;

		sum -= vec.front();
		vec.erase(vec.begin());

		//maybe verify sum here
	}
	
	int GetHeight() { return sum; }
	int GetNumBlocks() { return vec.size(); }
	bool StackEmpty() { return vec.empty(); }

private:
	vector<int> vec;
	int sum;
};


bool StacksAreEqual(BlockStack &B1, BlockStack &B2, BlockStack &B3)
{
	return ((B1.GetHeight() == B2.GetHeight()) && (B2.GetHeight() == B3.GetHeight()));
}

bool StacksAreEmpty(BlockStack &B1, BlockStack &B2, BlockStack &B3)
{
	return (B1.StackEmpty() && B2.StackEmpty() && B3.StackEmpty());
}

BlockStack& TallestStack(BlockStack &B1, BlockStack &B2, BlockStack &B3)
{
	if (B1.GetHeight() > B2.GetHeight() && B1.GetHeight() > B3.GetHeight())
		return B1;

	if (B2.GetHeight() > B3.GetHeight())
		return B2;

	return B3;

}

int main() {
	int n1;
	int n2;
	int n3;
	cin >> n1 >> n2 >> n3;
	vector<int> h1(n1);
	for (int h1_i = 0; h1_i < n1; h1_i++) {
		cin >> h1[h1_i];
	}
	vector<int> h2(n2);
	for (int h2_i = 0; h2_i < n2; h2_i++) {
		cin >> h2[h2_i];
	}
	vector<int> h3(n3);
	for (int h3_i = 0; h3_i < n3; h3_i++) {
		cin >> h3[h3_i];
	}

	//while (!stacks equal)
		//remove highest

	BlockStack B1(h1);
	BlockStack B2(h2);
	BlockStack B3(h3);

	
	while (!StacksAreEmpty(B1, B2, B3) && !StacksAreEqual(B1, B2, B3))
	{
		//remove highest
		BlockStack &ref = TallestStack(B1, B2, B3);
		ref.RemoveTopBlock();
	}


	//output any since they should be equal or empty
	cout << B1.GetHeight();


	return 0;
}
