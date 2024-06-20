#include <iostream>
#include <vector>
using namespace std;

struct compare {
	bool operator()(const int& e1, const int& e2) {
		return e1 > e2;
	}
};

class heap {
public:
	heap();
	int size();
	bool empty();
	void insert(int e);
	int top();
	void removeTop();
	void second_top(heap h);
private:
	vector<int> arr;
	void upHeap(int idx);
	void downHeap(int idx);
	void swap(int idx1, int idx2);
};

heap::heap() {
	arr.push_back(0);
}

int heap::size() {
	return arr.size() - 1;
}

void heap::insert(int e) {
	arr.push_back(e);
	upHeap(size());	//새로 삽입된 원소에서 upHeap 수행
}

bool heap::empty() {
	return (arr.size() == 1);
}

void heap::swap(int idx1, int idx2) {
	arr[0] = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = arr[0];
}

int heap::top() {
	if (empty()) {
		return -1;
	}
	return arr[1];
}

void heap::second_top(heap h) {
	if (size() < 2) {
		cout << "Error" << endl;
		return;
	}
	heap h2;
	h2 = h;
	int sec_top;
	h2.removeTop();
	sec_top = h2.top();
	cout << sec_top << endl;
}

void heap::removeTop() {
	if (empty()) {
		cout << -1 << endl;
		return;
	}
	swap(1, size());
	arr.pop_back();
	downHeap(1);
}

void heap::upHeap(int idx) {
	if (idx == 1) {
		return;
	}
	int parent = idx / 2;
	compare C;
	if (!C(arr[parent], arr[idx])) {//heapOrder 맞춰주기 minheap
		swap(parent, idx);
		upHeap(parent);
	}
}

void heap::downHeap(int idx) {
	int left = 2 * idx;
	int right = 2 * idx + 1;
	int child; //두 자식 중 더 작은 자식의 인덱스를 저장하는 변수
	compare C;
	if (left > size()) { //두 자식 모두 존재하지 않을 경우 종료
		return;
	}
	else if (left == size()) { // 왼쪽 자식만 존재할 경우, child에 왼쪽 자식의 인덱스를 대입
		child = left;
	}
	else {
		if (!C(arr[right], arr[left])) {
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


int main() {
	int t;
	cin >> t;
	heap h1;

	for (int i = 0; i < t; i++) {
		string s;
		cin >> s;
		if (s == "push") {
			int n;
			cin >> n;
			h1.insert(n);
		}
		else if (s == "size") {
			cout << h1.size() << endl;
		}
		else if (s == "empty") {
			if (h1.empty()) {
				cout << 1 << endl;
			}
			else {
				cout << 0 << endl;
			}
		}
		else if (s == "pop") {
			if (h1.empty()) {
				cout << -1 << endl;
			}
			else {
				cout << h1.top() << endl;
				h1.removeTop();
			}
		}
		else if (s == "top") {
			cout << h1.top() << endl;
		}
		else if (s == "second_top") {
			h1.second_top(h1);
		}
	}
}