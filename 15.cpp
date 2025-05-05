#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void OBST(vector<string>& keys, vector<int>& p, vector<int>& q, int n) {
    vector<vector<int>> W(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> R(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++) {
        W[i][i + 1] = q[i];
        C[i][i + 1] = q[i];
        R[i][i + 1] = i;
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length;
            W[i][j] = W[i][j - 1] + p[j - 1] + q[j];
            C[i][j] = INT_MAX;

            for (int r = i; r < j; r++) {
                int cost = C[i][r] + C[r + 1][j] + W[i][j];
                if (cost < C[i][j]) {
                    C[i][j] = cost;
                    R[i][j] = r;
                }
            }
        }
    }

    // Display Weight Matrix
    cout << "Weight Matrix (W):\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << W[i][j] << " ";
        }
        cout << endl;
    }

    // Display Cost Matrix
    cout << "Cost Matrix (C):\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    // Display Root Matrix
    cout << "Root Matrix (R):\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << R[i][j] << " ";
        }
        cout << endl;
    }

    // Display the optimal binary search tree
    cout << "\nOptimal Binary Search Tree:\n";
    cout << "Root: " << R[0][n] << endl;
}

int main() {
    vector<string> keys = {"do", "if", "read", "while"};
    vector<int> p = {1, 3, 1, 3};
    vector<int> q = {1, 2, 1, 1, 3};
    int n = keys.size();

    OBST(keys, p, q, n);

    return 0;
}
