#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];
int visited[MAX];
int n;

int dfs(int current, int parent) {
    visited[current] = 1;

    for (int i = 0; i < n; i++) {
        if (adj[current][i]) {
            if (!visited[i]) {
                if (dfs(i, current))  // Recursive DFS
                    return 1;         // Cycle found
            }
            else if (i != parent) {
                return 1;  // Visited neighbor not parent → cycle
            }
        }
    }
    return 0;  // No cycle
}

int main() {
    int edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    // Read edges
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;  // Undirected graph
    }

    // Initialize visited array
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    // Check for cycle
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, -1)) {
                printf("Cycle detected!\n");
                return 0;
            }
        }
    }

    printf("No cycle found.\n");
    return 0;
}
