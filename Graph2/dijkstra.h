#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <limits.h>

/*typedef struct {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct {
    int size;
    int capacity;
    int* pos;
    MinHeapNode** array;
} MinHeap;

MinHeapNode* newMinHeapNode(int vertex, int distance);
MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isEmpty(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, int dist);
//bool isInMinHeap(MinHeap* minHeap, int v);
*/
void dijkstra(Graph* graph, int src);

#endif