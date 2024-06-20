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
		valid = NOITEM;
		cnt = 0;
	}
	entry(int key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
		cnt = 0;
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
	Hash(int n,int m) {
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

int hashkey(string s) {
	int result = 0;
	int b = 1;
	int a;
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
	Hash id2name(350003, 1007);
	Hash name2id(350003, 1007);
	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "add") {
			int x;
			string s;
			cin >> x >> s;
			id2name.add(x, s);//학번 이름
			name2id.add(hashkey(s), to_string(x));//이름 학번
		}
		else if (cmd == "delete") {
			int x;
			cin >> x;
			string name = id2name.find(x);
			id2name.remove(x);
			name2id.remove(hashkey(name));
		}
		else if (cmd == "name") {
			int x;
			cin >> x;
			cout << id2name.find(x) << endl;
		}
		else if (cmd == "number") {
			string s;
			cin >> s;
			if (name2id.find(hashkey(s)) == "") {
				cout << 0 << endl;
			}
			else {
				cout << name2id.find(hashkey(s)) << endl;
			}
		}
		else if (cmd == "present") {
			string s;
			cin >> s;
			string str = name2id.find(hashkey(s));
			if (str == "") {
				cout << -1 << endl;
			}
			else {
				int id = stoi(str);
				id2name.toPresent(id);
			}
		}
		else if (cmd == "count") {
			int x;
			cin >> x;
			id2name.count(x);
		}
	}
}
