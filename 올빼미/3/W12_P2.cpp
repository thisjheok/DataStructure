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
	int cnt;
	entry() {
		key = 0;
		value = "";
		cnt = 0;
		valid = NOITEM;
	}
	entry(int key, string value) {
		this->key = key;
		this->value = value;
		this->cnt = 0;
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

	void add(int x, string s) {
		int index = hashFnc(x);
		int probe = 1;
		while (table[index].valid == ISITEM && probe <= capacity) {
			index = hashFnc(index + hashFnc2(x));
			probe++;
		}
		table[index] = entry(x, s);
	}

	void remove(int x) {
		int index = hashFnc(x);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == x) {
				table[index].erase();
				return;
			}
			index = hashFnc(index + hashFnc2(x));
			probe++;
		}
	}

	string find(int x) {
		int index = hashFnc(x);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == x) {
				return table[index].value;
			}
			index = hashFnc(index + hashFnc2(x));
			probe++;
		}
		return "";
	}

	void toPresent(int x) {
		int index = hashFnc(x);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == x) {
				table[index].cnt++;
				cout << table[index].cnt << endl;
				return;
			}
			index = hashFnc(index + hashFnc2(x));
			probe++;
		}
			cout << -1 << endl;
	}

	void count(int x) {
		int index = hashFnc(x);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == x) {
				cout << table[index].cnt << endl;
				return;
			}
			index = hashFnc(index + hashFnc2(x));
			probe++;
		}
			cout << -1 << endl;
	}
};

int toHashKey(string s) {
	int a;
	int b = 1;
	int result = 0;
	for (int i = 0; i < s.size(); i++) {
		a = s[i] - 'a';
		result += a * b;
		b *= 26;
	}
	return result;
}

int main() {
	int t;
	cin >> t;
	Hash idToname(350003, 1007);//학번 이름
	Hash nameToid(350003, 1007);//이름 학번

	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "add") {
			int x;
			string s;
			cin >> x >> s;
			idToname.add(x, s);
			nameToid.add(toHashKey(s), to_string(x));
		}
		else if (cmd == "delete") {
			int x;
			cin >> x;
			string name = idToname.find(x);
			idToname.remove(x);
			nameToid.remove(toHashKey(name));
		}
		else if (cmd == "name") {
			int x;
			cin >> x;
			string name = idToname.find(x);
			cout << name << endl;
		}
		else if (cmd == "number") {
			string s;
			cin >> s;
			if (nameToid.find(toHashKey(s)) == "") {
				cout << 0 << endl;
			}
			else {
				cout << nameToid.find(toHashKey(s)) << endl;
			}
		}
		else if (cmd == "present") {
			string s;
			cin >> s;
			string conv = (nameToid.find(toHashKey(s)));
			if (conv == "") {
				cout << -1 << endl;
			}
			else {
				int id = stoi(conv);
				idToname.toPresent(id);
			}
		}
		else if (cmd == "count") {
			int x;
			cin >> x;
			idToname.count(x);
		}
	}
}