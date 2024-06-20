#include <iostream>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		if (e1 % 2 == 0 && e2 % 2 == 0) {
			// �� �� ��� ¦���� ���
			return e1 < e2;
		}
		else if (e1 % 2 != 0 && e2 % 2 != 0) {
			// �� �� ��� Ȧ���� ���
			return e1 > e2;
		}
		else {
			// �ϳ��� Ȧ��, �ϳ��� ¦���� ��� (Ȧ���� �� ū �켱������ ����)
			return e1 % 2 != 0;
		}
	}
};



class heap {
public:
	heap();
	int size();
	bool empty();
	void insert(int e);
	int min();
	void removeMin();
	void print();
private:
	vector<int> arr;

	void swap(int idx1, int idx2);
	void upHeap(int idx);
	void downHeap(int idx);
};

heap::heap() {
	arr.push_back(0);
}

int heap::size() {
	return arr.size() - 1;
}

bool heap::empty() {
	return (arr.size() == 1);
}

void heap::swap(int idx1, int idx2) {
	arr[0] = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = arr[0];
}

void heap::insert(int e) {
	arr.push_back(e);
	upHeap(size());	//���� ���Ե� ���ҿ��� upHeap ����
}

int heap::min() {
	if (empty()) {
		return -1;
	}
	return arr[1];
}

void heap::removeMin() {
	if (empty()) {
		return;
	}
	swap(1, size());
	arr.pop_back();
	downHeap(1); //���� ��Ʈ���� downHeap ����
}

void heap::upHeap(int idx) {
	if (idx == 1) { //��Ʈ�� ������ ��� ����
		return;
	}
	compare C;
	int parent = idx / 2; //���� ����� �θ��� �ε��� ���
	if (!C(arr[parent], arr[idx])) { //heap-order�� �������� ���� ���(min-heap)
		swap(parent, idx); //���� ���� �θ��� ���� �ٲٰ�
		upHeap(parent); //�θ� �������� upheap ����
	}
}

void heap::downHeap(int idx) {
	int left = 2 * idx;
	int right = 2 * idx + 1;
	int child;
	compare C;
	if (left > size()) {
		return;
	}
	else if (left == size()) { // ���� �ڽĸ� ������ ���, child�� ���� �ڽ��� �ε����� ����
		child = left;
	}
	else {
		if (C(arr[left], arr[right])) {
			child = left;
		}
		else {
			child = right;
		}
	}

	if (!C(arr[idx], arr[child])) {//heap-order �������� ���� ���
		swap(child, idx);
		downHeap(child);
	}
}

void heap::print() {
	int s;
	s = size();
	for (int i = 1; i <= s; i++) {
		cout << min() << " ";
		removeMin();
	}
	cout << endl;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		heap h;
		int n;
		cin >> n;
		for (int j = 0; j < n; j++) {
			int b;
			cin >> b;
			h.insert(b);
		}
		h.print();
	}
}