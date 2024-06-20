#include <iostream>
using namespace std;

struct node {
	int key;
	node* parent;
	node* left;
	node* right;
	node(int key) {
		this->key = key;
		parent = left = right = NULL;
	}
};

class BST {
private:
	node* root;
public:
	BST() {
		root = NULL;
	}
	node* search(node* node, int k) {
		if (node == NULL) {
			return NULL;
		}
		if (node->key == k) {
			return node;
		}
		else if (node->key < k) {
			return search(node->right, k);
		}
		else {
			return search(node->left, k);
		}
	}

	void findMax(node* node,int& count,int& result,int k) {
		if (node == NULL) {
			return;
		}

		findMax(node->right, count, result, k);
		count++;
		if (count == k) {
			result = node->key;
			return;
		}
		findMax(node->left, count, result, k);
	}

	void insert(int x) {
		node* newNode = new node(x);
		if (search(root, x) != NULL) {
			return;
		}
		if (root == NULL) {
			root = newNode;
			return;
		}
		node* curNode = root;
		node* parNode = NULL;

		while (curNode != NULL) {
			parNode = curNode;
			if(curNode->key < x){
				curNode = curNode->right;
			}
			else if (curNode->key > x) {
				curNode = curNode->left;
			}
		}
		newNode->parent = parNode;

		if (parNode->key < x) {
			parNode->right = newNode;
		}
		else {
			parNode->left = newNode;
		}
	}

	void remove(int x) {
		node* delNode = search(root, x);
		if (delNode == NULL) {
			return;
		}
		node* parNode = delNode->parent;
		node* childNode;
		if (delNode->left == NULL && delNode->right == NULL) {
			childNode = NULL;
		}
		else if (delNode->left != NULL && delNode->right == NULL) {
			childNode = delNode->left;
		}
		else if (delNode->left == NULL && delNode->right != NULL) {
			childNode = delNode->right;
		}
		else {
			childNode = delNode->right;
			while (childNode->left != NULL) {
				childNode = childNode->left;
			}
			delNode->key = childNode->key;
			delNode = childNode;
			parNode = delNode->parent;
			childNode = delNode->right;
		}

		if (parNode == NULL) {
			root = childNode;
			if (childNode != NULL) {
				childNode->parent = NULL;
			}
		}
		else if (delNode == parNode->left) {
			parNode->left = childNode;
			if (childNode != NULL) {
				childNode->parent = parNode;
			}
		}
		else if (delNode == parNode->right) {
			parNode->right = childNode;
			if (childNode != NULL) {
				childNode->parent = parNode;
			}
		}
		delete delNode;
	}
	void max(int k) {
		int count = 0;
		int result = -1;
		findMax(root, count, result, k);
		if (result != -1) {
			cout << result << endl;
		}
	}
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		BST bst;
		for (int j = 0; j < n; j++) {
			string cmd;
			cin >> cmd;
			if (cmd == "insert") {
				int x;
				cin >> x;
				bst.insert(x);
			}
			else if (cmd == "delete") {
				int x;
				cin >> x;
				bst.remove(x);
			}
			else if (cmd == "max") {
				int k;
				cin >> k;
				bst.max(k);
			}
		}
	}
}
/*
1
13
insert 10
insert 60
max 1
delete 60
insert 18
max 2
insert 7
max 3
insert 3
insert 9
max 2
delete 7
max 4
*/