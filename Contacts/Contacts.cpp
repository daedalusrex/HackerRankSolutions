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

/* 
We're going to make our own Contacts application! The application must perform two types of operations:

add name, where  is a string denoting a contact name. This must store  as a new contact in the application.
find partial, where  is a string denoting a partial name to search the application for. It must count the number of contacts starting with  and print the count on a new line.
Given  sequential add and find operations, perform each operation in order.
*/



//trie data structure
class trie_node
{
private:
    //chars are limited to 26 'a' - 'z'
    trie_node* children[26];

public:
    trie_node(char c) : data(c), is_contact(false), num_prefix(0), children{ NULL } {};
    trie_node() :data('\0'), is_contact(false), num_prefix(0), children{ NULL } {};
    //character in this node
    char data;
    //number of contacts with this node as part of prefix, incremented every insert
    int num_prefix;
    //true if a word ends at this node
    bool is_contact;

    //adds a new child node, unless there already is one, and returns it
    trie_node* add_new_child_char(char new_char)
    {       
        //protect against bad input
        if (new_char < 'a' || new_char > 'z') return NULL;
        //prevent overwriting, as input was guaranteed to have all unique entries
        if (children[new_char - 'a'] != NULL) return NULL;
        trie_node* new_child = new trie_node(new_char);
        children[new_child->data - 'a'] = new_child;
        return new_child;
    }

    //returns ptr to node with letter, or null if it does not have a child node with that letter
    trie_node* get_branching_char(char test)
    {
        if (test < 'a' || test > 'z')
            return NULL;
        return children[test - 'a'];
    }
};

class trie {

private:
    trie_node* root;
    int num_entries;

public:
    trie() : root(new trie_node), num_entries(0) {};

    void insert_unique_entry(string entry_to_add)
    {
        trie_node* next = root;
        trie_node* old = next;
        int entry_char_index = 0;

        //Traverse while there are prefixes in current tree
        do {
            next = old->get_branching_char(entry_to_add[entry_char_index]);
            if (next)
            {
                next->num_prefix++;
                old = next;
                entry_char_index++;
            }
        } while (next != NULL && entry_char_index < entry_to_add.size());

        //Reached end of current entries in tree, but still more chars to add, create new branch nodes
        while (entry_char_index < entry_to_add.size())
        {
            next = old->add_new_child_char(entry_to_add[entry_char_index]);
            if (entry_char_index == entry_to_add.size() - 1)
                next->is_contact = true;
            else
                next->num_prefix++;

            old = next;
            entry_char_index++;
        }
        return;
    }

    int get_num_contacts_from_partial(string partial) {
        trie_node* stem = root;
        for (int i = 0; i < partial.size(); i++) {
            stem = stem->get_branching_char(partial[i]);
            if (!stem)
                return 0;
        }
        if (stem->is_contact)
            return stem->num_prefix + 1;
        return stem->num_prefix;
    }
};



/*
 * Complete the contacts function below.
 */
vector<int> contacts(vector<vector<string>> queries) {
    
    vector<int> results; 
    trie contact_trie;

    for (int r = 0; r < queries.size(); r++) {
        //Command Process
        if (queries[r][0] == "add")
            contact_trie.insert_unique_entry(queries[r][1]);
        else if (queries[r][0] == "find")
            results.push_back(contact_trie.get_num_contacts_from_partial(queries[r][1]));
    }

    return results;
}

int main()
{
    ofstream fout("contact_out.txt");
    //original
    //ofstream fout(getenv("OUTPUT_PATH"));

    int queries_rows;
    cin >> queries_rows;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
        queries[queries_row_itr].resize(2);

        for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}