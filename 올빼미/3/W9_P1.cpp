#include <iostream>
#include <vector>
using namespace std;

class PQ {
private:
	vector<int> seq;
public:
	bool empty() {
		return seq.size() == 0;
	}
	int size() {
		return seq.size();
	}
	void insert(int a) {
		seq.push_back(a);
	}
	int min() {
		int minIdx = 0;
		int n = seq.size();
		for (int i = 0; i < n; i++) {
			if (seq[minIdx] > seq[i]) {
				minIdx = i;
			}
		}
		return seq[minIdx];
	}
	void removeMin() {
		int minIdx = 0;
		int n = seq.size();
		for (int i = 0; i < n; i++) {
			if (seq[minIdx] > seq[i]) {
				minIdx = i;
			}
		}
		seq.erase(seq.begin() + minIdx);
	}
	int max() {
		int maxIdx = 0;
		int n = seq.size();
		for (int i = 0; i < n; i++) {
			if (seq[maxIdx] < seq[i]) {
				maxIdx = i;
			}
		}
		return seq[maxIdx];
	}
	void removeMax() {
		int minIdx = 0;
		int n = seq.size();
		for (int i = 0; i < n; i++) {
			if (seq[minIdx] < seq[i]) {
				minIdx = i;
			}
		}
		seq.erase(seq.begin() + minIdx);
	}
};

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		vector<int> s;
		PQ pq;
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			s.push_back(x);
		}
		int k;
		cin >> k;

		if (k <= n) {
			for (int j = 0; j < k; j++) {
				pq.insert(s[0]);
				s.erase(s.begin());
			}
			cout << "S : ";
			for (int j = 0; j < n - k; j++) {
				cout << s[j] << " ";
			}
			cout << endl;
			cout << "PQ : ";
			for (int j = 0; j < k; j++) {
				cout << pq.min() << " ";
				pq.removeMin();
			}
			cout << endl;
		}
		else {
			for (int j = 0; j < n; j++) {
				pq.insert(s[0]);
				s.erase(s.begin());
			}
			for (int j = 0; j < k - n; j++) {
				s.push_back(pq.max());
				pq.removeMax();
			}
			cout << "S : ";
			for (int j = 0; j < k - n; j++) {
				cout << s[j] << " ";
			}
			cout << endl;
			cout << "PQ : ";
			for (int j = 0; j < n-(k-n); j++) {
				cout << pq.min() << " ";
				pq.removeMin();
			}
			cout << endl;
		}

	}
}

/*
2
7
7 4 8 2 5 3 9
5 
10
1 4 2 8 9 7 23 3 66 5
13
*/