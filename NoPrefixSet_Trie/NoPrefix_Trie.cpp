#include <cmath>
#include <string>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

//trie data structure
class t_node
{
private:
	//chars are limited to 10 'a' - 'j'
	t_node * ninos[10];

public:
	t_node(char c) : data(c), is_word(false), num_prefix(0), ninos{ NULL } {};
	t_node() :data('\0'), is_word(false), num_prefix(0), ninos{ NULL } {};
	//char in this node
	char data;
	//get's incremented every insert
	int num_prefix;
	//true if a word ends at this node
	bool is_word;

	//adds a new childe node with char already present
	void add_child(t_node* new_child)
	{
		//protect against bad input
		if (!new_child || new_child->data < 'a' || new_child->data > 'j')
			return;

		ninos[new_child->data - 'a'] = new_child;
	}

	//returns node of letter, or false
	t_node* ChildHasLetter(char test)
	{
		if(test < 'a' || test > 'j')
			return NULL;

		return ninos[test - 'a'];
	}
};


bool new_entry(t_node *root, string entry_to_add)
{
	t_node* next = root;
	t_node* old = next;
	int i = 0;

	//Traverse while there are prefixes in current tree
	do {
		next = old->ChildHasLetter(entry_to_add[i]);
		if (next)
		{
			if (next->is_word)
			{
				cout << "BAD SET\n" << entry_to_add << endl;
				return false;
			}
				
			next->num_prefix++;
			old = next;
			i++;
		}

	} while (next != NULL && i < entry_to_add.size());


	if (i == entry_to_add.size() && next->num_prefix > 1)
	{
		cout << "BAD SET\n" << entry_to_add << endl;
		return false;
	}


	//Reached end of current info in tree, but more chars to add
	while (i < entry_to_add.size())
	{
		next = new t_node(entry_to_add[i]);
		old->add_child(next);

		if (i == entry_to_add.size() - 1)
			next->is_word = true;
		else
			next->num_prefix++;


		old = next;
		i++;
	}
	return true;
}


int main() {
	int n;
	//Init trie
	t_node* root = new t_node();
	
	cin >> n;
	for (int a0 = 0; a0 < n; a0++) {
		string name;
		cin >> name;

		if (!new_entry(root, name))
			return 0;

	}

	//print good set
	cout << "GOOD SET" << endl;
	return 0;
}
