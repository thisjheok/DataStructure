#include <iostream> 
#include <vector>
using namespace std;

// vector���� �� �ڿ� ����(queue������ enqueue)
void enqueue(vector<int>&, int);
// vector���� �� �� ��Ҹ� ��ȯ�ϸ� ����(queue������ dequeue)
int dequeue(vector<int>&);

// vertexId�� 1~n���� ������� ���� �����Ǵ� ������ �����Ƿ� vertexId�� matrixId�� ����
struct vertex {
    int vertexId;
    vertex* prev;
    vertex* next;
    // ���� ���� ���� �⺻�� NULL(������ ������ ���»���)�̸� graph class ������ ����Լ��� ���� ���� ����
    vertex* link;

    vertex() {
        vertexId = -1;
        prev = next = link = NULL;
    }
    vertex(int vertexId) {
        this->vertexId = vertexId;
        prev = next = link = NULL;
    }
};

// edgeList�� �ʿ���� �������� �ʿ��� �κи� ���ܵ׾��
struct edge {
    vertex* src;
    vertex* dst;

    edge() {
        src = dst = NULL;
    }
    edge(vertex* src, vertex* dst) {
        this->src = src;
        this->dst = dst;
    }
};

// ������ �����Ǵ� ���� �����Ƿ� eraseVertex�κ� ����
class vertexList {
private:
    vertex* header;
    vertex* trailer;
public:
    vertexList() {
        header = new vertex();
        trailer = new vertex();
        header->next = trailer;
        trailer->prev = header;
    }
    void insertVertex(vertex* newVertex) {
        newVertex->prev = trailer->prev;
        newVertex->next = trailer;
        trailer->prev->next = newVertex;
        trailer->prev = newVertex;
    }
    vertex* findVertex(int vertexId) {
        for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
            if (cur->vertexId == vertexId) {
                return cur;
            }
        }

        return NULL;
    }
};

class graph {
private:
    // eList ����
    vector<vector<edge*>> edgeMatrix;
    vertexList vList;
public:
    // eraseEdge, eraseVertex ����
    void insertVertex(int vertexId) {
        vertex* newVertex = new vertex(vertexId);

        for (int i = 0; i < edgeMatrix.size(); i++) edgeMatrix[i].push_back(NULL);
        edgeMatrix.push_back(vector<edge*>(edgeMatrix.size() + 1, NULL));

        vList.insertVertex(newVertex);
    }
    void insertEdge(int srcVertexId, int dstVertexId) {
        vertex* src = new vertex(srcVertexId);
        vertex* dst = new vertex(dstVertexId);

        if (edgeMatrix[srcVertexId][dstVertexId] != NULL || edgeMatrix[dstVertexId][srcVertexId] != NULL) {
            return;
        }

        edge* newEdge = new edge(src, dst);
        edgeMatrix[srcVertexId][dstVertexId] = edgeMatrix[dstVertexId][srcVertexId] = newEdge;
    }
    // id2���� �־����� �� ������ ã�� ������Ŵ
    void link(int vertexId1, int vertexId2) {
        vList.findVertex(vertexId1)->link = vList.findVertex(vertexId2);
        vList.findVertex(vertexId2)->link = vList.findVertex(vertexId1);
    }
    void BFS(int startVertexId, int limit) {
        vertex* startVertex = vList.findVertex(startVertexId);
        int size = edgeMatrix[startVertexId].size();

        vector<int> dist(size, 0);
        dist[startVertexId] = 1; // ���ǻ� ���������� �Ÿ��� 1�� ����

        vector<int> queue;
        enqueue(queue, startVertexId);
        while (!queue.empty()) {
            int curVertexId = dequeue(queue);
            // 0�� ������ ��� ������ ���� Ž��
            for (int id = 1; id < size; id++) {
                // �� ���� ���̿� ������ �����鼭 ���� ������ �湮���� �ʾҴٸ�(�Ÿ� ������ 0�̶��)
                if (edgeMatrix[curVertexId][id] != NULL && !dist[id]) {
                    // �ش� ������ �����ϴ� �ּ� �Ÿ�(�ּ� ������ ����)�� ���� ���� + 1
                    dist[id] = dist[curVertexId] + 1;
                    enqueue(queue, id);
                }
            }
        }

        int cnt = 0, score = 0;
        // 1�� �������� ��� ������ ����
        for (int id = 1; id < size; id++) {
            vertex* curVertex = vList.findVertex(id);
            // ���� �����̰ų� ���� ������ ������ �����̶�� ����(pdf�� 5�� ����)
            if (id == startVertexId || curVertex == startVertex->link) continue;

            // �ش� ������ �湮 �Ͽ����� (�Ÿ��� 0�� �ƴϸ�) ��õ ���� �̳��� �ִ� �����̶��
            if (dist[id] && dist[id] <= limit) {
                // dist[id]�� 2�̸� 1���� ģ������� �̾��������Ƿ� 3(5-2)�� �߰�
                // dist[id]�� 3�̸� 2���� ģ������� �̾��������Ƿ� 2(5-3)�� �߰�
                score += (5 - dist[id]);
                cnt++;
            }
            // ��õ ���� �ٱ��̰ų� ������ �� ���� �����̶� ��õ ���� �̳��� �ִ� ������ ������ �����̶��
            else if (curVertex->link != NULL && dist[curVertex->link->vertexId] <= limit) {
                // 1�� �߰�
                score++;
                cnt++;
            }
        }

        // ģ���� �ִٸ�(cnt�� 0�� �ƴ϶��)
        if (cnt) {
            cout << cnt << ' ' << score << '\n';
        }
        else cout << "-1\n";
    }
};

int main() {
    graph g;

    int n, m, d; cin >> n >> m >> d;

    // ������ vertexId�� matrixId�� �����ϰ� �����ϱ� ���� 0�� ������ ����(�ڸ��� ������ �� ������ Ž���� ���X)
    for (int id = 0; id <= n; id++) g.insertVertex(id);

    // ���� ���� �Է� �κ�
    while (d--) {
        int id1, id2; cin >> id1 >> id2;
        g.link(id1, id2);
    }

    // 0�� ������ �����ϸ� �ȵ�
    for (int id1 = 1; id1 <= n; id1++) {
        for (int id2 = 1; id2 <= n; id2++) {
            // isFriend�� 1(true)�̸� ���� ���� �߰�
            bool isFriend; cin >> isFriend;
            if (isFriend) {
                g.insertEdge(id1, id2);
            }
        }
    }

    // ���������� �Ÿ��� 1�� �����Ͽ��⿡ limit���� 1���ؼ� �����ؾ���
    while (m--) {
        int k, s; cin >> k >> s;
        g.BFS(k, s + 1);
    }
}

void enqueue(vector<int>& queue, int value) {
    queue.push_back(value);
}

int dequeue(vector<int>& queue) {
    int value = queue.front();

    queue.erase(queue.begin());

    return value;
}