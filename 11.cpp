#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

class UnionFind {
private:
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int kruskal(int n, vector<Edge>& edges) {
    UnionFind uf(n);
    int mstWeight = 0;
    sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) { return a.weight < b.weight; });
    
    for (const auto& edge : edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unionSets(edge.u, edge.v);
            mstWeight += edge.weight;
            cout << "Edge (" << edge.u << ", " << edge.v << ") with weight " << edge.weight << " added to MST\n";
        }
    }

    return mstWeight;
}

int main() {
    int n = 5;
    vector<Edge> edges = {{0, 1, 10}, {0, 3, 30}, {0, 4, 100}, {1, 3, 50}, {1, 2, 20}, {2, 3, 10}, {3, 4, 60}};
    int totalCost = kruskal(n, edges);
    cout << "Total cost of MST: " << totalCost << endl;
    return 0;
}
