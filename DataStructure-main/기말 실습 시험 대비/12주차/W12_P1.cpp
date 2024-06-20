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

    entry() {//빈 엔트리를 생성하는 생성자
        key = 0;
        value = "";
        valid = NOITEM;
    }

    entry(int key, string value) {//데이터가 저장된 엔트리를 생성하는 생성자
        this->key = key;
        this->value = value;
        valid = ISITEM;
    }

    void erase() {//엔트리의 상태를 AVAILABLE로 변경하는 함수
        valid = AVAILABLE;
    }

};

class DoubleHashTable {
public:
    DoubleHashTable(int N, int M);
    void put(int key, string value);
    void erase(int key);
    string find(int key);
    void vacant();
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
    return;
}

int DoubleHashTable::hashFnc(int key) {
    return key % capacity;
}

int DoubleHashTable::hashFnc2(int key) {
    return divisor - (key % divisor);
}

void DoubleHashTable::put(int key, string value) {
    int index = hashFnc(key);
    int fstIdx = index;
    int probe = 1;
    int secIdx;
    while (table[index].valid == ISITEM && probe <= capacity) {
        index = hashFnc(index + hashFnc2(key));
        probe++;
    }
    secIdx = index;
    if (probe > capacity) {
        secIdx = -1;
        cout << fstIdx << " " << secIdx << endl;
        return;
    }
    table[index] = entry(key, value);
    cout << fstIdx << " " << secIdx << endl;
    return;
}

void DoubleHashTable::erase(int key) {
    int index = hashFnc(key);
    int probe = 1;
    while (table[index].valid != NOITEM && probe <= capacity) {
        if (table[index].valid == ISITEM && table[index].key == key) {
            cout << table[index].value << endl;
            table[index].erase();
            return;
        }
        index = hashFnc(index + hashFnc2(key));
        probe++;
    }
    cout << "None" << endl;
    return;
}

string DoubleHashTable::find(int key) {
    int index = hashFnc(key);
    int probe = 1;

    while (table[index].valid != NOITEM && probe <= capacity) {
        if (table[index].valid == ISITEM && table[index].key == key) {
            return table[index].value;
        }
        index = hashFnc(index + hashFnc2(key));
        probe++;
    }
    return "None";
}

void DoubleHashTable::vacant() {
    int cnt = 0;
    for (int i = 0; i < capacity; i++) {
        if (table[i].valid == NOITEM || table[i].valid == AVAILABLE) {
            cnt++;
        }
    }
    cout << cnt << endl;
}

int main() {
    int t;
    cin >> t;
    int N;
    cin >> N;
    int M;
    cin >> M;
    DoubleHashTable HT(N,M);
    for (int i = 0; i < t; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "put") {
            int k;
            cin >> k;
            string s;
            cin >> s;

            HT.put(k, s);
        }
        else if (cmd == "erase") {
            int k;
            cin >> k;
            HT.erase(k);
        }
        else if (cmd == "find") {
            int k;
            cin >> k;
            cout << HT.find(k) << endl;
        }
        else if (cmd == "vacant") {
            HT.vacant();
        }
    }
}