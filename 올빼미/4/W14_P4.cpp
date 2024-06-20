#include <iostream>
#include<vector>
using namespace std;

vector<int> v[1001];
bool isVisited[1001];
int connect = 1;

void ans(int vertex1) {
	isVisited[vertex1] = true;
	for (int i : v[vertex1]) {
		if (!isVisited[i]) {
			connect += 1;
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
		connect = 1;
		int c;
		cin >> c;
		ans(c);
		cout << connect << endl;
		for (int x = 0; x < 1001; x++) {
			isVisited[x] = false;
		}
	}
}