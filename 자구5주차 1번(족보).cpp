#include <iostream>
using namespace std;

struct node {
    int data;
    node* prev;
    node* next;
};

class nodeList {
public:
    nodeList();
    bool empty();
    int size();
    node* begin();
    node* end();
    node* getCurrentPosition();
    void insert(node* pos, int data);
    void erase(node* pos);
    void nextP();
    void prevP();
    void setPToBegin();
    void setPToEnd();
    void findmultiple(int e);
private:
    node* header;
    node* trailer;
    int n;
    node* p;
};

nodeList::nodeList() {
    header = new node();
    trailer = new node();
    header->next = trailer;
    trailer->prev = header;
    header->prev = trailer->next = NULL;
    n = 0;
    p = begin();
}

bool nodeList::empty() {
    return (n == 0);
}

int nodeList::size() {
    return n;
}

node* nodeList::getCurrentPosition() {
    return p;
}

node* nodeList::begin() {
    return header->next;
}

node* nodeList::end() {
    return trailer;
}

void nodeList::insert(node* pos, int data) {
    node* newNode = new node();
    newNode->data = data;
    newNode->prev = pos->prev;
    newNode->next = pos;
    pos->prev->next = newNode;
    pos->prev = newNode;
    n++;
}

void nodeList::setPToBegin() {
    p = begin();
}

void nodeList::setPToEnd() {
    p = end();
}

void nodeList::erase(node* pos) {
    if (pos == trailer || empty()) {
        if (empty()) cout << "empty" << endl;
        return;
    }
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    if (pos == p) { // 현재 p가 삭제되는 경우, p를 begin으로 변경
        p = begin();
    }
    delete pos;
    n--;
}

void nodeList::nextP() {
    if (p != trailer) p = p->next;
}

void nodeList::prevP() {
    if (p->prev != header) p = p->prev;
}

void nodeList::findmultiple(int e) {
    node* current = begin();
    bool found = false;
    int index = 0;
    while (current != trailer) {
        if (current->data % e == 0) {
            cout << index << " ";
            found = true;
        }
        current = current->next;
        index++;
    }
    if (!found) cout << "-1";
    cout << endl;
}

int main() {
    int commandCount;
    cin >> commandCount;
    nodeList list;

    for (int i = 0; i < commandCount; ++i) {
        string command;
        cin >> command;

        if (command == "insert") {
            int data;
            cin >> data;
            list.insert(list.getCurrentPosition(), data);
        }
        else if (command == "erase") {
            list.erase(list.getCurrentPosition());
        }
        else if (command == "nextP") {
            list.nextP();
        }
        else if (command == "prevP") {
            list.prevP();
        }
        else if (command == "findmultiple") {
            int e;
            cin >> e;
            list.findmultiple(e);
        }
        else if (command == "begin") {
            list.setPToBegin();
        }
        else if (command == "end") {
            list.setPToEnd();
        }
    }
    return 0;
}
