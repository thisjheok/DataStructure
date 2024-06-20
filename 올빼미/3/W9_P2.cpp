#include <iostream>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		int c1 = e1;
		int c2 = e2;
		int n1 = 0;
		int n2 = 0;

		while (c1 != 0) {
			n1++;
			c1 /= 10;
		}
		while (c2 != 0) {
			n2++;
			c2 /= 10;
		}
		if (n1 == n2) {
			return e1 > e2;
		}
		else {
			return n1 < n2;
		}
	}
};

class PQ {
private:
	vector<int> seq;
public:
	int size() {
		return seq.size();
	}
	void insert(int e) {
		seq.push_back(e);
	}
	int top() {
		int idx = 0;
		compare C;
		for (int i = 0; i < size(); i++) {
			if (C(seq[i], seq[idx])) {
				idx = i;
			}
		}
		return seq[idx];
	}
	void removeTop() {
		int idx = 0;
		compare C;
		for (int i = 0; i < size(); i++) {
			if (C(seq[i], seq[idx])) {
				idx = i;
			}
		}
		seq.erase(seq.begin() + idx);
	}
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		PQ pq;
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			pq.insert(x);
		}
		cout << "Case #" << i + 1 << "." << endl;
		for (int j = 0; j < n; j++) {
			cout << pq.top() << " ";
			pq.removeTop();
		}
		cout << endl;
	}
}

/*
2
7
614 8 3525 4132 27 482 16656
10
824 120 565 74 17 175 170 163 1293 3696
*/