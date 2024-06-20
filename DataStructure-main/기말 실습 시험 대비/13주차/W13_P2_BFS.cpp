#include <iostream> 
#include <vector>
using namespace std;

// vector에서 맨 뒤에 삽입(queue에서의 enqueue)
void enqueue(vector<int>&, int);
// vector에서 맨 앞 요소를 반환하며 삭제(queue에서의 dequeue)
int dequeue(vector<int>&);

// vertexId가 1~n까지 순서대로 들어가며 삭제되는 정점이 없으므로 vertexId와 matrixId가 동일
struct vertex {
    int vertexId;
    vertex* prev;
    vertex* next;
    // 계정 연동 정보 기본은 NULL(연동된 계정이 없는상태)이며 graph class 내부의 멤버함수로 계정 연동 구현
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

// edgeList가 필요없는 문제여서 필요한 부분만 남겨뒀어요
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

// 정점이 삭제되는 경우는 없으므로 eraseVertex부분 제거
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
    // eList 제거
    vector<vector<edge*>> edgeMatrix;
    vertexList vList;
public:
    // eraseEdge, eraseVertex 제거
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
    // id2개가 주어지면 두 정점을 찾아 연동시킴
    void link(int vertexId1, int vertexId2) {
        vList.findVertex(vertexId1)->link = vList.findVertex(vertexId2);
        vList.findVertex(vertexId2)->link = vList.findVertex(vertexId1);
    }
    void BFS(int startVertexId, int limit) {
        vertex* startVertex = vList.findVertex(startVertexId);
        int size = edgeMatrix[startVertexId].size();

        vector<int> dist(size, 0);
        dist[startVertexId] = 1; // 편의상 시작정점의 거리를 1로 설정

        vector<int> queue;
        enqueue(queue, startVertexId);
        while (!queue.empty()) {
            int curVertexId = dequeue(queue);
            // 0을 제외한 모든 정점에 대해 탐색
            for (int id = 1; id < size; id++) {
                // 두 정점 사이에 간선이 있으면서 아직 정점을 방문하지 않았다면(거리 정보가 0이라면)
                if (edgeMatrix[curVertexId][id] != NULL && !dist[id]) {
                    // 해당 정점에 도달하는 최소 거리(최소 간선의 개수)는 이전 정점 + 1
                    dist[id] = dist[curVertexId] + 1;
                    enqueue(queue, id);
                }
            }
        }

        int cnt = 0, score = 0;
        // 1번 정점부터 모든 정점에 대해
        for (int id = 1; id < size; id++) {
            vertex* curVertex = vList.findVertex(id);
            // 시작 정점이거나 시작 정점의 연동된 계정이라면 제외(pdf의 5번 조건)
            if (id == startVertexId || curVertex == startVertex->link) continue;

            // 해당 정점을 방문 하였으며 (거리가 0이 아니며) 추천 범위 이내에 있는 정점이라면
            if (dist[id] && dist[id] <= limit) {
                // dist[id]가 2이면 1번의 친구관계로 이어져있으므로 3(5-2)점 추가
                // dist[id]가 3이면 2번의 친구관계로 이어져있으므로 2(5-3)점 추가
                score += (5 - dist[id]);
                cnt++;
            }
            // 추천 범위 바깥이거나 도달할 수 없는 정점이라도 추천 범위 이내에 있는 정점과 연동된 계정이라면
            else if (curVertex->link != NULL && dist[curVertex->link->vertexId] <= limit) {
                // 1점 추가
                score++;
                cnt++;
            }
        }

        // 친구가 있다면(cnt가 0이 아니라면)
        if (cnt) {
            cout << cnt << ' ' << score << '\n';
        }
        else cout << "-1\n";
    }
};

int main() {
    graph g;

    int n, m, d; cin >> n >> m >> d;

    // 정점의 vertexId와 matrixId를 동일하게 유지하기 위해 0번 정점도 삽입(자리만 차지할 뿐 실제로 탐색에 사용X)
    for (int id = 0; id <= n; id++) g.insertVertex(id);

    // 연동 정보 입력 부분
    while (d--) {
        int id1, id2; cin >> id1 >> id2;
        g.link(id1, id2);
    }

    // 0번 정점은 접근하면 안됨
    for (int id1 = 1; id1 <= n; id1++) {
        for (int id2 = 1; id2 <= n; id2++) {
            // isFriend가 1(true)이면 간선 정보 추가
            bool isFriend; cin >> isFriend;
            if (isFriend) {
                g.insertEdge(id1, id2);
            }
        }
    }

    // 시작정점의 거리를 1로 설정하였기에 limit값도 1더해서 전달해야함
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