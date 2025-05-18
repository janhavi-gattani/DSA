#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent an edge
typedef struct {
    int src, dest, weight;
} Edge;

// Disjoint set (Union-Find) with path compression and union by rank
int parent[MAX], rank[MAX];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findSet(int x) {
    if (parent[x] != x)
        parent[x] = findSet(parent[x]); // Path compression
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);
    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Compare function for qsort
int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Kruskal’s algorithm
void kruskal(Edge edges[], int V, int E) {
    makeSet(V);
    qsort(edges, E, sizeof(Edge), compare);

    int totalWeight = 0;
    printf("Edge\tWeight\n");

    for (int i = 0, count = 0; i < E && count < V - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int setU = findSet(u);
        int setV = findSet(v);

        if (setU != setV) {
            printf("%d - %d\t%d\n", u, v, edges[i].weight);
            totalWeight += edges[i].weight;
            unionSet(setU, setV);
            count++;
        }
    }

    printf("Total weight of MST = %d\n", totalWeight);
}

// ------------ MAIN ------------
int main() {
    int choice, V, E = 0;
    Edge edges[MAX];

    printf("Choose Graph Representation:\n");
    printf("1. Adjacency Matrix\n");
    printf("2. Adjacency List\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    if (choice == 1) {
        int matrix[MAX][MAX];
        printf("Enter adjacency matrix (0 if no edge):\n");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        // Collect edges from upper triangle
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (matrix[i][j]) {
                    edges[E++] = (Edge){i, j, matrix[i][j]};
                }
            }
        }

        printf("\nMinimum Spanning Tree using Kruskal's (Matrix):\n");
        kruskal(edges, V, E);

    } else if (choice == 2) {
        printf("Enter number of edges: ");
        scanf("%d", &E);
        printf("Enter edges in format (src dest weight):\n");

        for (int i = 0; i < E; i++) {
            scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        }

        printf("\nMinimum Spanning Tree using Kruskal's (List):\n");
        kruskal(edges, V, E);

    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
