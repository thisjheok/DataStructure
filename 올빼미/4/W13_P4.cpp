#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, M, D;
	cin >> N >> M >> D;

	vector<vector<int>> adj(N, vector<int>(N, 0));
	vector<bool> reject(N, false);

	for (int i = 0; i < D; i++) {
		int c;
		cin >> c;
		c--;
		reject[c] = true;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> adj[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int K, S;
		cin >> K >> S;
		K--;

		int score = 0;
		int count = 0;
		vector<bool> visited(N, false);
		visited[K] = true;

		for (int j = 0; j < N; j++) {
			if (adj[K][j] == 1 && !visited[j]) {
				visited[j] = true;
				if (!reject[j]) {
					score+=2;
					count++;
				}
			}
		}

		if (S > 1) {
			for (int j = 0; j < N; j++) {
				if (adj[K][j] == 1) {
					for (int q = 0; q < N; q++) {
						if (adj[j][q] == 1 && !visited[q]) {
							visited[q] = true;
							if (!reject[q]) {
								score += 1;
								count++;
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