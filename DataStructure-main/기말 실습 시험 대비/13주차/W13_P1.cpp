#include <iostream>
#include <vector>
using namespace std;
// ����ü vertex ����
struct vertex {
    int vertexId;   // ������ ���� ��ȣ
    int matrixId;   // edge matrix���� ������ �ε��� ��ȣ
    vertex* prev;   // ���� vertex ������
    vertex* next;   // ���� vertex ������

    // �⺻ ������
    vertex() {
        vertexId = matrixId = -1; // �ʱⰪ ����
        prev = next = NULL;       // ������ �ʱ�ȭ
    }

    // ������
    vertex(int vertexId) {
        this->vertexId = vertexId;
        matrixId = -1;
        prev = next = NULL;
    }
};

// ����ü edge ����
struct edge {
    vertex* src;    // ���� ���� ������
    vertex* dst;    // ���� ���� ������
    edge* prev;     // ���� edge ������
    edge* next;     // ���� edge ������

    // �⺻ ������
    edge() {
        src = dst = NULL;
        prev = next = NULL;
    }

    // ������
    edge(vertex* src, vertex* dst) {
        this->src = src;
        this->dst = dst;
        prev = next = NULL;
    }
};

// Ŭ���� vertexList ����
class vertexList {
private:
    vertex* header;   // ��� ������
    vertex* trailer;  // Ʈ���Ϸ� ������
public:

    // ������
    vertexList() {
        header = new vertex();
        trailer = new vertex();
        header->next = trailer;
        header->matrixId = -1;
        trailer->prev = header;
    }

    // ���� ���� �Լ�
    void insertVertex(vertex* newVertex) {
        newVertex->prev = trailer->prev;
        newVertex->next = trailer;
        trailer->prev->next = newVertex;
        newVertex->matrixId = trailer->prev->matrixId + 1; // ���ο� matrix ID �Ҵ�
        trailer->prev = newVertex;
    }

    // ���� ���� �Լ�
    void eraseVertex(vertex* delVertex) {
        for (vertex* cur = delVertex; cur != trailer; cur = cur->next) {
            cur->matrixId--;
        }
        delVertex->prev->next = delVertex->next;
        delVertex->next->prev = delVertex->prev;
        delete delVertex;
    }

    // ���� ã�� �Լ�
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

// Ŭ���� edgeList ����
class edgeList {
private:
    edge* header;   // ��� ������
    edge* trailer;  // Ʈ���Ϸ� ������
public:

    // ������
    edgeList() {
        header = new edge();
        trailer = new edge();
        header->next = trailer;
        trailer->prev = header;
    }

    // ���� ���� �Լ�
    void insertEdge(edge* newEdge) {
        newEdge->prev = trailer->prev;
        newEdge->next = trailer;
        trailer->prev->next = newEdge;
        trailer->prev = newEdge;
    }

    // ���� ���� �Լ�
    void eraseEdge(edge* delEdge) {
        delEdge->prev->next = delEdge->next;
        delEdge->next->prev = delEdge->prev;
        delete delEdge;
    }
};

// Ŭ���� graph ����
class graph {
private:
    vector<vector<edge*>> edgeMatrix; // ������ ���� �����ϴ� ������ ����
    vertexList vList;                 // ������ �����ϴ� ����Ʈ
    edgeList eList;                   // ������ �����ϴ� ����Ʈ
public:

    // ���� ���� �Լ�
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
        // ������ ������ ���Ե� ���� ���� ����
        for (int i = 0; i < edgeMatrix.size(); i++) {
            if (i != matrixId) {
                if (edgeMatrix[i][matrixId] != NULL) {
                    eList.eraseEdge(edgeMatrix[i][matrixId]);
                }
                edgeMatrix[i].erase(edgeMatrix[i].begin()+matrixId);
            }
        }

        // ���� ��Ʈ�������� �ش� ���� ���� ���� ����
        edgeMatrix.erase(edgeMatrix.begin() + matrixId);
        // ���� ����Ʈ���� ���� ����
        vList.eraseVertex(delVertex);
    }

    void insertEdge(int srcVertexId, int dstVertexId) {
        vertex* src = vList.findVertex(srcVertexId);
        vertex* dst = vList.findVertex(dstVertexId);
        if (src == NULL || dst == NULL) {
            return; // ���� ���� Ȯ��
        }

        int srcMatrixId = src->matrixId;
        int dstMatrixId = dst->matrixId;

        // ����� ���� Ȯ��
        if (edgeMatrix[srcMatrixId][dstMatrixId] != NULL || edgeMatrix[dstMatrixId][srcMatrixId] != NULL) {
            cout << "Exist" << endl;
            return;
        }

        // ����� ���� ����
        edge* newEdge = new edge(src, dst);
        eList.insertEdge(newEdge);
        edgeMatrix[srcMatrixId][dstMatrixId] = newEdge;
        edgeMatrix[dstMatrixId][srcMatrixId] = newEdge; // �߰�
    }

    void eraseEdge(int srcVertexId, int dstVertexId) {
        vertex* src = vList.findVertex(srcVertexId);
        vertex* dst = vList.findVertex(dstVertexId);
        if (src == NULL || dst == NULL) {
            return; // ���� ���� Ȯ��
        }

        int srcMatrixId = src->matrixId;
        int dstMatrixId = dst->matrixId;

        if (edgeMatrix[srcMatrixId][dstMatrixId] == NULL && edgeMatrix[dstMatrixId][srcMatrixId] == NULL) {
            cout << "None" << endl;
            return;
        }

        // ����� ���� ����
        eList.eraseEdge(edgeMatrix[srcMatrixId][dstMatrixId]);
        edgeMatrix[srcMatrixId][dstMatrixId] = NULL;
        edgeMatrix[dstMatrixId][srcMatrixId] = NULL; // �߰�
    }
    void IsAdjacent(int vertexId1,int vertexId2) {
        vertex* v1 = vList.findVertex(vertexId1);
        vertex* v2 = vList.findVertex(vertexId2);
        if (v1 == NULL) {
            cout << "None" << endl;
            return; // ������ �������� �ʴ� ���
        }
        bool isadja = false;
        int matrixId1 = v1->matrixId; // ���� ������ matrixId ��ȸ
        int matrixId2 = v2->matrixId; // ���� ������ matrixId ��ȸ

        if (edgeMatrix[matrixId1][matrixId2] != NULL){
                isadja = true; 
        }  

        int deg1 = 0;
        int deg2 = 0;
        for (int i = 0; i < edgeMatrix[matrixId1].size(); i++) {
            if (edgeMatrix[matrixId1][i] != NULL) { // �ڱ� �ڽ��� ����
                 deg1++;
            }
        }
        for (int i = 0; i < edgeMatrix[matrixId2].size(); i++) {
            if (edgeMatrix[matrixId2][i] != NULL) { // �ڱ� �ڽ��� ����
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
            return; // ������ �������� �ʴ� ���
        }
        int deg1 = 0;
        int matrixId1 = v->matrixId; // ���� ������ matrixId ��ȸ
        for (int i = 0; i < edgeMatrix[matrixId1].size(); i++) {
            if (edgeMatrix[matrixId1][i] != NULL && i != matrixId1) { // �ڱ� �ڽ��� ����
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