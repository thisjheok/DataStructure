#include <iostream>
#include <string>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

struct entry {
	int key;
	string value;
	int valid;
	entry() {
		key = 0;
		value = "";
		valid = NOITEM;
	}
	entry(int key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
	}
	void erase() {
		valid = AVAILABLE;
	}
};

class Hash {
private:
	entry* table;
	int capacity;
	int divisor;
	int hashFnc(int key) {
		return key % capacity;
	}
	int hashFnc2(int key) {
		return divisor - (key % divisor);
	}
public:
	Hash(int n,int m) {
		capacity = n;
		divisor = m;
		table = new entry[capacity];
	}
	void put(int k, string s) {
		int idx = hashFnc(k);
		int fstIdx = idx;
		int probe = 1;
		int secIdx;
		while (table[idx].valid == ISITEM && probe <= capacity) {
			idx = hashFnc(idx + hashFnc2(k));
			probe++;
		}
		secIdx = idx;
		if (probe > capacity) {
			secIdx = -1;
			cout << fstIdx << " " << secIdx << endl;
			return;
		}
		table[idx] =  entry(k, s);
		cout << fstIdx << " " << secIdx << endl;
		return;
	}

	void erase(int k) {
		int idx = hashFnc(k);
		int probe = 1;
		while (table[idx].valid != NOITEM && probe <= capacity) {
			if (table[idx].valid == ISITEM && table[idx].key == k) {
				cout << table[idx].value << endl;
				table[idx].erase();
				return;
			}
			idx = hashFnc(idx + hashFnc2(k));
			probe++;
		}
			cout << "None" << endl;
	}

	void find(int k) {
		int idx = hashFnc(k);
		int probe = 1;
		while (table[idx].valid != NOITEM && probe <= capacity) {
			if (table[idx].valid == ISITEM && table[idx].key == k) {
				cout << table[idx].value << endl;
				return;
			}
			idx = hashFnc(idx + hashFnc2(k));
			probe++;
		}
			cout << "None" << endl;
	}
	void vacant() {
		int cnt = 0;
		for (int i = 0; i < capacity; i++) {
			if (table[i].valid == NOITEM || table[i].valid == AVAILABLE) {
				cnt++;
			}
		}
		cout << cnt << endl;
	}
};

int main() {
	int t, n, m;
	cin >> t >> n >> m;
	Hash hash(n, m);
	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "put") {
			int k;
			string s;
			cin >> k >> s;
			hash.put(k, s);
		}
		else if (cmd == "erase") {
			int k;
			cin >> k;
			hash.erase(k);
		}
		else if (cmd == "find") {
			int k;
			cin >> k;
			hash.find(k);
		}
		else if (cmd == "vacant") {
			hash.vacant();
		}
	}
}