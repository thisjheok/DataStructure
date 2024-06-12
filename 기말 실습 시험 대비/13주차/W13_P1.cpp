#include <iostream>
#include <vector>
using namespace std;
// 구조체 vertex 정의
struct vertex {
    int vertexId;   // 정점의 고유 번호
    int matrixId;   // edge matrix에서 정점의 인덱스 번호
    vertex* prev;   // 이전 vertex 포인터
    vertex* next;   // 다음 vertex 포인터

    // 기본 생성자
    vertex() {
        vertexId = matrixId = -1; // 초기값 설정
        prev = next = NULL;       // 포인터 초기화
    }

    // 생성자
    vertex(int vertexId) {
        this->vertexId = vertexId;
        matrixId = -1;
        prev = next = NULL;
    }
};

// 구조체 edge 정의
struct edge {
    vertex* src;    // 시작 정점 포인터
    vertex* dst;    // 도착 정점 포인터
    edge* prev;     // 이전 edge 포인터
    edge* next;     // 다음 edge 포인터

    // 기본 생성자
    edge() {
        src = dst = NULL;
        prev = next = NULL;
    }

    // 생성자
    edge(vertex* src, vertex* dst) {
        this->src = src;
        this->dst = dst;
        prev = next = NULL;
    }
};

// 클래스 vertexList 정의
class vertexList {
private:
    vertex* header;   // 헤더 포인터
    vertex* trailer;  // 트레일러 포인터
public:

    // 생성자
    vertexList() {
        header = new vertex();
        trailer = new vertex();
        header->next = trailer;
        header->matrixId = -1;
        trailer->prev = header;
    }

    // 정점 삽입 함수
    void insertVertex(vertex* newVertex) {
        newVertex->prev = trailer->prev;
        newVertex->next = trailer;
        trailer->prev->next = newVertex;
        newVertex->matrixId = trailer->prev->matrixId + 1; // 새로운 matrix ID 할당
        trailer->prev = newVertex;
    }

    // 정점 삭제 함수
    void eraseVertex(vertex* delVertex) {
        for (vertex* cur = delVertex; cur != trailer; cur = cur->next) {
            cur->matrixId--;
        }
        delVertex->prev->next = delVertex->next;
        delVertex->next->prev = delVertex->prev;
        delete delVertex;
    }

    // 정점 찾기 함수
    vertex* findVertex(int vertexId) {
        for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
            if (cur->vertexId == vertexId) {
                return cur;
            }
        }
        return NULL;
    }

    vertex* findMinVertex() {
        int min = 10000;
        vertex* minV = NULL;
        for (vertex* cur = header->next; cur != trailer; cur = cur->next) {
            if (cur->vertexId < min) {
                minV = cur;
                min = cur->vertexId;
            }
        }
        return minV;
    }
};

// 클래스 edgeList 정의
class edgeList {
private:
    edge* header;   // 헤더 포인터
    edge* trailer;  // 트레일러 포인터
public:

    // 생성자
    edgeList() {
        header = new edge();
        trailer = new edge();
        header->next = trailer;
        trailer->prev = header;
    }

    // 간선 삽입 함수
    void insertEdge(edge* newEdge) {
        newEdge->prev = trailer->prev;
        newEdge->next = trailer;
        trailer->prev->next = newEdge;
        trailer->prev = newEdge;
    }

    // 간선 삭제 함수
    void eraseEdge(edge* delEdge) {
        delEdge->prev->next = delEdge->next;
        delEdge->next->prev = delEdge->prev;
        delete delEdge;
    }
};

// 클래스 graph 정의
class graph {
private:
    vector<vector<edge*>> edgeMatrix; // 간선의 수를 저장하는 이차원 벡터
    vertexList vList;                 // 정점을 저장하는 리스트
    edgeList eList;                   // 간선을 저장하는 리스트
public:

    // 정점 삽입 함수
    void insertVertex(int vertexId) {
        if (vList.findVertex(vertexId) != NULL) {
            cout << "Exist" << endl;
            return;
        }
        vertex* newVertex = new vertex(vertexId);
        for (int i = 0; i < edgeMatrix.size(); i++) {
            edgeMatrix[i].push_back(NULL);
        }
        edgeMatrix.push_back(vector<edge*>(edgeMatrix.size() + 1, NULL));
        vList.insertVertex(newVertex);
    }

    void eraseVertex(int vertexId) {
        vertex* delVertex = vList.findVertex(vertexId);
        if (delVertex == NULL) {
            return;
        }

        int matrixId = delVertex->matrixId;
        // 삭제할 정점이 포함된 간선 정보 삭제
        for (int i = 0; i < edgeMatrix.size(); i++) {
            if (i != matrixId) {
                if (edgeMatrix[i][matrixId] != NULL) {
                    eList.eraseEdge(edgeMatrix[i][matrixId]);
                }
                edgeMatrix[i].erase(edgeMatrix[i].begin()+matrixId);
            }
        }

        // 간선 매트릭스에서 해당 정점 관련 정보 제거
        edgeMatrix.erase(edgeMatrix.begin() + matrixId);
        // 정점 리스트에서 정점 삭제
        vList.eraseVertex(delVertex);
    }

    void insertEdge(int srcVertexId, int dstVertexId) {
        vertex* src = vList.findVertex(srcVertexId);
        vertex* dst = vList.findVertex(dstVertexId);
        if (src == NULL || dst == NULL) {
            return; // 정점 존재 확인
        }

        int srcMatrixId = src->matrixId;
        int dstMatrixId = dst->matrixId;

        // 양방향 간선 확인
        if (edgeMatrix[srcMatrixId][dstMatrixId] != NULL || edgeMatrix[dstMatrixId][srcMatrixId] != NULL) {
            cout << "Exist" << endl;
            return;
        }

        // 양방향 간선 삽입
        edge* newEdge = new edge(src, dst);
        eList.insertEdge(newEdge);
        edgeMatrix[srcMatrixId][dstMatrixId] = newEdge;
        edgeMatrix[dstMatrixId][srcMatrixId] = newEdge; // 추가
    }

    void eraseEdge(int srcVertexId, int dstVertexId) {
        vertex* src = vList.findVertex(srcVertexId);
        vertex* dst = vList.findVertex(dstVertexId);
        if (src == NULL || dst == NULL) {
            return; // 정점 존재 확인
        }

        int srcMatrixId = src->matrixId;
        int dstMatrixId = dst->matrixId;

        if (edgeMatrix[srcMatrixId][dstMatrixId] == NULL && edgeMatrix[dstMatrixId][srcMatrixId] == NULL) {
            cout << "None" << endl;
            return;
        }

        // 양방향 간선 삭제
        eList.eraseEdge(edgeMatrix[srcMatrixId][dstMatrixId]);
        edgeMatrix[srcMatrixId][dstMatrixId] = NULL;
        edgeMatrix[dstMatrixId][srcMatrixId] = NULL; // 추가
    }
    void IsAdjacent(int vertexId1,int vertexId2) {
        vertex* v1 = vList.findVertex(vertexId1);
        vertex* v2 = vList.findVertex(vertexId2);
        if (v1 == NULL) {
            cout << "None" << endl;
            return; // 정점이 존재하지 않는 경우
        }
        bool isadja = false;
        int matrixId1 = v1->matrixId; // 현재 정점의 matrixId 조회
        int matrixId2 = v2->matrixId; // 현재 정점의 matrixId 조회

        if (edgeMatrix[matrixId1][matrixId2] != NULL){
                isadja = true; 
        }  

        int deg1 = 0;
        int deg2 = 0;
        for (int i = 0; i < edgeMatrix[matrixId1].size(); i++) {
            if (edgeMatrix[matrixId1][i] != NULL) { // 자기 자신을 제외
                 deg1++;
            }
        }
        for (int i = 0; i < edgeMatrix[matrixId2].size(); i++) {
            if (edgeMatrix[matrixId2][i] != NULL) { // 자기 자신을 제외
                deg2++;
            }
        }

        if (isadja == true) {
            cout << "True "; 
            if (deg1 > deg2) {
                cout << vertexId2 << endl;
            }
            else if (deg1 < deg2) {
                cout << vertexId1 << endl;
            }
            else {
                if (vertexId1 > vertexId2) {
                    cout << vertexId2 << endl;
                }
                else {
                    cout << vertexId1 << endl;
                }
            }
        }
        else {
            cout << "False ";
            if (deg1 > deg2) {
                cout << vertexId2 << endl;
            }
            else if (deg1 < deg2) {
                cout << vertexId1 << endl;
            }
            else {
                if (vertexId1 > vertexId2) {
                    cout << vertexId2 << endl;
                }
                else {
                    cout << vertexId1 << endl;
                }
            }
        }
    }

    void minVertexInfo() {
        vertex* v = vList.findMinVertex();
        if (v == NULL) {
            cout << -1 << endl;
            return; // 정점이 존재하지 않는 경우
        }
        int deg1 = 0;
        int matrixId1 = v->matrixId; // 현재 정점의 matrixId 조회
        for (int i = 0; i < edgeMatrix[matrixId1].size(); i++) {
            if (edgeMatrix[matrixId1][i] != NULL && i != matrixId1) { // 자기 자신을 제외
                deg1++;
            }
        }
        cout << v->vertexId << " " << deg1 << endl;
    }
      

};

int main() {
    graph G;
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "insertEdge") {
            int s, d;
            cin >> s >> d;
            G.insertEdge(s, d);
        }
        else if (cmd == "eraseEdge") {
            int s, d;
            cin >> s >> d;
            G.eraseEdge(s, d);
        }
        else if (cmd == "insertVertex") {
            int s;
            cin >> s;
            G.insertVertex(s);
        }
        else if (cmd == "eraseVertex") {
            int s;
            cin >> s;
            G.eraseVertex(s);
        }
        else if (cmd == "isAdjacent") {
            int s,d;
            cin >> s>>d;
            G.IsAdjacent(s,d);
        }
        else if (cmd == "minVertexInfo") {
            G.minVertexInfo();
        }
    }
}