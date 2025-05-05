#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

void dijkstra(int n, vector<vector<int>>& graph, int source) {
    vector<int> dist(n, INT_MAX), parent(n, -1);
    dist[source] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Shortest path from " << source << " to " << i << ": " << dist[i] << " with path: ";
        int temp = i;
        vector<int> path;
        while (temp != -1) {
            path.push_back(temp);
            temp = parent[temp];
        }
        for (int j = path.size() - 1; j >= 0; j--) {
            cout << path[j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 4;
    vector<vector<int>> graph = {
        {0, 10, 5, 0},
        {0, 0, 2, 1},
        {0, 0, 0, 9},
        {0, 0, 0, 0}
    };
    dijkstra(n, graph, 0);
    return 0;
}
