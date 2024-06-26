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
	node* search(node* curNode, int key) {
		if (curNode == NULL) {
			return NULL;
		}
		if (curNode->key == key) {
			return curNode;
		}
		else if (curNode->key < key) {
			return search(curNode->right, key);
		}
		else {
			return search(curNode->left, key);
		}
	}
	void reverseInorderCount(node* u, int& count, int& result, int k) {
		if (u == NULL || count >= k) {
			return;
		}
		reverseInorderCount(u->right, count, result, k); // 오른쪽 중위순회
		count++;
		if (count == k) {
			result = u->key; // k번째 큰 요소를 찾으면 결과에 저장
			return;
		}
		reverseInorderCount(u->left, count, result, k); // 왼쪽 중위순회
	}

	void insert(int key) {
		if (search(root, key) != NULL) {
			return;
		}
		node* newNode = new node(key);
		if (root == NULL) {
			root = newNode;
			return;
		}
		node* curNode = root;
		node* parNode = NULL;
		while (curNode != NULL) {
			parNode = curNode;
			if (curNode->key < key) {
				curNode = curNode->right;
			}
			else {
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
	}

	void remove(int key) {
		node* delNode = search(root, key);
		if (delNode == NULL) {
			return;
		}

		node* parNode = delNode->parent;
		node* childNode;
		if (delNode->left == NULL && delNode->right == NULL) {
			childNode = NULL;
		}
		else if (delNode->left == NULL && delNode->right != NULL) {
			childNode = delNode->right;
		}
		else if (delNode->left != NULL && delNode->right == NULL) {
			childNode = delNode->left;
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
		else {
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
		reverseInorderCount(root, count, result, k);
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
	return 0;
}