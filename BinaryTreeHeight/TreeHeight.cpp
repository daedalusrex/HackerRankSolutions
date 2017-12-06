#include <iostream>
#include <cstddef>


#include <queue>

using namespace std;

class Node {
public:
	int data;
	Node *left;
	Node *right;
	Node(int d) {
		data = d;
		left = NULL;
		right = NULL;
	}
};

class Solution {
public:
	Node * insert(Node* root, int data) {
		if (root == NULL) {
			return new Node(data);
		}
		else {
			Node* cur;
			if (data <= root->data) {
				cur = insert(root->left, data);
				root->left = cur;
			}
			else {
				cur = insert(root->right, data);
				root->right = cur;
			}

			return root;
		}
	}


	/*The tree node has data, left child and right child
	class Node {
	int data;
	Node* left;
	Node* right;
	};

	*/
	int height(Node* root) {
		// Write your code here.

		//BFS
		//build new tree with height do another search ??
		//DFS
		//could also change the data in each node, free thing
		//save greatest height as going through it?	

		if (root == NULL)
			return 0;

		queue<Node*> search;
		search.push(root);
		int max_height = 0;
		root->data = 0;

		while (!search.empty())
		{
			Node* current = search.front();
			search.pop();

			if (current->data > max_height)
				max_height = current->data;


			if (current->left != NULL) {
				current->left->data = current->data + 1;
				search.push(current->left);
			}
			
			if (current->right != NULL) {
				current->right->data = current->data + 1;
				search.push(current->right);
			}

		}

		return max_height;
	}
}; //End of Solution

int main() {
	Solution myTree;
	Node* root = NULL;
	int t;
	int data;

	cin >> t;

	while (t-- > 0) {
		cin >> data;
		root = myTree.insert(root, data);
	}
	int height = myTree.height(root);
	cout << height;

	return 0;
}

