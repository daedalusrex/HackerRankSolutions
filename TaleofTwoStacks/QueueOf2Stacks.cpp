#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

class MyQueue {

public:
	stack<int> stack_newest_on_top, stack_oldest_on_top;
	void push(int x) {
		stack_newest_on_top.push(x);

		stack_oldest_on_top = stack<int>();
		stack<int> copy_stack = stack_newest_on_top;
		while (!copy_stack.empty())
		{
			stack_oldest_on_top.push(copy_stack.top());
			copy_stack.pop();
		}
	}

	void pop() {
		stack_oldest_on_top.pop();

		stack_newest_on_top = stack<int>();
		stack<int> copy_stack = stack_oldest_on_top;
		while (!copy_stack.empty())
		{
			stack_newest_on_top.push(copy_stack.top());
			copy_stack.pop();
		}
	}

	int front() {
		return stack_oldest_on_top.top();
	}
};

int main() {
	MyQueue q1;
	int q, type, x;
	cin >> q;

	for (int i = 0; i < q; i++) {
		cin >> type;
		if (type == 1) {
			cin >> x;
			q1.push(x);
		}
		else if (type == 2) {
			q1.pop();
		}
		else cout << q1.front() << endl;
	}
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	return 0;
}
