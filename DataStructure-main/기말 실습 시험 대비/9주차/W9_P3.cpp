#include <iostream>
#include <vector>
using namespace std;
struct compare {
	bool operator()(const int& e1, const int& e2) {
		return e1 > e2;
	}
};

class unsortedSeqPQ {
public:
	int size();
	bool empty();
	void push(int e);
	int top();
	void pop();
	int elem(int i);
private:
	compare C;
	vector<int> arr;
};

int unsortedSeqPQ::size() {
	return arr.size();
}

bool unsortedSeqPQ::empty() {
	return size() == 0;
}

void unsortedSeqPQ::push(int e) {
	arr.push_back(e);
}

int unsortedSeqPQ::top() {
	if (empty()) {
		return -1;
	}
	int minIdx = 0;
	for (int i = 0;i < arr.size();i++) {
		if (C(arr[i], arr[minIdx])) {
			minIdx = i;
		}
	}
	return arr[minIdx];
}

void unsortedSeqPQ::pop() {
	if (empty()) {
		return;
	}
	int minIdx = 0;
	for (int i = 0;i < arr.size();i++) {
		if (C(arr[i], arr[minIdx])) {
			minIdx = i;
		}
	}
	arr.erase(arr.begin() + minIdx);
}

int unsortedSeqPQ::elem(int i) {
	if (empty()) {
		return -1;
	}
	return arr[i];
}

int main() {

	int t;
	cin >> t;

	for (int i = 0;i < t;i++) {
		unsortedSeqPQ PQ;
		vector<int> S;
		int n;
		cin >> n;
		
		for (int j = 0;j < n;j++) {
			int s;
			cin >> s;
			S.push_back(s);
		}
		int k;
		cin >> k;
		if (k <= n) {
			for (int j = 0;j < k;j++) {
				PQ.push(S[0]);
				S.erase(S.begin());
			}
			cout << "S : ";
			for (int j = 0;j < n - k;j++) {
				cout << S[j] << " ";
			}
			cout << endl;
			cout << "PQ : ";
			for (int j = 0;j < k;j++) {
				cout << PQ.elem(j) << " ";
			}
			cout << endl;
		}
		else {
			for (int j = 0;j < n;j++) {
				PQ.push(S[0]);
				S.erase(S.begin());
			}
			for (int j = 0;j < k-n;j++) {
				S.push_back(PQ.top());
				PQ.pop();
			}
			cout << "S : ";
			for (int j = 0;j < k - n;j++) {
				cout<<S[j]<<" ";
			}
			cout << endl;
			cout << "PQ : ";
			for (int j = 0; j < n - (k - n); j++) {//pqÃâ·Â
				cout << PQ.elem(j) << " ";
			}
			cout << endl;
		}

	}
}
