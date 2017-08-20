/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as:
struct Node {
int data;
struct Node* next;
}
*/


struct Node {
	int data;
	struct Node* next;
};

#include <map>
#include <vector>
#include <stdlib.h>

using namespace std;


bool has_cycle(Node* head) {
	// Complete this function
	// Do not write the main method

	if (head == NULL)
		return false;


	map<Node*, bool> SeenNodes;
	vector<Node*> search;
	search.push_back(head);

	while (!search.empty())
	{
		Node* step = search.back();
		search.pop_back();

		if (SeenNodes.count(step) == 1)
			return true;

		SeenNodes.insert(make_pair(step, true));

		if (step->next != NULL)
			search.push_back(step->next);
	}

	return false;

}