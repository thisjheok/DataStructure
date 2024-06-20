#include <iostream>
using namespace std;

struct node {
	node* parent;
	node* left;
	node* right;
	int key;
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
	node* search(node* node,int key,int& count) {
		if (node == NULL) {
			return NULL;
		}
		count++;
		if (node->key == key) {
			return node;
		}
		else if (node->key < key) {
			return search(node->right, key,count);
		}
		else {
			return search(node->left, key,count);
		}
	}
	void insert(int x) {
		int cnt = 0;
		int cnt2 = 0;
		if (search(root, x, cnt2) !=NULL) {
			return;
		}
		node* newNode = new node(x);
		node* curNode = root;
		node* parNode = NULL;
		if (root == NULL) {
			root = newNode;
			cout << cnt << endl;
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
		if (root == nullptr) {
			cout << "empty" << endl;
			return;
		}
		search(root, x, cnt);
		cout << cnt << endl;
	}
	void printParent(int x) {
		int cnt = 0;
		node* findNode = search(root, x, cnt);
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
		node* findNode = search(root, x, cnt);
		if (findNode == NULL) {
			cout << -1 << endl;
			return;
		}
		if (findNode->right == NULL) {
			cout << -2 << endl;
			return;
		}
		cout << findNode->right->key << endl;
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
				int k;
				cin >> k;
				bst.insert(k);
			}
			else if (cmd == "search") {
				int k;
				cin >> k;
				bst.printSearch(k);
			}
			else if (cmd == "parent") {
				int k;
				cin >> k;
				bst.printParent(k);
			}
			else if (cmd == "child") {
				int k;
				cin >> k;
				bst.printChild(k);
			}
		}
	}
}