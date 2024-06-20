#include <iostream>
#include <vector>
using namespace std;
//조건 만족하는 폴더 없으면 -1 나오게 하는 것 구현해야함
struct node
{
	int data;
	int size = NULL;
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
	void postorder(node* curNode,int c);
	void setSize(int data, int size);
	node* getRoot();
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

void Tree::setSize(int data, int size) {
	int idx = find(data, nodeList);
	node* nowNode = nodeList[idx];
	nowNode->size = size;
}

void Tree::postorder(node* curNode,int c) {
	for (int i = 0;i < curNode->childList.size();i++) {
		postorder(curNode->childList[i],c);
		curNode->size += curNode->childList[i]->size;
	}
	if (curNode->size > c) {
		cout << curNode->data << " ";
	}
}

node* Tree::getRoot() {
	return root;
}


int main() {
	int N, c;
	Tree tree1(1);
	cin >> N >> c;
	for (int i = 0;i < N-1;i++) {
		int x, y;
		cin >> x >> y;
		tree1.insertNode(x, y);
	}
	for (int i = 0;i < N;i++) {
		int x, w;
		cin >> x >> w;
		tree1.setSize(x, w);
	}
	tree1.postorder(tree1.getRoot(),c);
}