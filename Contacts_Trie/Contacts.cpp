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

//trie data structure

class t_node
{
public:
	t_node(char c) : data(c),is_word(false), num_prefix(0), children() {};
	t_node() :data('\0'), is_word(false), num_prefix(0), children() {};

	char data;

	//get's incremented every insert, and traverse
	int num_prefix;

	//true if a word ends at this node
	bool is_word;

	vector<t_node*> children;
	//t_node * childs[26];


	t_node* ChildHasLetter(char test)
	{
		/*for (auto it : children)
		{
			if (it->data == test)
				return it;
		}
		*/

		for (vector<t_node*>::iterator it = children.begin(); it != children.end(); it++)
		{
			if ((*it)->data == test)
				return *it;
		}
		

		return NULL;
	}
};


void new_entry(t_node *root, string contact)
{
	t_node* next = root;
	t_node* old = next;
	int i = 0;

	do {
		next = old->ChildHasLetter(contact[i]);
		if (next)
		{
			next->num_prefix++;
			old = next;
			i++;
		}

	} while (next != NULL && i < contact.size());

	
	while (i < contact.size())
	{
		next = new t_node(contact[i]);
		old->children.push_back(next);

		if (i == contact.size() - 1)
			next->is_word = true;
		else
			next->num_prefix++;
		

		old = next;
		i++;
	}
}

int find_numContacts(t_node *root, string contact)
{
	int cur_names = 0;
	//traverse tree, until out of contact or out of children
	//out of children print 0
	//out of contact, print num prefix at current node

	t_node *old = root;
	t_node * current = old;
	int i = 0;

	while (current != NULL && i < contact.size())
	{
		current = old->ChildHasLetter(contact[i]);
		if (current)
		{
			cur_names = current->num_prefix;
			
		}
		
		old = current;
		i++;

	}

	if (current == NULL)
		cur_names = 0;
	else if (current->is_word)
		cur_names++;


	return cur_names;
}


int main() {
	int n;
	//Init trie
	t_node* root = new t_node();

	cin >> n;
	for (int a0 = 0; a0 < n; a0++) {
		string op;
		string contact;
		cin >> op >> contact;

		if (op == "add")
			new_entry(root, contact);

		if (op == "find")
			cout << find_numContacts(root, contact) << endl;

	}
	return 0;
}
