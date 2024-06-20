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
	node* search(node* curnode, int& count,int k) {
		if (curnode == NULL) {
			return NULL;
		}
		count++;
		if (curnode->key == k) {
			return curnode;
		}
		else if (curnode->key < k) {
			return search(curnode->right, count, k);
		}
		else {
			return search(curnode->left, count, k);
		}
	}

	void insert(int x) {
		int cnt = 0;
		int cnt2 = 0;
		if (search(root, cnt2, x) != NULL) {
			return;
		}
		node* newNode = new node(x);
		if (root == NULL) {
			root = newNode;
			cout << cnt << endl;
			return;
		}
		node* curNode = root;
		node* parNode = NULL;

		while (curNode != NULL) {
			parNode = curNode;
			cnt++;
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
		cout << cnt << endl;
	}

	void printSearch(int x) {
		int cnt = 0;
		if (root == NULL) {
			cout << "empty" << endl;
			return;
		}
		search(root, cnt, x);
		cout << cnt << endl;
	}

	void printParent(int x) {
		int cnt = 0;
		node* findNode = search(root, cnt, x);

		if (findNode == NULL){
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