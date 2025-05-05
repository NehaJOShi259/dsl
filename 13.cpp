#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adjList;

    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void DFS(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited);
            }
        }
    }

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& topoStack) {
        visited[v] = true;

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                topologicalSortUtil(neighbor, visited, topoStack);
            }
        }

        topoStack.push(v);
    }

    void topologicalSort() {
        stack<int> topoStack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, topoStack);
            }
        }

        cout << "Topological Sort: ";
        while (!topoStack.empty()) {
            cout << topoStack.top() << " ";
            topoStack.pop();
        }
        cout << endl;
    }

    void DFS_traversal() {
        vector<bool> visited(V, false);

        cout << "DFS Traversal: ";
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(i, visited);
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topologicalSort();
    g.DFS_traversal();

    return 0;
}
