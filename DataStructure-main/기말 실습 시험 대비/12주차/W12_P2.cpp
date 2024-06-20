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

    entry() { // �� ��Ʈ���� �����ϴ� ������
        key = 0;
        value = "";
        valid = NOITEM;
        cnt = 0;
    }

    entry(int key, string value) { // �����Ͱ� ����� ��Ʈ���� �����ϴ� ������
        this->key = key;
        this->value = value;
        valid = ISITEM;
        cnt = 0;
    }

    void erase() { // ��Ʈ���� ���¸� AVAILABLE�� �����ϴ� �Լ�
        valid = AVAILABLE;
    }
};

class DoubleHashTable {
public:
    DoubleHashTable(int N, int M);
    void put(int key, string value);
    void erase(int key);
    string find(int key);
    void toPresent(int);
    void getPresentCount(int key);

private:
    entry* table;
    int capacity;
    int divisor;
    int hashFnc(int key);
    int hashFnc2(int key);
};

DoubleHashTable::DoubleHashTable(int N, int M) {
    capacity = N;
    divisor = M;
    table = new entry[capacity];
}

int DoubleHashTable::hashFnc(int key) { return key % capacity; }

int DoubleHashTable::hashFnc2(int key) {
    return (key % (capacity - 1)) + 1; // 1�� ���ؼ� 0�� ��ȯ���� �ʵ��� ��
}
int toHashKey(string name) {
    int hashKey = 0;
    int base = 1;
    for (int i = name.size() - 1; i >= 0; i--) {
        int value = name[i] - 'a';  // 'a'�� 0���� ����
        hashKey += value * base;
        base *= 26;  // 26����
    }
    return hashKey;
}

void DoubleHashTable::put(int key, string value) {
    int baseIndex = hashFnc(key); // ù ��° �ؽ� �Լ��� �⺻ �ε��� ���
    int step = hashFnc2(key); // �� ��° �ؽ� �Լ��� ���� ũ�� ���
    int index = baseIndex;    // ���� �ε��� �ʱ�ȭ

    for (int probe = 0; probe < capacity; probe++) {
        // ISITEM�� �ƴϰų� AVAILABLE ������ ��� ���� ��ġ�� ���
        if (table[index].valid != ISITEM) {
            table[index] = entry(key, value);
            return;
        }
        // ���� �ε��� ���
        index = (index + step) % capacity;
    }
}

void DoubleHashTable::erase(int key) {
    int index = hashFnc(key);
    int probe = 1;
    while (table[index].valid != NOITEM && probe <= capacity) {
        if (table[index].valid == ISITEM && table[index].key == key) {
            table[index].erase();
            return;
        }
        index = (index + hashFnc2(key)) % capacity;
        probe++;
    }
}

string DoubleHashTable::find(int key) {
    int index = hashFnc(key);
    int probe = 1;
    while (table[index].valid != NOITEM && probe <= capacity) {
        if (table[index].valid == ISITEM && table[index].key == key) {
            return table[index].value;
        }
        index = (index + hashFnc2(key)) % capacity;
        probe++;
    }
    return "";
}

void DoubleHashTable::toPresent(int id) {
    int index = hashFnc(id);
    int probe = 1;

    while (table[index].valid != NOITEM &&probe <= capacity) { // ���̺� ��ü�� ������ Ž���� �� �ֵ��� ����
        if (table[index].valid == ISITEM && table[index].key == id) {
            table[index].cnt++;
            cout << table[index].cnt << endl;
            return;
        }
        index = (index + hashFnc2(id)) % capacity;
        probe++;
    }
    cout << -1 << endl; // ��� Ž���� �������� ���� -1 ���
}

void DoubleHashTable::getPresentCount(int key) {
    int index = hashFnc(key);
    int probe = 1;
    while (table[index].valid != NOITEM && probe <= capacity) {
        if (table[index].valid == ISITEM && table[index].key == key) {
            cout << table[index].cnt << endl;
            return;
        }
        index = (index + hashFnc2(key)) % capacity;
        probe++;
    }
    cout << -1 << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    DoubleHashTable ht(350003, 1007);
    DoubleHashTable nameToId(350003, 1007);
    for (int i = 0; i < t; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "add") {
            int n;
            string name;
            cin >> n >> name;
            ht.put(n, name);
            nameToId.put(toHashKey(name), to_string(n));
        }
        else if (cmd == "delete") {
            int n;
            cin >> n;
            string name = ht.find(n);
            ht.erase(n);
            nameToId.erase(toHashKey(name));
        }
        else if (cmd == "name") {
            int n;
            cin >> n;
            cout << ht.find(n) << endl;
        }
        else if (cmd == "number") {
            string name;
            cin >> name;
            string str = nameToId.find(toHashKey(name));
            if (str == "") {
                cout << 0 << endl;
            }
            else {
                cout << str << endl;
            }
        }
        else if (cmd == "present") {
            string name;
            cin >> name;
            string conv = nameToId.find(toHashKey(name));
            if (conv == "") {
                cout << -1 << endl;
            }
            else {
                int id = stoi(conv);
                ht.toPresent(id);
            }
        }
        else if (cmd == "count") {
            int x;
            cin >> x;
            ht.getPresentCount(x);
        }
    }
    return 0;
}