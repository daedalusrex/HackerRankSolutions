#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

////for heap debugging
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

using namespace std;

/**
* Given a binary tree, return the level order traversal of its nodes' values.
* (ie, from left to right, level by level).
*
* For example:
* Given binary tree
*     3
*    / \
*   9  20
*  /   / \
*  1  15   7
* return its level order traversal as:
* [
*   [3],
*   [9,20],
*   [15,7]
* ]
*/

struct node
{
	int data;
	node* left;
	node* right;

	node() : data(0), left(NULL), right(NULL) {};
	node(int datum) : left(NULL), right(NULL) { data = datum; };

};


//Deletes entire tree
void cleantree_postorder(node* root)
{
	if (root == NULL)
		return;

	cleantree_postorder(root->left);
	cleantree_postorder(root->right);

	delete root;

	return;

}


void printout_parentlevel(queue<node*> &parents)
{
	if (parents.empty())
		return;

	queue<node*> children;
	while (!parents.empty())
	{
		node* vader = parents.front();
		parents.pop();

		vader->left != NULL ? children.push(vader->left) : NULL;
		vader->right != NULL ? children.push(vader->right) : NULL;

		cout << vader->data << " ";
	}

	cout << endl;

	return printout_parentlevel(children);

}


void printtreelevelv2(node* root)
{
	if (root == NULL)
		return;

	queue<node*> toplevel;
	toplevel.push(root);

	//recursive version
	printout_parentlevel(toplevel);


	//iterative Data structure version
	queue<node*> top2;
	top2.push(root);

	queue < queue<node*>> finalarray;

	while (!top2.empty())
	{
		queue<node*> children;
		queue<node*> parents(top2);
		queue<node*> saved;
		
		while (!parents.empty())
		{
			node* vader = parents.front();
			parents.pop();

			vader->left != NULL ? children.push(vader->left) : NULL;
			vader->right != NULL ? children.push(vader->right) : NULL;

			//cout << vader->data << " ";
			saved.push(vader);
		}

		finalarray.push(saved);

		top2 = children;

		
	}

	
	return;
	//queue<node*> levsearch;
	//search.push(root);
	//levsearch.push(root);
	//

	//
	//queue<node*>  nextlevel;
	//node* lastlevelnode = nextlevel.front();

	//(lastlevelnode->left != NULL) ? nextlevel.push(lastlevelnode->left) : NULL;
	//(lastlevelnode->right != NULL) ? nextlevel.push(lastlevelnode->right) : NULL;

	//
	////Traverse Queue
	//cout << "normal search";
	//while (!search.empty())
	//{
	//	//Print This Level
	//	node* current = search.front();
	//	search.pop();


	//	cout << current->data << " ";

	//	(current->left != NULL) ? search.push(current->left) : NULL;
	//	(current->right != NULL) ? search.push(current->right) : NULL;
	//	
	//}


}


//Need to add tree input, as a data structure, and then do the work
int main(void)
{

	//build this sample tree
	node* root= new node(3);
	root->left = new node(9);
	root->left->left = new node(1);
	root->right = new node(20);
	root->right->left = new node(15);
	root->right->right = new node(7);
	


	printtreelevelv2(root);

	
	cleantree_postorder(root);
	
	int pause;
	cin >> pause;
	return 0;
}




 //vector<vector<int>> printtree(node &mytree)
 //{
	// //input guard
	// if (mytree == NULL)
	//	 return NULL;

	// //iteration
	// //queue - this iteration, im on same level
	// //enqueu children

	// //build up lists 


	// vector<vector<int>> toplist;
	// queue<node*> children;
	// children.push(&mytree)
	//	 int level = 0;
	// vector<int> levelsizes;
	// levelsizes.push(1);

	// while (children.size() != 0)
	// {
	//	 node* current = children.pop();

	//	 vector<int> layer = new vector<int>;
	//	 layer.pushback(current->data);


	//	 if (current->left != NULL)
	//	 {
	//		 levelsizes.at(level)++;
	//		 children.push_back(current->left);
	//	 }

	//	 if (current->right != NULL)
	//	 {
	//		 layerchildren++
	//			 children.push_back(current->right);
	//	 }


	//	 level++;


	//	 toplist.insert(layer);
	// }

 //}




