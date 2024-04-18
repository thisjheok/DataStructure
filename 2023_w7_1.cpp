#include <iostream>
#include <vector>
using namespace std;

struct node
{
	int data;
	node* parent;
	vector<node*> childList;
	node(int data, node* parent) {
		this->data = data;
		this->parent = parent;
	}
};

class Tree {
public:
	Tree(int data);
	void insertNode(int parData, int data);
	void preorder(node* curNode);
	void postorder(node* curNode);
	node* getRoot();
	void print(int data);
private:
	node* root;
	vector<node*> nodeList;

	int find(int data, vector<node*>& list);
};

Tree::Tree(int data) {
	root = new node(data, NULL);
	nodeList.push_back(root);
}

int Tree::find(int data, vector<node*>& list) {
	for (int i = 0;i < list.size();i++) {
		if (list[i]->data == data) {
			return i;
		}
	}
	return -1;
}

void Tree::insertNode(int parData, int data) {
	if (find(data, nodeList) != -1) {
		return;
	}
	int idx = find(parData, nodeList);
	if (idx == -1) {
		return;
	}

	node* parNode = nodeList[idx];
	node* newNode = new node(data, parNode);
	parNode->childList.push_back(newNode);
	nodeList.push_back(newNode);
	return;
}

void Tree::preorder(node* curNode) {
	print(curNode->data);
	for (int i = 0;i < curNode->childList.size();i++) {
		preorder(curNode->childList[i]);
	}
}
void Tree::postorder(node* curNode) {
	for (int i = 0;i < curNode->childList.size();i++) {
		postorder(curNode->childList[i]);
	}
	cout << curNode->data << " ";
}

node* Tree::getRoot() {
	return root;
}

void Tree::print(int data) {
	int idx = find(data, nodeList);
	vector<node*>& child = nodeList[idx]->childList;
	if (child.empty()) {//자식이 없는 경우: 깊이(부모의 수) 출력
		node* curNode = nodeList[idx];
		int n = 0;
		while (curNode->parent != NULL) {
			curNode = curNode->parent;
			n++;
		}
		cout << n << " ";
	}
	else {
		cout << child.size() << " ";
	}
}

int main() {
	int t;
	cin >> t;
	for (int i = 0;i < t;i++) {
		int n;
		cin >> n;
		Tree tree1(1);
		for (int j = 0;j < n-1;j++) {
			int x, y;
			cin >> x >> y;
			tree1.insertNode(x, y);
		}
		tree1.preorder(tree1.getRoot());
		cout << endl;
	}
}