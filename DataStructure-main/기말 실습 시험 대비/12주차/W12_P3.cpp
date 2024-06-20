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
	int hashFnc(int key) {
		return key % capacity;
	};
public:
	Hash(int N) {
		capacity = N;
		table = new entry[capacity];
	}
	void put(int key,string value) {
		int index = hashFnc(key);
		int fstIdx = index;
		int probe = 0;
		while (table[index].valid == ISITEM && probe <= capacity) {
			index = hashFnc(index + 1);
			probe++;
		}
		int secIdx = index;
		if (probe > capacity) {
			secIdx = -1;
			cout << fstIdx << " " << secIdx << endl;
			return;
		}
		table[index] = entry(key, value);
		cout << fstIdx << " " << secIdx << endl;
	}

	void erase(int key) {
		int index = hashFnc(key);
		int probe = 0;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				cout << table[index].value << endl;
				table[index].erase();
				return;
			}
			probe++;
			index = hashFnc(index + 1);
		}
		cout << "None" << endl;
		return;
	}

	void find(int key) {
		int index = hashFnc(key);
		int probe = 0;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				cout << table[index].value << endl;
				return;
			}
			probe++;
			index = hashFnc(index + 1);
		}
		cout << "None" << endl;
		return;
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
	Hash hash(n);
	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "put") {
			int k;
			string s;
			cin >> k>>s;
			hash.put(k, s);
		}
		else if (cmd == "erase") {
			int k;
			cin >> k;
			hash.erase(k);
		}
		else if(cmd=="find") {
			int k;
			cin >> k;
			hash.find(k);
		}
		else if (cmd == "vacant") {
			hash.vacant();
		}
	}
}