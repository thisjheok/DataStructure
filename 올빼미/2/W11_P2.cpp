#include <iostream>
#include <string>
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
		if (node == NULL || count >= k) {
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
		if (search(root, x) != NULL) {
			return;
		}
		node* newNode = new node(x);
		node* curNode = root;
		node* parNode = NULL;

		if (root == nullptr) {
			root = newNode;
			return;
		}

		while (curNode != NULL) {
			parNode = curNode;
			if (curNode->key < x) {
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
		node* delNode = search(root,x);
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
				root->parent = NULL;
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

	void Max(int k) {
		int result = -1;
		int count = 0;
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
		BST bst;
		int N;
		cin >> N;
		for (int j = 0; j < N; j++) {
			string s;
			cin >> s;
			if (s == "insert") {
				int key;
				cin >> key;
				bst.insert(key);
			}
			else if (s == "delete") {
				int key;
				cin >> key;
				bst.remove(key);
			}
			else if (s == "max") {
				int k;
				cin >> k;
				bst.Max(k);
			}
		}
	}
}