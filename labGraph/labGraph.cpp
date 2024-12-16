#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Edge {
    int begin;
    int end;
};

class Node {
public:
    int id;
    int state;

    Node(int id) : id(id), state(0) {}
};

class Graph {
private:
    int adjacencyMatrix[7][7] = {
        { 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0 },
        { 0, 1, 1, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 }
    };
    vector<Node> nodes;
    stack<Edge> edges;

public:

    Graph() {
        for (int i = 0; i < 7; i++) {
            nodes.push_back(Node(i));
        }
    }

    // Обход графа в глубину (DFS)
    void DFS(int start, int target) {
        stack<int> Stack;
        Stack.push(start);
        nodes[start].state = 1;

        cout << "Обход в глубину, начиная с вершины " << start + 1 << ":\n";

        while (!Stack.empty()) {
            int nodeID = Stack.top();
            Stack.pop();

            if (nodes[nodeID].state == 2) continue;

            nodes[nodeID].state = 2;
            cout << nodeID + 1 << endl;

            for (int j = 6; j >= 0; j--) { 
                if (adjacencyMatrix[nodeID][j] == 1 && nodes[j].state == 0) {
                    Stack.push(j);
                    nodes[j].state = 1;
                    edges.push({ nodeID, j });
                    if (j == target) return;
                }
            }
        }
    }

    // Обход графа в ширину (BFS)
    void BFS(int start, int target) {
        queue<int> Queue;
        Queue.push(start);
        nodes[start].state = 1;

        cout << "Обход в ширину, начиная с вершины " << start + 1 << ":\n";

        while (!Queue.empty()) {
            int nodeID = Queue.front();
            Queue.pop();
            nodes[nodeID].state = 2;
            //cout << nodeID + 1 << endl;

            for (int j = 0; j < 7; j++) {
                if (adjacencyMatrix[nodeID][j] == 1 && nodes[j].state == 0) {
                    Queue.push(j);
                    nodes[j].state = 1;
                    edges.push({ nodeID, j });
                    if (j == target) break;
                }
            }
        }
    }


    void printPath(int target) {
        cout << "Путь до вершины " << target + 1 << ":\n" << target + 1;
        while (!edges.empty()) {
            Edge e = edges.top();
            edges.pop();
            if (e.end == target) {
                target = e.begin;
                cout << " <- " << target + 1;
            }
        }
        cout << endl;
    }

    void resetStates() {
        for (auto& node : nodes) {
            node.state = 0;
        }
        while (!edges.empty()) edges.pop();
    }
};

int main() {

    setlocale(LC_ALL, "ru");
    Graph graph;
    int req;
    cout << "Введите номер целевой вершины (1-7): ";
    cin >> req;
    req--;
    graph.BFS(0, req);
    graph.printPath(req);

    graph.resetStates(); 
    graph.DFS(0, req);
    graph.printPath(req);

    cin.get();
    cin.get();
    return 0;
}
