#include <iostream>
#include <vector>
using namespace std;

vector<int> v[1001];
bool isVisited[1001];
bool connected = false;

void ans(int vertex1, int vertex2) {
	if (vertex1 == vertex2) {
		connected = true;
	}
	isVisited[vertex1] = true;
	for (int i:v[vertex1]) {
		if (!isVisited[i]) {
			ans(i, vertex2);
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
		connected = false;
		int c, v;
		cin >> c >> v;
		ans(c, v);
		if (connected) {
			cout << "True" << endl;
		}
		else {
			cout << "False" << endl;
		}
	}
}