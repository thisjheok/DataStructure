#include <iostream>
using namespace std;

struct node {
	int key;
	node* left;
	node* right;
	node* parent;

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
	node* search(node* node, int& count, int key) {
		if (node == NULL) {
			return NULL;
		}
		count++;
		if (node->key == key) {
			return node;
		}
		else if (node->key < key) {
			return search(node->right, count, key);
		}
		else {
			return search(node->left, count, key);
		}
	}
	void insert(int x) {
		node* newNode = new node(x);
		int cnt = 0;
		int cnt2 = 0;
		if (search(root, cnt2, x) != NULL) {
			return;
		}
		node* curNode = root;
		node* parNode = NULL;
		if (root == nullptr) {
			root = newNode;
			cout << cnt << endl;
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
			cnt++;
		}
		newNode->parent = parNode;

		if (parNode->key < x) {
			parNode->right = newNode;
		}
		else {
			parNode->left = newNode;
		}
		cout << cnt << endl;
	}

	void printSearch(int x) {
		int cnt = 0;
		if (root == NULL) {
			cout << "empty" << endl;
		}
		else {
			search(root, cnt, x);
			cout << cnt << endl;
		}
	}

	void printParent(int x) {
		int cnt = 0;
		node* findNode = search(root, cnt, x);
		if (findNode == NULL) {
			cout << -1 << endl;
			return;
		}
		if (findNode->parent == NULL) {
			cout << -2 << endl;
			return;
		}
		cout << findNode->parent->key << endl;
	}

	void printChild(int x) {
		int cnt = 0;
		node* findNode = search(root, cnt, x);
		if (findNode == NULL) {
			cout << -1 << endl;
			return;
		}
		if (findNode->left == NULL) {
			cout << -2 << endl;
			return;
		}
		cout << findNode->left->key << endl;
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
			else if (cmd == "search") {
				int x;
				cin >> x;
				bst.printSearch(x);
			}
			else if (cmd == "parent") {
				int x;
				cin >> x;
				bst.printParent(x);
			}
			else if (cmd == "child") {
				int x;
				cin >> x;
				bst.printChild(x);
			}
		}
	}
}