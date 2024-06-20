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
class Hash {
private:
	int capacity;
	int divisor;
	int hashFnc(int key) {
		return key % capacity;
	}
	int hashFnc2(int key) {
		return divisor - (key % divisor);
	}
	entry* table;
public:
	Hash(int n,int m) {
		capacity = n;
		divisor = m;
		table = new entry[capacity];
	}
	void add(int X, string S) {
		int index = hashFnc(X);
		int probe = 1;
		while (table[index].valid == ISITEM && probe <= capacity) {
			index = hashFnc(index + hashFnc2(X));
			probe++;
		}
		table[index] = entry(X, S);
	}
	void remove(int X) {
		int index = hashFnc(X);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == X) {
				table[index].erase();
				return;
			}
			index = hashFnc(index + hashFnc2(X));
			probe++;
		}
	}

	string find(int X) {
		int index = hashFnc(X);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == X) {	
				return table[index].value;
			}
			index = hashFnc(index + hashFnc2(X));
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

	void count(int X) {
		int index = hashFnc(X);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == X) {
				cout << table[index].cnt << endl;
				return;
			}
			index = hashFnc(index + hashFnc2(X));
			probe++;
		}
		cout << -1 << endl;
	}
};

int main() {
	int t;
	cin >> t;
	Hash idToname(350003, 1007);
	Hash nameToid(350003, 1007);
	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
	
		if (cmd == "add") {
			int k;
			string s;
			cin >> k >> s;
			idToname.add(k, s);
			nameToid.add(toHashKey(s), to_string(k));
		}
		else if (cmd == "delete") {
			int x;
			cin >> x;
			string name = idToname.find(x);
			idToname.remove(x);//삭제하고 find하지 않도록 조심...!!!
			nameToid.remove(toHashKey(name));
		}
		else if (cmd == "name") {
			int x;
			cin >> x;
			string str = idToname.find(x);
			if (str == "") {
				cout << 0 << endl;
			}
			else {
				cout << str << endl;
			}
		}
		else if (cmd == "number") {
			string s;
			cin >> s;
			string id = nameToid.find(toHashKey(s));
			if (id == "") {
				cout << 0 << endl;
			}
			else {
				cout << id << endl;
			}
		}
		else if (cmd == "present") {
			string s;
			cin >> s;
			string strid = nameToid.find(toHashKey(s));
			if (strid == "") {
				cout << -1 << endl;
			}
			else {
				idToname.toPresent(stoi(strid));
			}
		}
		else if (cmd == "count") {
			int x;
			cin >> x;
			idToname.count(x);
		}
	}
}