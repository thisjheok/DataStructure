#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, M, D;
	cin >> N >> M >> D;

	vector<vector<int>> adj(N, vector<int>(N, 0));
	vector<int> linkedAccount(N, -1);

	for (int i = 0; i < D; i++) {
		int a, b;
		cin >> a >> b;
		linkedAccount[a - 1] = b - 1;
		linkedAccount[b - 1] = a - 1;
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
		vector<int> linked;
		vector<bool> visited(N, false);
		visited[K] = true;
		int count = 0;

		for (int j = 0; j < N; j++) {
			if (linkedAccount[K] == j)continue;
			if (adj[K][j] == 1 && !visited[j]) {
				visited[j] = true;
				count++;
				score += 3;
				if (linkedAccount[j] != -1) linked.push_back(linkedAccount[j]);
			}
		}

		if (S > 1) {
			for (int j = 0; j < N; j++) {
				if (adj[K][j] == 1) {
					for (int q = 0; q < N; q++) {
						if (linkedAccount[K] == q) continue;
						if (adj[j][q] == 1 && !visited[q]) {
							visited[q] = true;
							score += 2;
							count++;
							if (linkedAccount[q] != -1) linked.push_back(linkedAccount[q]);
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