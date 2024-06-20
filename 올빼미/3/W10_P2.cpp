#include<iostream>
#include<vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		if (e1 % 2 == 0 && e2 % 2 == 0) {
			return e1 < e2;
		}
		else if (e1 % 2 != 0 && e2 % 2 != 0) {
			return e1 > e2;
		}
		else {
			return e1 % 2 != 0;
		}
	}
};

class Heap {
private:
	vector<int> seq;
	void swap(int a, int b) {
		seq[0] = seq[a];
		seq[a] = seq[b];
		seq[b] = seq[0];
	}
	void upHeap(int idx) {
		if (idx == 1) {
			return;
		}
		int par = idx / 2;
		compare C;
		if (C(seq[idx], seq[par])) {
			swap(idx, par);
			upHeap(par);
		}
	}
	void downHeap(int idx) {
		int left = 2 * idx;
		int right = 2 * idx + 1;
		int child;
		compare C;
		if (left > size()) {
			return;
		}
		else if (left == size()) {
			child = left;
		}
		else {
			if (C(seq[left], seq[right])) {
				child = left;
			}
			else {
				child = right;
			}
		}
		if (C(seq[child], seq[idx])) {
			swap(child, idx);
			downHeap(child);
		}
	}
public:
	Heap() {
		seq.push_back(0);
	}
	int size() {
		return seq.size()-1;
	}
	bool empty() {
		return seq.size() == 1;
	}
	void insert(int a) {
		seq.push_back(a);
		upHeap(size());
	}
	int top() {
		if (empty()) return -1;
		return seq[1];
	}
	void removeTop() {
		if (empty()) return;
		swap(1, size());
		seq.pop_back();
		downHeap(1);
	}
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		Heap h;
		for (int j = 0; j < n; j++) {
			int b;
			cin >> b;
			h.insert(b);
		}
		for (int j = 0; j < n; j++) {
			cout << h.top() << " ";
			h.removeTop();
		}
		cout << endl;
	}
}