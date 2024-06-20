#include <iostream>
using namespace std;

struct node {
	node* left;
	node* right;
	node* parent;
	int key;
	node(int key) {
		this->key = key;
		left = right = parent = NULL;
	}
};

class BST {
private:
	node* root;
public:
	BST() {
		root = NULL;
	}
	node* search(node* node, int key) {
		if (node == NULL) {
			return NULL;
		}
		if (node->key == key) {
			return node;
		}
		else if (node->key < key) {
			return search(node->right, key);
		}
		else {
			return search(node->left, key);
		}
	}
	void findMax(node* node, int& count, int& result, int k) {
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
			else {
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
		if (parNode == NULL) {//부모가 없을 때
			root = childNode;
			if (childNode != NULL) {
				root->parent = NULL;
			}
		}
		else if (delNode==parNode->left) {//부모의 왼쪽 노드가 델노드일 때
			parNode->left = childNode;
			if (childNode != NULL) {
				childNode->parent = parNode;
			}
		}
		else {//부모의 오른쪽 노드가 델노드일 때
			parNode->right = childNode;
			if (childNode != NULL) {
				childNode->parent = parNode;
			}
		}
		delete delNode;
	}
	void Max(int k) {
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
				bst.Max(k);
			}
		}
	}
}