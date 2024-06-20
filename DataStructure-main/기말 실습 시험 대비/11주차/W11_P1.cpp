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
	node* getRoot() {
		return root;
	}
	node* search(node* curNode, int key, int& cmpCount) {
		if (curNode == NULL) {
			return NULL;
		}
		cmpCount++;
		if (curNode->key == key) {
			return curNode;
		}
		else if (curNode->key < key) {
			return search(curNode->right, key, cmpCount);
		}
		else {
			return search(curNode->left, key, cmpCount);
		}
	}

	void insert(int key) {
		int cmpCount = 0;
		if (search(root, key, cmpCount) != NULL) {
			return;
		}
		node* newNode = new node(key);
		if (root == NULL) {
			root = newNode;
			cout << cmpCount << endl;
			return;
		}
		node* curNode = root;
		node* parNode = NULL;

		while (curNode != NULL) {//leaf까지 위치 찾아서 내려가기
			parNode = curNode;
			cmpCount++;
			if (curNode->key < key) {
				curNode = curNode->right;
			}
			else {
				curNode = curNode->left;
			}
		}
		newNode->parent = parNode;

		if (parNode->key < key) {//자식과 연결
			parNode->right = newNode;
		}
		else { 
			parNode->left = newNode;
		}
		cout << cmpCount / 2 << endl;
	}


	void searchCnt(node* node1, int x) {
		int cmpCount = 0;
		if (root == nullptr) {
			cout << "empty" << endl;
			return;
		}
		if (search(node1, x, cmpCount)) {
			cout << cmpCount << endl;
		}
		else {
			cout << cmpCount << endl;
		}
	}

	void printParent(int x) {
		int cmpCount = 0;
		node* findNode = search(root, x, cmpCount);
		if (findNode == NULL) {
			cout << -1 << endl;
			return;
		}
		node* parNode = findNode->parent;
		if (parNode == NULL) {
			cout << -2 << endl;
			return;
		}
		cout << parNode->key << endl;
	}


	void printChild(int x) {
		int cmpCount = 0;
		node* findNode = search(root, x, cmpCount);
		if (findNode == NULL) {
			cout << -1 << endl;
			return;
		}
		node* childNode = findNode->left; // 왼쪽 자식의 키값 출력
		if (childNode == NULL) {
			cout << -2 << endl;
			return;
		}
		cout << childNode->key << endl;
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
				int x;
				cin >> x;
				bst.insert(x);
			}
			else if (s == "search") {
				int x;
				cin >> x;
				bst.searchCnt(bst.getRoot(), x);
			}
			else if (s == "parent") {
				int x;
				cin >> x;
				bst.printParent(x);
			}
			else if (s == "child") {
				int x;
				cin >> x;
				bst.printChild(x);
			}
		}
	}
	return 0;
}