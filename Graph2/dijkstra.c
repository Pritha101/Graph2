#include "dijkstra.h"
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

// Function to heapify the priority queue
void heapify(Item* items, int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && items[l].distance < items[smallest].distance)
        smallest = l;

    if (r < n && items[r].distance < items[smallest].distance)
        smallest = r;

    if (smallest != i) {
        swap(&items[i], &items[smallest]);
        heapify(items, n, smallest);
    }
}

// Function to extract the minimum distance vertex from the priority queue
Item extractMin(Item* items, int* n) {
    if (*n <= 0) {
        fprintf_s(stderr, "Heap underflow. Priority queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    Item root = items[0];
    items[0] = items[*n - 1];
    (*n)--;
    heapify(items, *n, 0);

    return root;
}

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf_s(stderr, "Failed to allocate memory for distance array.\n");
        return;
    }
    Item* pq = (Item*)malloc(V * sizeof(Item));
    int size = V;

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        pq[i].vertex = i;
        pq[i].distance = INT_MAX;
    }

    dist[src] = 0;
    pq[src].distance = 0;

    while (size > 0) {
        Item u = extractMin(pq, &size);

        EdgeNodePtr head = graph->edges[u.vertex].head;
        while (head != NULL) {
            int v = head->edge.to_vertex;
            int weight = head->edge.weight;

            if (dist[u.vertex] != INT_MAX && dist[u.vertex] + weight < dist[v]) {
                dist[v] = dist[u.vertex] + weight;
                for (int i = 0; i < size; i++) {
                    if (pq[i].vertex == v) {
                        pq[i].distance = dist[v];
                        break;
                    }
                }
            }

            head = head->next;
        }
    }

    // Print the distances
    printf_s("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf_s("%d\t%d\n", i, dist[i]);
    }

    // Clean up
    free(pq);
    free(dist);
}

/*
int findMinimumDistanceVertex(int* distance, int* visited, int vertices) {
    int minDistance = INT_MAX, minIndex = -1;
    for (int v = 0; v < vertices; v++) {
        if (!visited[v] && distance[v] <= minDistance) {
            minDistance = distance[v];
            minIndex = v;
        }
    }
    return minIndex;
}

bool isInMinHeap(MinHeap* minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size) {
        return true;
    }
    return false;
}


void dijkstra_array(Graph* graph, int src) {
    int vertices = graph->V;
    int distance[vertices];
    int visited[vertices];

    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[src] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        int u = findMinimumDistanceVertex(distance, visited, vertices);
        visited[u] = 1;

        EdgeNodePtr current = graph->edges[u].head;
        while (current != NULL) {
            int v = current->edge.to_vertex;
            if (!visited[v] && distance[u] != INT_MAX && distance[u] + current->edge.weight < distance[v]) {
                distance[v] = distance[u] + current->edge.weight;
            }
            current = current->next;
        }
    }

    printf_s("Vertex\t Distance from Source\n");
    for (int i = 0; i < vertices; i++) {
        printf_s("%d\t %d\n", i, distance[i]);
    }
}



void dijkstra_heap(Graph* graph, int src) {
    int V = graph->V;
    int dist[V];

    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        EdgeNodePtr pCrawl = graph->edges[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->edge.to_vertex;

            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                pCrawl->edge.weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->edge.weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    printf_s("Vertex\t Distance from source\n");
    for (int i = 0; i < V; ++i) {
        printf_s("%d\t %d\n", i, dist[i]);
    }
}*/