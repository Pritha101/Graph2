#include "dijkstra.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int vertex;
    int distance;
} Item;

// Function to swap two items
void swap(Item* a, Item* b) {
    Item t = *a;
    *a = *b;
    *b = t;
}

// Standard function to heapify a subtree rooted with node i
void heapify(Item* items, int n, int i) {
    int smallest = i;  // Initialize the smallest as root
    int l = 2 * i + 1; // Left = 2*i + 1
    int r = 2 * i + 2; // Right = 2*i + 2

    // If left child is smaller than root
    if (l < n && items[l].distance < items[smallest].distance)
        smallest = l;

    // If right child is smaller than smallest so far
    if (r < n && items[r].distance < items[smallest].distance)
        smallest = r;

    // If smallest is not root
    if (smallest != i) {
        swap(&items[i], &items[smallest]);

        // Recursively heapify the affected sub-tree
        heapify(items, n, smallest);
    }
}

// Function to extract minimum distance item from priority queue
Item extractMin(Item* items, int* n) {
    if (*n == 0) {
        fprintf(stderr, "Heap underflow. Priority queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    // Store the root node
    Item root = items[0];

    // Replace root node with last node
    items[0] = items[*n - 1];
    (*n)--;

    // Heapify the root node
    heapify(items, *n, 0);

    return root;
}

void dijkstra(Graph* graph, int src) {
    int V = graph->numVertices;
    int dist[V];  // The output array. dist[i] will hold the shortest
                  // distance from src to i

    Item* priorityQueue = (Item*)malloc(V * sizeof(Item));
    int queueSize = 0;

    // Initialize all distances as INFINITE and dist[] as false
    for (int i = 0; i < V; ++i) {
        dist[i] = INT_MAX;
        priorityQueue[i].vertex = i;
        priorityQueue[i].distance = INT_MAX;
        queueSize++;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    priorityQueue[src].distance = 0;

    // Loop through all vertices in priority queue
    while (queueSize > 0) {
        // Extract the vertex with minimum distance value
        Item item = extractMin(priorityQueue, &queueSize);

        // Store the extracted vertex number
        int u = item.vertex;

        // Traverse all adjacent vertices of extracted vertex u and update
        // their distance values
        Edge* temp = graph->adjacencyLists[u];
        while (temp != NULL) {
            int v = temp->vertex;

            // If there is a shorter path to v through u
            if (dist[u] != INT_MAX && temp->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + temp->weight;

                // Update priority queue to the updated distance value
                for (int i = 0; i < queueSize; ++i) {
                    if (priorityQueue[i].vertex == v) {
                        priorityQueue[i].distance = dist[v];
                        break;
                    }
                }
            }
            temp = temp->next;
        }
    }

    // Print the constructed distance array
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
