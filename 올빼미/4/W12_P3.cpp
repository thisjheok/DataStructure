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
	int capacity;
	int hashFnc(int key) {
		return key % capacity;
	}
	entry* table;
public:
	Hash(int n) {
		capacity = n;
		table = new entry[capacity];
	}
	void put(int K, string S) {
		int index = hashFnc(K);
		int probe = 1;
		int fstIdx = index;
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
		table[index] =  entry(K, S);
		cout << fstIdx << " " << secIdx << endl;
	}
	void erase(int K) {
		int index = hashFnc(K);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == K) {
				cout << table[index].value << endl;
				table[index].erase();
				return;
			}
			index = hashFnc(index + 1);
			probe++;
		}
		cout << "None" << endl;
	}

	string find(int K) {
		int index = hashFnc(K);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == K) {
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
	int t;
	cin >> t;
	int n;
	cin >> n;
	Hash hash(n);
	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "put") {
			int x;
			string s;
			cin >> x >> s;
			hash.put(x, s);
		}
		else if (cmd == "erase") {
			int x;
			cin >> x;
			hash.erase(x);
		}
		else if (cmd == "find") {
			int x;
			cin >> x;
			cout<<hash.find(x)<<endl;
		}
		else if (cmd == "vacant") {
			hash.vacant();
		}
	}
}