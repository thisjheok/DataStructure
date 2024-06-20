#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m, d;
	cin >> n >> m >> d;

	vector<vector<int>> adj(n, vector<int>(n, 0));
	vector<bool> reject(n, false);

	for (int i = 0; i < d; i++) {
		int c;
		cin >> c;
		c--;
		reject[c] = true;
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
		vector<bool> visited(n, false);
		visited[K] = true;

		for (int j = 0; j < n; j++) {
			if (adj[K][j] == 1 && !visited[j]) {
				visited[j] = true;
				if (!reject[j]) {
					count++;
					score += 2;
				}
			}
		}
		if (S > 1) {
			for (int j = 0; j < n; j++) {
				if (adj[K][j] == 1) {
					for (int q = 0; q < n; q++) {
						if (adj[j][q] == 1 && !visited[q]) {
							visited[q] = true;
							if (!reject[q]) {
								count++;
								score += 1;
							}
						}
					}
				}
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