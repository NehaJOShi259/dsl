#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

class Graph {
public:
    int V;
    vector<vector<int>> adjMatrix;

    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, INT_MAX));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void primMST(int source) {
        vector<int> key(V, INT_MAX), parent(V, -1);
        vector<bool> inMST(V, false);
        key[source] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            inMST[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != INT_MAX && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        int totalCost = 0;
        for (int i = 1; i < V; i++) {
            cout << "Edge: " << parent[i] << " - " << i << " with cost: " << adjMatrix[i][parent[i]] << endl;
            totalCost += adjMatrix[i][parent[i]];
        }
        cout << "Total cost of MST: " << totalCost << endl;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.primMST(0);

    return 0;
}
;
