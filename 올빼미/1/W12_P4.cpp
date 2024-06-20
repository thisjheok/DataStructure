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
	Hash(int n, int m) {
		capacity = n;
		divisor = m;
		table = new entry[capacity];
	}
	void push(int s, string p) {
		int index = hashFnc(s);
		int probe = 1;
		while (table[index].valid == ISITEM && probe <= capacity) {
			index = hashFnc(index + hashFnc2(s));
			probe++;
		}
		table[index] = entry(s, p);
	}
	string find(int s) {
		int index = hashFnc(s);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == s) {
				return table[index].value;
			}
			probe++;
			index = hashFnc(index + hashFnc2(s));
		}
		return "";
	}
	void erase(int s) {
		int index = hashFnc(s);
		int probe = 1;
		while (table[index].valid != NOITEM && probe <= capacity) {
			if (table[index].valid == ISITEM && table[index].key == s) {
				table[index].erase();
				return;
			}
			probe++;
			index = hashFnc(index + hashFnc2(s));
		}
	}
};
int toHashKey(string s) {
	int a;
	int b = 1;
	int result = 0;
	for (int i = 0; i < s.size(); i++) {
		a = s[i] - 'a';
		result += a * b;
		b = b * 26;
	}
	return result;
}

int main() {
	int t;
	cin >> t;
	Hash signTable(350003, 1007);
	Hash logTable(350003, 1007);
	int cnt = 0;
	for (int i = 0; i < t; i++) {
		string cmd;
		cin >> cmd;
		if (cmd == "signup") {
			string s;
			string pw;
			cin >> s >> pw;
			if (signTable.find(toHashKey(s)) != "") {
				cout << "Invalid" << endl;
			}
			else {
				signTable.push(toHashKey(s), pw);
				cout << "Submit" << endl;
			}
		}
		else if (cmd == "login") {
			string s;
			string pw;
			cin >> s >> pw;
			if (signTable.find(toHashKey(s)) == "" || signTable.find(toHashKey(s)) != pw) {
				cout << "Invalid" << endl;
			}
			else if (logTable.find(toHashKey(s)) != "") {
				cout << "Already" << endl;
			}
			else {
				logTable.push(toHashKey(s), pw);
				cout << "Submit" << endl;
				cnt++;
			}
		}
		else if (cmd == "logout") {
			string s;
			cin >> s;
			logTable.erase(toHashKey(s));
			cout << "Submit" << endl;
			cnt--;
		}
		else if (cmd == "online") {
			cout << cnt << endl;
		}
	}
}