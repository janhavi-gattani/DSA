#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];  // Adjacency list
int visited[MAX];    // Visited array for DFS and BFS
int n;               // Number of vertices

// Add edge to the adjacency list
void addEdge(int u, int v, int isDirected) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    if (!isDirected) {
        Node* newNode2 = (Node*)malloc(sizeof(Node));
        newNode2->vertex = u;
        newNode2->next = adjList[v];
        adjList[v] = newNode2;
    }
}

// DFS function
void DFS(int v) {
    visited[v] = 1;
    printf("%d ", v);
    for (Node* temp = adjList[v]; temp; temp = temp->next)
        if (!visited[temp->vertex])
            DFS(temp->vertex);
}

// BFS function
void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
        for (Node* temp = adjList[v]; temp; temp = temp->next) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                queue[rear++] = temp->vertex;
            }
        }
    }
}

// Main function
int main() {
    int edges, u, v, isDirected;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Is the graph directed (1) or undirected (0)? ");
    scanf("%d", &isDirected);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(u, v, isDirected);
    }

    printf("\nDFS Traversal: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    DFS(0);

    printf("\nBFS Traversal: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    BFS(0);

    return 0;
}
