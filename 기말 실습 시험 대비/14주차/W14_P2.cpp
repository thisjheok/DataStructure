#include <iostream>
#include <vector>
using namespace std;

vector <int> v[1001];
bool isVisited[1001];
bool connnected = false;

//Connected Component를 돌면서 비교
void ans(int vertex,int vertex2) {
    if (vertex == vertex2) connnected = true; 
    isVisited[vertex] = true;
    for (int i : v[vertex]) {
        if (!isVisited[i]) {
            ans(i,vertex2);
        }
    }
}

int main() {
        int n, m, k;
        cin >> n >> m >> k;//정점, 간선, 질의 수
        //정점과 간선 삽입
        for (int j = 0; j < m; j++) {
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        for (int j = 0; j < k; j++) {
            connnected = false; 
            int c;
            cin >> c;
            int v;
            cin >> v;
            ans(c,v);
            if (connnected) {
                cout << "True" << endl;
            }
            else {
                cout << "False" << endl;
            }
            for (int x = 0; x < 1001; x++) {
                isVisited[x] = false;
            }
        }
}
