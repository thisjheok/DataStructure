#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M, D; // ����� ��(N), ���� ��(M), ���� ���� ��(D)
    cin >> N >> M >> D;

    vector<vector<int>> adjMatrix(N, vector<int>(N, 0));
    vector<int> linkedAccount(N, -1); // �� ������� ������ ���� ����

    // ���� ���� ���� �Է�
    for (int i = 0; i < D; i++) {
        int a, b;
        cin >> a >> b;
        linkedAccount[a - 1] = b - 1;
        linkedAccount[b - 1] = a - 1;
    }

    // ģ�� ���� �Է�
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> adjMatrix[i][j];
        }
    }

    // ���ǿ� ���� ó��
    for (int i = 0; i < M; i++) {
        int K, S; // ���ǿ� ���� ����� ��ȣ(K)�� ��õ ����(S)
        cin >> K >> S;
        K--; // 0 ��� �ε����� ��ȯ

        int score{ 0 };
        vector<int> linked;
        vector<bool> visited(N, false);
        visited[K] = true; // �ڱ� �ڽ� �湮 ó��
        int count = 0;

        // 1�ܰ� ģ�� ��õ
        for (int j = 0; j < N; j++) {
            if (j == linkedAccount[K]) continue;
            if (adjMatrix[K][j] == 1 && !visited[j]) {
                visited[j] = true;
                count++;
                score += 3; // �������� ģ������ 3��
                if (linkedAccount[j] != -1) {
                    linked.push_back(linkedAccount[j]);
                }
            }
        }

        // 2�ܰ� ģ�� ��õ (S�� 2 �̻��� ��)
        if (S > 1) {
            for (int j = 0; j < N; j++) {
                if (adjMatrix[K][j] == 1) { // 1�ܰ� ģ�� Ȯ��
                    for (int k = 0; k < N; k++) {
                        if (k == linkedAccount[K]) continue;
                        if (adjMatrix[j][k] == 1 && !visited[k]) {
                            visited[k] = true;
                            count++;
                            score += 2; // ģ���� ģ������ 2��
                            if (linkedAccount[k] != -1) linked.push_back(linkedAccount[k]);
                        }
                    }
                }
            }
        }

        // ���� ������ ���� �ۿ� �ִ� ��� 1�� �߰�
        for (int nxt : linked) {
            if (!visited[nxt]) {
                visited[nxt];
                score += 1;
                count++;
            }
        }

        // ��� ���
        if (count == 0) {
            cout << "-1" << endl;
        }
        else {
            cout << count << " " << score << endl;
        }
    }

    return 0;
}
