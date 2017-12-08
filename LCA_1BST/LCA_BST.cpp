
#include <iostream>
#include <vector>

using namespace std;

/*
Node is defined as
*/
typedef struct node
{
int data;
node *left;
node *right;

node(int d) : data(d), left(NULL), right(NULL) {}
}node;



int main(void)
{
	vector<node> mynodes;
	for (int i = 0; i <= 7; i++)
	{
		mynodes.push_back(node(i));
	}
	
	

	return 0;
}


bool AmHasDescendant(node* root, int v1, int v2)
{
	if (root == NULL)
		return false;

	if (root->data == v1 || root->data == v2)
		return true;

	if (AmHasDescendant(root->left, v1, v2))
		return true;

	if (AmHasDescendant(root->right, v1, v2))
		return true;

	return false;

}

node *lca(node *root, int v1, int v2)
{
	//definition of LCA 
	//if(detected descendent left and right) or I am descendent and detect one
	//return me
	//else search left branch
	//else search right branch

	if (root == NULL)
		return NULL;

	bool lefthas = AmHasDescendant(root->left, v1, v2);
	bool righthas = AmHasDescendant(root->right, v1, v2);
	

	if ((root->data == v1 || root->data == v2)
		&& (lefthas || righthas))
		return root;

	if (lefthas && righthas)
		return root; 


	if (lefthas)
		return lca(root->left, v1, v2);

	if (righthas)
		return lca(root->left, v1, v2);


	return NULL;

	

	//maybe can use properties of binary search tree to be optimal



}