#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int minKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, minIndex = -1;
    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void primsMatrix(int graph[MAX][MAX], int n) {
    int parent[MAX], key[MAX], mstSet[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
}


struct Node {
    int dest, weight;
    struct Node* next;
};

struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void primsList(struct Node* adjList[], int n) {
    int key[MAX], parent[MAX], mstSet[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        struct Node* temp = adjList[u];
        while (temp) {
            int v = temp->dest;
            int weight = temp->weight;

            if (!mstSet[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d\t%d\n", parent[i], i, key[i]);
}

int main() {
    int choice, n;
    printf("Choose Graph Representation:\n");
    printf("1. Adjacency Matrix\n");
    printf("2. Adjacency List\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (choice == 1) {
        int graph[MAX][MAX];
        printf("Enter adjacency matrix (0 if no edge):\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &graph[i][j]);

        printf("\nMinimum Spanning Tree using Prim's (Matrix):\n");
        primsMatrix(graph, n);

    } else if (choice == 2) {
        struct Node* adjList[MAX];
        for (int i = 0; i < n; i++)
            adjList[i] = NULL;

        int edges, u, v, w;
        printf("Enter number of edges: ");
        scanf("%d", &edges);
        printf("Enter edges (src dest weight):\n");
        for (int i = 0; i < edges; i++) {
            scanf("%d %d %d", &u, &v, &w);
            struct Node* newNode = createNode(v, w);
            newNode->next = adjList[u];
            adjList[u] = newNode;

            newNode = createNode(u, w); // undirected
            newNode->next = adjList[v];
            adjList[v] = newNode;
        }

        printf("\nMinimum Spanning Tree using Prim's (List):\n");
        primsList(adjList, n);

    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
