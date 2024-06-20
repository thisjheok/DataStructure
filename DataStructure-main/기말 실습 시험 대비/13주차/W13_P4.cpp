#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, M, D;
	cin >> N >> M >> D;

	vector<vector<int>> adjMatrix(N, vector<int>(N, 0));
	vector<bool> reject(N, false);

	for (int i = 0; i < D; i++) {
		int K;
		cin >> K;
		K--;
		reject[K] = true;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> adjMatrix[i][j];
		}
	}

	for (int i = 0; i < M; i++) {
		int K, S;
		cin >> K >> S;
		K--;

		int score{ 0 };
		vector<bool> visited(N, false);
		visited[K] = true;
		int count = 0;

		for (int j = 0; j < N; j++) {
			if (adjMatrix[K][j] == 1 && !visited[j]) {
				visited[j] = true;
				if (!reject[j]) {
					count++;
					score += 2;
				}
			}
		}

		if (S > 1) {
			for (int j = 0; j < N; j++) {
				if (adjMatrix[K][j] == 1) {
					for (int k = 0; k < N; k++) {
						if (adjMatrix[j][k] == 1 && !visited[k]) {
							visited[k] = true;
							if (!reject[k]) {
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
	return 0;
}