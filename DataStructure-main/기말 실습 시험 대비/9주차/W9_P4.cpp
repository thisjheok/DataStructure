#include <iostream>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		int c1 = e1;//복사한 수
		int c2 = e2;//복사한 수

		int n1 = 0;//자릿수 담을 변수
		int n2 = 0;//자릿수 담을 변수

		while (c1 != 0) {
			c1 /= 10;
			n1++;
		}
		while (c2 != 0) {
			c2 /= 10;
			n2++;
		}

		if (n1 == n2) {
			return e1 < e2;
		}
		else {
			return n1 > n2;//자릿수가 큰 수가 우선순위가 높다.
		}
	}
};

class unsortedSeqPQ {
private:
	vector<int> seq;
public:
	bool empty();
	void insert(int e);
	int min();
	void removeMin();
};

bool unsortedSeqPQ::empty() {
	return seq.size() == 0;
}

void unsortedSeqPQ::insert(int e) {
	seq.push_back(e);
}

int unsortedSeqPQ::min() {
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

void unsortedSeqPQ::removeMin() {
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

int main() {
	unsortedSeqPQ PQ;
	int t;
	cin >> t;

	for (int i = 0;i < t;i++) {
		int n;
		cin >> n;
		for (int j = 0;j < n;j++) {
			int s;
			cin >> s;
			PQ.insert(s);
		}
		cout << "Case #" << i + 1 << "." << endl;
		for (int i = 0; i < n; i++) {
			cout << uq.min() << " ";
			uq.removeMin();

		}
		cout << endl;
	}
}