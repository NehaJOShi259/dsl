#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adj;
    vector<bool> visited;

public:
    Graph(int size) : n(size), adj(size, vector<int>(size, 0)), visited(size, false) {}

    void addEdge(int u, int v) {
        adj[u][v] = adj[v][u] = 1;
    }

    void resetVisited() {
        fill(visited.begin(), visited.end(), false);
    }

    void DFS(int v) {
        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < n; i++)
            if (adj[v][i] && !visited[i])
                DFS(i);
    }

    void BFS(int v) {
        queue<int> q;
        visited[v] = true;
        q.push(v);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (int i = 0; i < n; i++) {
                if (adj[u][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    int connectedComponents() {
        int count = 0;
        resetVisited();
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                count++;
                DFS(i);
            }
        }
        return count;
    }

    void printAdjMatrix() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << adj[i][j] << " ";
            cout << endl;
        }
    }
};

int main() {
    int v, e, u, w;
    cout << "Enter number of vertices: ";
    cin >> v;

    Graph g(v);

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; i++) {
        cin >> u >> w;
        g.addEdge(u, w);
    }

    g.printAdjMatrix();

    cout << "\nDFS traversal from node 0: ";
    g.resetVisited();
    g.DFS(0);

    cout << "\nBFS traversal from node 0: ";
    g.resetVisited();
    g.BFS(0);

    int comps = g.connectedComponents();
    cout << "\n\nIs graph connected? " << (comps == 1 ? "Yes" : "No");
    cout << "\nConnected Components: " << comps << endl;

    return 0;
}
