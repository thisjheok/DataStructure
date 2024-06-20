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
	int n, m, q;
	cin >> n >> m >> q;

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	for (int i = 0; i < q; i++) {
		cnt = 1;
		int c;
		cin >> c;
		ans(c);
		cout << cnt << endl;
		for (int i = 0; i < 1001; i++) {
			isVisited[i] = false;
		}
	}
}