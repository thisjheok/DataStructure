#include <iostream>
using namespace std;

struct node{
	int data;
	node* next;
	node* prev;
};

class DoublyLinkedList {
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void insert(node*pos,int data);
	void move(int n);
	int getCurrentData();
	node* end();
private:
	node* header;
	node* trailer;
	node* p;
};

DoublyLinkedList::DoublyLinkedList() {
	header = new node();
	trailer = new node();
	header->next = trailer;
	trailer->prev = header;
	header->prev = trailer->next = NULL;
	header->data = trailer->data = 0;
	p = header->next;
}

DoublyLinkedList::~DoublyLinkedList() {
	while (header->next != trailer) {
		node* temp = header->next;
		header->next = temp->next;
		delete temp;
	}
	delete header;
	delete trailer;
}

void DoublyLinkedList::insert(node* pos,int data) {
	node* newNode = new node();
	newNode->data = data;
	newNode->prev = pos->prev;
	newNode->next = pos;
	pos->prev->next = newNode;
	pos->prev = newNode;
}

node* DoublyLinkedList::end() {
	return trailer;
}

int DoublyLinkedList::getCurrentData() {
	return p->data;
}

void DoublyLinkedList::move(int n) {
	while (n != 0) {
		if (n > 0) {
			if (p->next == trailer) break; // trailer에 도달하면 종료
			p = p->next;
			n--;
		}
		else {
			if (p->prev == header) break; // header에 도달하면 종료
			p = p->prev;
			n++;
		}
	}
}


int main() {
	int t;
	cin >> t;


	for (int i = 0;i < t;i++) {
		DoublyLinkedList list;
		int n, m, command;
		cin >> n;
		int k;
		for (int j = 0;j < n;j++) {
			cin >> k;
			list.insert(list.end(),k);
		}

		cin >> m;
		for (int i = 0;i < m;i++) {
			cin >> command;
			list.move(command);
			list.move(list.getCurrentData());
		}
		cout << list.getCurrentData() << endl;
	}
}