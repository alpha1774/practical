#include <iostream>
#include <stdlib.h>
using namespace std;

int cost[10][10], i, j, k, n, m;
int qu[10], front = 0, rear = 0, v;
int visited[10];  // Only use one visited array for BFS and DFS
int stk[10], top = 0;

void BFS(int start) {
    for (int i = 0; i < n; i++) visited[i] = 0;  // Reset visited for BFS
    cout << "The BFS of the Graph is: \n";
    cout << start << " ";
    visited[start] = 1;
    qu[rear++] = start;
    
    while (front != rear) {
        int v = qu[front++];
        for (int j = 0; j < n; j++) {
            if (cost[v][j] == 1 && visited[j] == 0) {
                cout << j << " ";
                visited[j] = 1;
                qu[rear++] = j;
            }
        }
    }
    cout << endl;
}

void DFS(int start) {
    for (int i = 0; i < n; i++) visited[i] = 0;  // Reset visited for DFS
    cout << "The DFS of the Graph is: \n";
    cout << start << " ";
    visited[start] = 1;
    stk[top++] = start;
    
    while (top > 0) {
        int v = stk[--top];
        for (int j = n - 1; j >= 0; j--) {  // Explore in reverse order for DFS
            if (cost[v][j] == 1 && visited[j] == 0) {
                cout << j << " ";
                visited[j] = 1;
                stk[top++] = j;
            }
        }
    }
    cout << endl;
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;

    // Initialize adjacency matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cost[i][j] = 0;
        }
    }

    // Read edges
    cout << "\nEDGES:\n";
    for (k = 0; k < m; k++) {
        cout << "Enter edge " << k + 1 << " (in the format: vertex1 vertex2): ";
        cin >> i >> j;
        cost[i][j] = 1;
        cost[j][i] = 1; // Because the graph is undirected
    }

    // Display adjacency matrix
    cout << "The adjacency matrix of the graph is:\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << " " << cost[i][j];
        }
        cout << endl;
    }

    // BFS
    cout << "Enter initial vertex for BFS: ";
    cin >> v;
    BFS(v);

    // DFS
    cout << "Enter initial vertex for DFS: ";
    cin >> v;
    DFS(v);

    return 0;
}
