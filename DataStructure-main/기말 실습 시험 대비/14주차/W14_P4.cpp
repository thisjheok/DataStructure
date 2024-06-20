#include <iostream>
#include <vector>
using namespace std;

vector<int> v[1001];
bool isVisited[1001];
int cnt = 1;

void ans(int vertex) {
	isVisited[vertex] = true;
	for (int i : v[vertex]) {
		if (!isVisited[i]) {
			cnt++;
			ans(i);
		}
	}
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int j = 0; j < m; j++) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	for (int j = 0; j < k; j++) {
		cnt = 1;
		int c;
		cin >> c;
		ans(c);
		cout << cnt << endl;
		for (int x = 0; x < 1001; x++) {
			isVisited[x] = false;
		}
	}
}