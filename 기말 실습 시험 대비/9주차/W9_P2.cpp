#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct compare {

	bool operator()(const int& e1, const int& e2) const {
		int c1, c2;
		c1 = e1;
		c2 = e2;
		int n1 = 0, n2 = 0;
		while (c1 != 0) {
			c1 /= 10;
			n1++;
		}

		while (c2 != 0) {
			c2 /= 10;
			n2++;
		}

		if (n1 == n2) {
			return e2 < e1;  // �� ū ���� �켱������ �����Ƿ� e2�� e1���� ũ�� true�� ��ȯ
		}
		// �׷��� ������ �ڸ����� ���� ���� �켱������ ����
		else {
			return n1 < n2;  // �ڸ����� ���� ���� �켱������ �����Ƿ� n1�� n2���� ũ�� false�� ��ȯ (n1 < n2�� ��� true)
		}
	}
};


class unsortedSeqPQ {
private:
	vector<int> seq;
public:
	int size() {
		return seq.size();
	}

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

};



int main() {
	unsortedSeqPQ uq;
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			int e;
			cin >> e;

			uq.insert(e);
		}
		cout << "Case #" << i+1 <<"." << endl;
		for (int i = 0; i < n; i++) {
			cout << uq.min() << " ";
			uq.removeMin();

		}
		cout << endl;

	}

	return 0;
}
