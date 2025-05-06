#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adj;

public:
    Graph(int v) : n(v), adj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void topologicalSort() {
        vector<int> inDegree(n, 0);
        for (int u = 0; u < n; u++)
            for (int v : adj[u])
                inDegree[v]++;

        queue<int> q;
        for (int i = 0; i < n; i++)
            if (inDegree[i] == 0)
                q.push(i);

        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topoOrder.push_back(u);
            for (int v : adj[u]) {
                if (--inDegree[v] == 0)
                    q.push(v);
            }
        }

        cout << "Topological Order: ";
        for (int v : topoOrder)
            cout << v << " ";
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        cout << "BFS from node " << start << ": ";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int v, e, u, w;
    cout << "Enter number of vertices: ";
    cin >> v;

    Graph g(v);

    cout << "Enter number of edges: ";
    cin >> e;
    cout << "Enter directed edges (u v):\n";
    for (int i = 0; i < e; i++) {
        cin >> u >> w;
        g.addEdge(u, w);
    }

    g.topologicalSort();

    cout << "Enter start node for BFS: ";
    cin >> u;
    g.BFS(u);

    return 0;
}
