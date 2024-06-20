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
		return key% capacity;
	}
	int hashFnc2(int key) {
		return (divisor - (key % divisor));
	}
public:
	Hash(int N, int M) {
		capacity = N;
		divisor = M;
		table = new entry[capacity];
	}

	void put(int key, string value) {
		int index = hashFnc(key);
		int probe = 1;
		while (table[index].valid == ISITEM && probe <= capacity) {
			index = hashFnc(index + hashFnc2(key));
			probe++;
		}
		if (probe > capacity) {
			return;
		}
		table[index] = entry(key, value);
	}

	void erase(int key) {
		int index = hashFnc(key);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == key) {
				table[index].erase();
				return;
			}
			index = hashFnc(index + hashFnc2(key));
			probe++;
		}
	}

	string find(int key) {
		int index = hashFnc(key);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == key) {	
				return table[index].value;
			}
			index = hashFnc(index + hashFnc2(key));
			probe++;
		}
		return "";
	}

};

int toHashKey(string s) {
	int hashKey = 0;
	int base = 1;
	for (int i = s.size() - 1; i >= 0; i--) {
		int value = s[i] - 'a';
		hashKey += value * base;
		base *= 26;
	}
	return hashKey;
}

int main() {
	int t;
	cin >> t;
	Hash signupTable(350003, 1007);
	Hash logTable(350003, 1007);
	int cnt = 0;
	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "signup") {
			string id;
			string pw;
			cin >> id >> pw;

			if (signupTable.find(toHashKey(id)) != "") {
				cout << "Invalid" << endl;
			}
			else {
				signupTable.put(toHashKey(id), pw);
				cout << "Submit" << endl;
			}
		}
		else if (cmd == "login") {
			string id;
			string pw;
			cin >> id >> pw;

			if (signupTable.find(toHashKey(id)) == "" || signupTable.find(toHashKey(id)) != pw) {
				cout << "Invalid" << endl;
			}
			else if (logTable.find(toHashKey(id)) != "") {
			cout << "Already" << endl;
			}
			else {
				logTable.put(toHashKey(id), pw);
				cnt++;
				cout << "Submit" << endl;
			}
		}
		else if (cmd == "logout") {
			string id;
			cin >> id;
			cnt--;
			logTable.erase(toHashKey(id));
			cout << "Submit" << endl;
		}
		else if (cmd == "online") {
			cout << cnt << endl;
		}
	}
}