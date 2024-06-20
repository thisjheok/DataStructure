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
	int divisor;
	entry* table;
	int hashFnc(int key) {
		return key % capacity;
	}
	int hashFnc2(int key) {
		return divisor - (key % divisor);
	}
public:
	Hash(int n, int m) {
		capacity = n;
		divisor = m;
		table = new entry[capacity];
	}
	void put(int K, string S) {
		int index = hashFnc(K);
		int fstIdx = index;
		int probe = 1;
		while (table[index].valid == ISITEM && probe <= capacity) {
			index = hashFnc(index + hashFnc2(K));
			probe++;
		}
		int secIdx = index;
		if (probe > capacity) {
			secIdx = -1;
			cout << fstIdx << " " << secIdx << endl;
			return;
		}
		table[index] = entry(K, S);
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
			index = hashFnc(index + hashFnc2(K));
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
			index = hashFnc(index + hashFnc2(K));
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
	int T, N, M;
	cin >> T >> N >> M;
	Hash hash(N, M);
	for (int i = 0; i < T; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "put") {
			int K;
			string S;
			cin >> K >> S;
			hash.put(K, S);
		}
		else if (cmd == "erase") {
			int K;
			cin >> K;
			hash.erase(K);
		}
		else if (cmd == "find") {
			int K;
			cin >> K;
			cout << hash.find(K) << endl;
		}
		else if (cmd == "vacant") {
			hash.vacant();
		}
	}
}