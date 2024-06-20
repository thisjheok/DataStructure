#include <iostream>
#include <vector>
using namespace std;

class Heap {
private:
	vector<int> seq;
	void swap(int a, int b) {
		seq[0] = seq[a];
		seq[a] = seq[b];
		seq[b] = seq[0];
	}
	void upHeap(int idx) {
		int par = idx / 2;
		if (idx == 1) {
			return;
		}
		if (seq[par] > seq[idx]) {
			swap(par, idx);
			upHeap(par);
		}
	}
	void downHeap(int idx) {
		int left = 2 * idx;
		int right = 2 * idx + 1;
		int child;

		if (left > size()) {
			return;
		}
		else if (left == size()) {
			child = left;
		}
		else {
			if (seq[left] < seq[right]) {
				child = left;
			}
			else if (seq[left] > seq[right]) {
				child = right;
			}
		}
		if (seq[child] < seq[idx]) {
			swap(idx, child);
			downHeap(child);
		}
	}
public:
	Heap() {
		seq.push_back(0);
	}
	int size() {
		return seq.size() - 1;
	}
	bool empty() {
		return seq.size() == 1;
	}
	void push(int e) {
		seq.push_back(e);
		upHeap(size());
	}
	void pop() {
		if (empty()) {
			cout << -1 << endl;
			return;
		}
		swap(1, size());
		seq.pop_back();
		downHeap(1);
	}
	int top() {
		if (empty()) return -1;
		return seq[1];
	}
	void sec_top(Heap h) {
		if (size() < 2) {
			cout << "Error" << endl;
			return;
		}
		Heap h2 = h;
		h2.pop();
		cout << h2.top() << endl;
	}
};

int main() {
	int n;
	cin >> n;
	Heap heap;
	for (int i = 0; i < n; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "size") {
			cout << heap.size() << endl;
		}
		else if (cmd == "empty") {
			if (heap.empty()) {
				cout << 1 << endl;
			}
			else {
				cout << 0 << endl;
			}
		}
		else if (cmd == "push") {
			int e;
			cin >> e;
			heap.push(e);
		}
		else if (cmd == "pop") {
			if (heap.empty()) {//empty 조건 주의!! main에서 해주기
				cout << -1 << endl;
			}
			else {
				cout << heap.top() << endl;
				heap.pop();
			}
		}
		else if (cmd == "top") {
			cout << heap.top() << endl;
		}
		else if (cmd == "second_top") {
			heap.sec_top(heap);
		}
	}
}