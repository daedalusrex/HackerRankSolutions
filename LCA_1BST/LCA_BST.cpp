
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


/* C++ Program to find LCA of n1 and n2 using one traversal of Binary Tree */
#include <iostream> 

using namespace std;

// A Binary Tree Node 
struct Node
{
    struct Node* left, * right;
    int key;
};




//Example code copied from: https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/

/*Binary Search Tree
/* Function to find LCA of n1 and n2. The function assumes that both
   n1 and n2 are present in BST */
/*
struct node* lca(struct node* root, int n1, int n2)
{
    if (root == NULL) return NULL;

    // If both n1 and n2 are smaller than root, then LCA lies in left 
    if (root->data > n1 && root->data > n2)
        return lca(root->left, n1, n2);

    // If both n1 and n2 are greater than root, then LCA lies in right 
    if (root->data < n1 && root->data < n2)
        return lca(root->right, n1, n2);

    return root;
} 
*/

	//Good explanation
// Utility function to create a new tree Node 
Node* newNode(int key)
{
    Node* temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// This function returns pointer to LCA of two given values n1 and n2. 
// This function assumes that n1 and n2 are present in Binary Tree 
struct Node* findLCA(struct Node* root, int n1, int n2)
{
    // Base case 
    if (root == NULL) return NULL;

    // If either n1 or n2 matches with root's key, report 
    // the presence by returning root (Note that if a key is 
    // ancestor of other, then the ancestor key becomes LCA 
    if (root->key == n1 || root->key == n2)
        return root;

    // Look for keys in left and right subtrees 
    Node* left_lca = findLCA(root->left, n1, n2);
    Node* right_lca = findLCA(root->right, n1, n2);

    // If both of the above calls return Non-NULL, then one key 
    // is present in once subtree and other is present in other, 
    // So this node is the LCA 
    if (left_lca && right_lca)  return root;

    // Otherwise check if left subtree or right subtree is LCA 
    return (left_lca != NULL) ? left_lca : right_lca;
}


/*
// Driver program to test above functions 
int main()
{
    // Let us create binary tree given in the above example 
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    cout << "LCA(4, 5) = " << findLCA(root, 4, 5)->key;
    cout << "nLCA(4, 6) = " << findLCA(root, 4, 6)->key;
    cout << "nLCA(3, 4) = " << findLCA(root, 3, 4)->key;
    cout << "nLCA(2, 4) = " << findLCA(root, 2, 4)->key;
    return 0;
}
*/


//Other Approach:, Two vectors
/// C++ Program for Lowest Common Ancestor in a Binary Tree
//// A O(n) solution to find LCA of two given values n1 and n2 
//#include <iostream> 
//#include <vector> 
//
//using namespace std;
//
//// A Binary Tree node 
//struct Node
//{
//    int key;
//    struct Node* left, * right;
//};
//
//// Utility function creates a new binary tree node with given key 
//Node* newNode(int k)
//{
//    Node* temp = new Node;
//    temp->key = k;
//    temp->left = temp->right = NULL;
//    return temp;
//}
//
//// Finds the path from root node to given root of the tree, Stores the 
//// path in a vector path[], returns true if path exists otherwise false 
//bool findPath(Node * root, vector<int> & path, int k)
//{
//    // base case 
//    if (root == NULL) return false;
//
//    // Store this node in path vector. The node will be removed if 
//    // not in path from root to k 
//    path.push_back(root->key);
//
//    // See if the k is same as root's key 
//    if (root->key == k)
//        return true;
//
//    // Check if k is found in left or right sub-tree 
//    if ((root->left && findPath(root->left, path, k)) ||
//        (root->right && findPath(root->right, path, k)))
//        return true;
//
//    // If not present in subtree rooted with root, remove root from 
//    // path[] and return false 
//    path.pop_back();
//    return false;
//}
//
//// Returns LCA if node n1, n2 are present in the given binary tree, 
//// otherwise return -1 
//int findLCA(Node * root, int n1, int n2)
//{
//    // to store paths to n1 and n2 from the root 
//    vector<int> path1, path2;
//
//    // Find paths from root to n1 and root to n1. If either n1 or n2 
//    // is not present, return -1 
//    if (!findPath(root, path1, n1) || !findPath(root, path2, n2))
//        return -1;
//
//    /* Compare the paths to get the first different value */
//    int i;
//    for (i = 0; i < path1.size() && i < path2.size(); i++)
//        if (path1[i] != path2[i])
//            break;
//    return path1[i - 1];
//}
