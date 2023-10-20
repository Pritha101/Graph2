#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function to create a new edge node
Edge* createEdge(int vertex, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (newEdge == NULL) {
        fprintf(stderr, "Unable to allocate memory for edge\n");
        exit(EXIT_FAILURE);
    }

    newEdge->vertex = vertex;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

// Function to create a graph of vertices V
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Unable to allocate memory for graph\n");
        exit(EXIT_FAILURE);
    }

    graph->numVertices = vertices;

    // Create an array of adjacency lists. Size of array will be V (num of vertices)
    graph->adjacencyLists = malloc(vertices * sizeof(Edge*));
    if (graph->adjacencyLists == NULL) {
        fprintf(stderr, "Unable to allocate memory for adjacency lists\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices; i++) {
        graph->adjacencyLists[i] = NULL;
    }

    return graph;
}

// Add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    Edge* newEdge = createEdge(dest, weight);
    newEdge->next = graph->adjacencyLists[src];
    graph->adjacencyLists[src] = newEdge;

    // Since the graph is undirected, add an edge from dest to src also
    newEdge = createEdge(src, weight);
    newEdge->next = graph->adjacencyLists[dest];
    graph->adjacencyLists[dest] = newEdge;
}

// Function to check if an edge already exists between two vertices
bool edgeExists(Graph* graph, int src, int dest) {
    Edge* temp = graph->adjacencyLists[src];
    while (temp) {
        if (temp->vertex == dest) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Function to generate a random connected graph
Graph* generateRandomGraph(int numVertices, int numEdges) {
    if (numEdges < numVertices - 1) {
        fprintf(stderr, "The number of edges must be at least vertices - 1 for connected graph\n");
        exit(EXIT_FAILURE);
    }

    Graph* graph = createGraph(numVertices);
    srand(time(NULL));

    for (int i = 0; i < numVertices - 1; i++) {
        int weight = rand() % 50 + 1;
        addEdge(graph, i, i + 1, weight);
        numEdges--;
    }

    while (numEdges > 0) {
        int src = rand() % numVertices;
        int dest = rand() % numVertices;
        int weight = rand() % 50 + 1;

        if (src != dest && !edgeExists(graph, src, dest)) {
            addEdge(graph, src, dest, weight);
            numEdges--;
        }
    }

    return graph;
}

// Function to print the adjacency list of graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Edge* temp = graph->adjacencyLists[v];
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (temp) {
            printf("-> %d(%d)", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}
