#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) const {
		return e1 < e2;
	}
};


struct compare2 {
	bool operator()(const int& e1, const int& e2) const {
		return e1 > e2;
	}
};

class unsortedSeqPQ {
private :
	vector<int> seq;
public :
	bool empty() {
		return (seq.size() == 0);
	}

	void insert(int e) {
		seq.push_back(e);
	}

	int min() {
		if (empty()) return -1;
		compare C;
		int minVal = seq[0];

		for (int i = 0; i < seq.size(); i++) {
			if (C(seq[i], minVal)) {
				minVal = seq[i];
			}
		}
		return minVal;
	}

	void removeMin() {
		if (empty()) return;
		compare C;
		int minIdx = 0;
		for (int i = 0; i < seq.size(); i++) {
			if (C(seq[i], seq[minIdx])) {
				minIdx = i;
			}
		}
		seq.erase(seq.begin() + minIdx);
	}

	int max() {
		if (empty()) return -1;
		compare2 C;
		int maxVal = seq[0];

		for (int i = 0; i < seq.size(); i++) {
			if (C(seq[i], maxVal)) {
				maxVal = seq[i];
			}
		}
		return maxVal;
	}

	void removeMax() {
		if (empty()) return;
		compare2 C;
		int maxIdx = 0;
		for (int i = 0; i < seq.size(); i++) {
			if (C(seq[i], seq[maxIdx])) {
				maxIdx = i;
			}
		}
		seq.erase(seq.begin() + maxIdx);
	}

};

int main() {
	int t;
	cin >> t;

	for (int a = 0; a < t; a++) {
		int n;
		cin >> n;

		vector<int> arr;
		unsortedSeqPQ uq;

		for (int i = 0; i < n; i++) {
			int e;
			cin >> e;
			arr.push_back(e);
		}

		int k;
		cin >> k;

		if (k <= n) {
			for (int i = 0; i < k; i++) {
				uq.insert(arr[0]); //s->pq
				arr.erase(arr.begin());
			}
			cout << "S : ";
			for (int i = 0; i < n-k; i++) {
				cout << arr[i] << " ";// s출력
			}
			cout << endl;
			cout << "PQ : ";
			for (int i = 0; i < k; i++) {//pq출력
				cout << uq.min() << " ";
				uq.removeMin();
			}
		}
		else {
			for (int i = 0; i < n; i++) {//s->pq
				uq.insert(arr[0]);
				arr.erase(arr.begin());
			}
			for (int i = 0; i < k-n; i++) {//pq->s
				arr.push_back(uq.max());
				uq.removeMax();
			}
			cout << "S : ";
			for (int i = 0; i < k-n; i++) {//s출력
				cout << arr[i] << " ";
			}
			cout << endl;
			cout << "PQ : ";
			for (int i = 0; i < n-(k-n); i++) {//pq출력
				cout << uq.min() << " ";
				uq.removeMin();
			}
		}
		cout << endl;
	}

	return 0;

}