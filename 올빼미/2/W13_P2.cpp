#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, M, D;
	cin >> N >> M >> D;

	vector<vector<int>> adjMatrix(N, vector<int>(N, 0));
	vector<int> linkedAccount(N, -1);

	for (int i = 0; i < D; i++) {
		int a, b;
		cin >> a >> b;
		linkedAccount[a - 1] = b - 1;
		linkedAccount[b - 1] = a - 1;
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

		vector<int> linked;
		vector<bool> visited(N,false);
		int score = 0;
		int count = 0;
		visited[K] = true;

		for (int j = 0; j < N; j++) {
			if (j == linkedAccount[K]) continue;
			if (adjMatrix[K][j] == 1 && !visited[j]) {
				score += 3;
				count++;
				visited[j] = true;
				if (linkedAccount[j] != -1) linked.push_back(linkedAccount[j]);
			}
		}

		if (S > 1) {
			for (int j = 0; j < N; j++) {
				if (adjMatrix[K][j] == 1) {
					for (int q = 0; q < N; q++) {
						if (q == linkedAccount[K]) continue;
						if (adjMatrix[j][q] == 1 && !visited[q]) {
							score += 2;
							count++;
							visited[q] = true;
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