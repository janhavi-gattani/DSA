#include <stdio.h>
#define MAX 100

int graph[MAX][MAX], visited[MAX], n;

// DFS function
void DFS(int v) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < n; i++)
        if (graph[v][i] && !visited[i])
            DFS(i);
}

// BFS function
void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
        for (int i = 0; i < n; i++) {
            if (graph[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    int directed;

    // Input number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Check if the graph is directed
    printf("Is the graph directed (1) or undirected (0)? ");
    scanf("%d", &directed);

    // Input adjacency matrix
    printf("Enter the adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            // If graph is undirected, mirror the input to ensure symmetry
            if (!directed && graph[i][j])
                graph[j][i] = 1;
        }
    }

    // DFS Traversal
    printf("\nDFS Traversal: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    DFS(0);

    // BFS Traversal
    printf("\nBFS Traversal: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    BFS(0);

    return 0;
}
