#include <iostream>
#include<vector>
using namespace std;

class Heap {
private:
	vector<int> seq;
	void swap(int a,int b) {
		seq[0] = seq[a];
		seq[a] = seq[b];
		seq[b] = seq[0];
	}
	void upHeap(int idx) {
		if (idx == 1) {
			return;
		}
		int parIdx = idx / 2;
		if (seq[idx] < seq[parIdx]) {
			swap(idx, parIdx);
			upHeap(parIdx);
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
			else {
				child = right;
			}
		}
		if (seq[child] < seq[idx]) {
			swap(child, idx);
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
	void push(int i) {
		seq.push_back(i);
		upHeap(size());
	}
	void pop() {
		if (empty()) {
			cout << -1 << endl;
			return;
		}
		swap(size(), 1);
		seq.pop_back();
		downHeap(1);
	}
	int top() {
		if (empty()) {
			return -1;
		}
		return seq[1];
	}
	void sec_top(Heap h) {
		if (size()<2) {
			cout << "Error" << endl;
			return;
		}
		Heap h2 = h;
		h2.pop();
		cout << h2.top() << endl;
	}
};

int main() {
	int N;
	cin >> N;
	Heap h;
	for (int i = 0; i < N; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "size") {
			cout << h.size() << endl;
		}
		else if (cmd == "empty") {
			if (h.empty()) {
				cout << 1 << endl;
			}
			else {
				cout << 0 << endl;
			}
		}
		else if (cmd == "push") {
			int x;
			cin >> x;
			h.push(x);
		}
		else if (cmd == "pop") {
			if (h.empty()) {
				cout << -1 << endl;
			}
			else {
				cout << h.top() << endl;
				h.pop();
			}
		}
		else if (cmd == "top") {
			cout << h.top() << endl;
		}
		else if (cmd == "second_top") {
			h.sec_top(h);
		}
	}
}