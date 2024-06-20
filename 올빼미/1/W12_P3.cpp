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
		this->key = key;
		this->value = value;
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
public:
	Hash(int n, int m) {
		capacity = n;
		divisor = m;
		table = new entry[capacity];
	}
	void push(int k, string s) {
		int index = hashFnc(k);
		int fstIdx = index;
		int probe = 1;
		while (table[index].valid == ISITEM && probe <= capacity) {
			index = hashFnc(index + 1);
			probe++;
		}
		int secIdx = -1;
		if (probe > capacity) {
			cout << fstIdx << " " << secIdx << endl;
			return;
		}
		secIdx = index;
		table[index] = entry(k, s);
		cout << fstIdx << " " << secIdx << endl;
	}
	void erase(int k) {
		int index = hashFnc(k);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if(table[index].valid == ISITEM && table[index].key ==k){
				cout << table[index].value << endl;
				table[index].erase();
				return;
			}
			index = hashFnc(index + 1);
			probe++;
		}
		cout << "None" << endl;
	}
	string find(int k) {
		int index = hashFnc(k);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == k) {
				return table[index].value;
			}
			index = hashFnc(index + 1);
			probe++;
		}
		return "None";
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
	int t,n;
	cin >> t>>n;
	Hash hash(n, n);
	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "put") {
			int x;
			string s;
			cin >> x >> s;
			hash.push(x, s);
		}
		else if (cmd == "erase") {
			int x;
			cin >> x;
			hash.erase(x);
		}
		else if (cmd == "find") {
			int x;
			cin >> x;
			cout << hash.find(x) << endl;
		}
		else if (cmd == "vacant") {
			hash.vacant();
		}
	}
}