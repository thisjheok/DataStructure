#include <iostream>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		if (e1 % 2 == 0 && e2 % 2 == 0) {
			// 두 수 모두 짝수인 경우
			return e1 < e2;
		}
		else if (e1 % 2 != 0 && e2 % 2 != 0) {
			// 두 수 모두 홀수인 경우
			return e1 > e2;
		}
		else {
			// 하나는 홀수, 하나는 짝수인 경우 (홀수가 더 큰 우선순위를 갖음)
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
	upHeap(size());	//새로 삽입된 원소에서 upHeap 수행
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
	downHeap(1); //힙의 루트에서 downHeap 수행
}

void heap::upHeap(int idx) {
	if (idx == 1) { //루트에 도달할 경우 종료
		return;
	}
	compare C;
	int parent = idx / 2; //현재 노드의 부모의 인덱스 계산
	if (!C(arr[parent], arr[idx])) { //heap-order를 만족하지 않을 경우(min-heap)
		swap(parent, idx); //현재 노드와 부모의 값을 바꾸고
		upHeap(parent); //부모를 기준으로 upheap 수행
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
	else if (left == size()) { // 왼쪽 자식만 존재할 경우, child에 왼쪽 자식의 인덱스를 대입
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

	if (!C(arr[idx], arr[child])) {//heap-order 만족하지 않을 경우
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