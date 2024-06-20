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
	node* search(node* node, int key,int& cnt) {
		if (node == NULL) {
			return NULL;
		}
		if (node->key == key) {
			cnt++;
			return node;
		}
		else if (node->key < key) {
			cnt++;
			return search(node->right, key,cnt);
		}
		else {
			cnt++;
			return search(node->left, key,cnt);
		}
	}
	void insert(int key) {
		int cnt = 0;
		int cnt2 = 0;
		node* newNode = new node(key);
		if (search(root, key,cnt2) != NULL) {
			return;
		}
		node* curNode = root;
		node* parNode = NULL;


		if (root == NULL) {
			root = newNode;
			cout << cnt << endl;
			return;
		}

		while (curNode != NULL) {
			cnt++;
			parNode = curNode;
			if (curNode->key < key) {
				curNode = curNode->right;
			}
			else if (curNode->key > key) {
				curNode = curNode->left;
			}
		}
		newNode->parent = parNode;

		if (parNode->key < key) {
			parNode->right = newNode;
		}
		else {
			parNode->left = newNode;
		}
		cout << cnt << endl;
	}

	void printParent(int x) {
		int cnt = 0;
		node* findNode = search(root, x,cnt);
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
		node* findNode = search(root, x,cnt);
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

	void printSearch(int x) {
		int cnt = 0;
		if (root == nullptr) {//이진트리가 비어있을 때 
			cout << "empty" << endl;
			return;
		}
		node* findNode = search(root, x, cnt);
		if (findNode == NULL) {
			cout << cnt << endl;
			return;
		}
		cout << cnt << endl;
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