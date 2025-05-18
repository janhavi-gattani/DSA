#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF 99999

// Structure for adjacency list node
typedef struct Node {
    int vertex, weight;
    struct Node* next;
} Node;

// Add node to adjacency list
Node* addNode(Node* head, int v, int w) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = head;
    return newNode;
}

// Get vertex with minimum distance
int minDistance(int dist[], int visited[], int V) {
    int min = INF, index = -1;
    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

// Dijkstra using adjacency matrix
void dijkstraMatrix(int graph[MAX][MAX], int V, int src) {
    int dist[V], visited[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break; // No reachable vertex
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}

// Dijkstra using adjacency list
void dijkstraList(Node* adjList[], int V, int src) {
    int dist[V], visited[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break; // No reachable vertex
        visited[u] = 1;

        Node* temp = adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;
            if (!visited[v] && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
            temp = temp->next;
        }
    }

    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}

// Optional: Debug print adjacency list
void printAdjList(Node* adjList[], int V) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < V; i++) {
        printf("%d: ", i);
        Node* temp = adjList[i];
        while (temp != NULL) {
            printf(" -> (%d, w=%d)", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

// ----------- MAIN -------------
int main() {
    int choice, V, E, src;
    int graph[MAX][MAX] = {0};
    Node* adjList[MAX];

    // Initialize all adjacency list heads to NULL
    for (int i = 0; i < MAX; i++)
        adjList[i] = NULL;

    printf("Choose Graph Representation:\n");
    printf("1. Adjacency Matrix\n");
    printf("2. Adjacency List\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    if (choice == 1) {
        printf("Enter adjacency matrix (0 if no edge):\n");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                scanf("%d", &graph[i][j]);
            }
        }

        printf("Enter source vertex: ");
        scanf("%d", &src);
        dijkstraMatrix(graph, V, src);

    } else if (choice == 2) {
        printf("Enter number of edges: ");
        scanf("%d", &E);

        printf("Enter each edge in format (u v weight):\n");
        for (int i = 0; i < E; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            if (u >= V || v >= V) {
                printf("Invalid edge (%d, %d). Skipping.\n", u, v);
                continue;
            }
            adjList[u] = addNode(adjList[u], v, w);
            adjList[v] = addNode(adjList[v], u, w); // For undirected graph
        }

        // Optional: Show adjacency list
        // printAdjList(adjList, V);

        printf("Enter source vertex: ");
        scanf("%d", &src);
        dijkstraList(adjList, V, src);

    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
