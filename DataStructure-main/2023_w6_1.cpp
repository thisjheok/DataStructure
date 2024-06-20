#include <iostream>
#include <vector>
using namespace std;


struct node {
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
	void deleteNode(int data);
	void printParent(int data);
	void printChild(int data);
	void min_maxChild(int data);
private:
	node* root; 
	vector<node*> nodeList; //트리의 모든 노드의 포인터를 저장하는 벡터
	int find(int data, vector<node*>& List);
};

Tree::Tree(int data) {
	root = new node(data, NULL);
	nodeList.push_back(root);
}

int Tree::find(int data, vector<node*>& List) {
	for (int i = 0;i < List.size();i++) {
		if (List[i]->data == data) {
			return i;
		}
	}
	return -1;
}

void Tree::insertNode(int parData, int data) {
	if (find(data, nodeList) != -1) {
		cout << -1 << endl;
		return;
	}
	int idx = find(parData, nodeList);
	if (idx == -1) {
		cout << -1 << endl;
		return;
	}

	node* parNode = nodeList[idx];
	node* newNode = new node(data, parNode);
	parNode->childList.push_back(newNode);
	nodeList.push_back(newNode);
}

void Tree::deleteNode(int data) {
	int idx = find(data, nodeList);
	if (idx == -1) {
		cout << -1 << endl;
		return;
	}
	node* delNode = nodeList[idx];
	if (delNode == root) {
		return;
	}

	node* parNode = delNode->parent;
	for (int i = 0;i < delNode->childList.size();i++) {
		parNode->childList.push_back(delNode->childList[i]);
		delNode->childList[i]->parent = parNode;
	}

	vector<node*>& child = parNode->childList;
	child.erase(child.begin() + find(data, child));
	nodeList.erase(nodeList.begin() + idx);
	delete delNode;
}

void Tree::printParent(int data) {
	int idx = find(data, nodeList);
	if (idx <= 0) {
		cout << -1 << endl;
		return;
	}

	node* curNode = nodeList[idx];
	cout << curNode->parent->data << endl;
}

void Tree::printChild(int data) {
	int idx = find(data, nodeList);
	if (idx == -1) {
		cout << -1 << endl;
		return;
	}

	vector<node*>& child = nodeList[idx]->childList;
	if (child.empty()) {
		cout << -1 << endl;
		return;
	}

	for (int i = 0;i < child.size();i++) {
		cout << child[i]->data << " ";
	}
	cout << endl;

}

void Tree::min_maxChild(int data) {
	int idx = find(data, nodeList);
	if (idx == -1) {
		cout << -1 << endl;
		return;
	}
	vector<node*>& child = nodeList[idx]->childList;
	if (child.size()<2) {
		cout << -1 << endl;
		return;
	}

	int max = child[0]->data;
	int min = child[0]->data;

	for (int i = 0; i < child.size(); i++) {
		if (max < child[i]->data) {
			max = child[i]->data;
		}
		if (min > child[i]->data) {
			min = child[i]->data;
		}
	}

	cout << min + max << endl;

}



int main() {
	int t;
	cin >> t;
	Tree tree1(1);
	for (int i = 0;i < t;i++) {
		string s;
		cin >> s;
		if (s == "insert") {
			int x,y;
			cin >> x >> y;
			tree1.insertNode(x, y);
		}
		else if (s == "delete") {
			int x;
			cin >> x;
			tree1.deleteNode(x);
		}
		else if (s == "parent") {
			int x;
			cin >> x;
			tree1.printParent(x);
		}
		else if (s == "child") {
			int x;
			cin >> x;
			tree1.printChild(x);
		}
		else if (s == "min_maxChild") {
			int x;
			cin >> x;
			tree1.min_maxChild(x);
		}
	}
}