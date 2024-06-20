#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m, d;
	cin >> n >> m >> d;

	vector<vector<int>> adj(n, vector<int>(n, 0));
	vector<int> linkedAccount(n, -1);

	for (int i = 0; i < d; i++) {
		int a, b;
		cin >> a >> b;
		linkedAccount[a - 1] = b - 1;
		linkedAccount[b - 1] = a - 1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> adj[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int K, S;
		cin >> K >> S;
		K--;

		int score = 0;
		int count = 0;
		vector<int> linked;
		vector<bool> visited(n, false);
		visited[K] = true;

		for (int j = 0; j < n; j++) {
			if (j == linkedAccount[K]) continue;
			if (adj[K][j] == 1 && !visited[j]) {
				count++;
				score += 3;
				visited[j] = true;
				if (linkedAccount[j] != -1) linked.push_back(linkedAccount[j]);
			}
		}
		
		if (S > 1) {
			for (int j = 0; j < n; j++) {
				if (adj[K][j] == 1) {
					for (int q = 0; q < n; q++) {
						if (q == linkedAccount[K]) continue;
						if (adj[j][q] == 1 && !visited[q]) {
							score += 2;
							count++;
							visited[q] = true;
							if (linkedAccount[q] != -1)linked.push_back(linkedAccount[q]);
						}
					}
				}
			}
		}
		for (int nxt : linked) {
			if (!visited[nxt]) {
				score += 1;
				count++;
			}
		}
		if (count == 0) {
			cout << -1 << endl;
		}
		else {
			cout << count << " " << score << endl;
		}
	}
}