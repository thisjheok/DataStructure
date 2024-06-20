#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M, D; // 사용자 수(N), 질의 수(M), 계정 연동 수(D)
    cin >> N >> M >> D;

    vector<vector<int>> adjMatrix(N, vector<int>(N, 0));
    vector<int> linkedAccount(N, -1); // 각 사용자의 연동된 계정 정보

    // 계정 연동 정보 입력
    for (int i = 0; i < D; i++) {
        int a, b;
        cin >> a >> b;
        linkedAccount[a - 1] = b - 1;
        linkedAccount[b - 1] = a - 1;
    }

    // 친구 관계 입력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> adjMatrix[i][j];
        }
    }

    // 질의에 대한 처리
    for (int i = 0; i < M; i++) {
        int K, S; // 질의에 대한 사용자 번호(K)와 추천 범위(S)
        cin >> K >> S;
        K--; // 0 기반 인덱스로 변환

        int score{ 0 };
        vector<int> linked;
        vector<bool> visited(N, false);
        visited[K] = true; // 자기 자신 방문 처리
        int count = 0;

        // 1단계 친구 추천
        for (int j = 0; j < N; j++) {
            if (j == linkedAccount[K]) continue;
            if (adjMatrix[K][j] == 1 && !visited[j]) {
                visited[j] = true;
                count++;
                score += 3; // 직접적인 친구에게 3점
                if (linkedAccount[j] != -1) {
                    linked.push_back(linkedAccount[j]);
                }
            }
        }

        // 2단계 친구 추천 (S가 2 이상일 때)
        if (S > 1) {
            for (int j = 0; j < N; j++) {
                if (adjMatrix[K][j] == 1) { // 1단계 친구 확인
                    for (int k = 0; k < N; k++) {
                        if (k == linkedAccount[K]) continue;
                        if (adjMatrix[j][k] == 1 && !visited[k]) {
                            visited[k] = true;
                            count++;
                            score += 2; // 친구의 친구에게 2점
                            if (linkedAccount[k] != -1) linked.push_back(linkedAccount[k]);
                        }
                    }
                }
            }
        }

        // 연동 계정이 범위 밖에 있는 경우 1점 추가
        for (int nxt : linked) {
            if (!visited[nxt]) {
                visited[nxt];
                score += 1;
                count++;
            }
        }

        // 결과 출력
        if (count == 0) {
            cout << "-1" << endl;
        }
        else {
            cout << count << " " << score << endl;
        }
    }

    return 0;
}
