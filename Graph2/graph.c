#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function to create a new edge node
EdgeNodePtr createEdgeNode(int to_vertex, int weight) {
    EdgeNodePtr newEdgeNode = (EdgeNodePtr)malloc(sizeof(struct edgeNode));
    if (newEdgeNode == NULL) {
        fprintf(stderr, "Unable to allocate memory for edge node\n");
        exit(EXIT_FAILURE);
    }

    newEdgeNode->edge.to_vertex = to_vertex;
    newEdgeNode->edge.weight = weight;
    newEdgeNode->next = NULL;
    return newEdgeNode;
}

// Function to create a graph of vertices V
Graph new_graph(int V) {
    Graph G;
    G.V = V;
    G.edges = (EdgeList*)malloc(V * sizeof(EdgeList));
    if (G.edges == NULL) {
        fprintf(stderr, "Unable to allocate memory for adjacency lists\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < V; i++) {
        G.edges[i].head = NULL;
    }

    return G;
}

// Add an edge to an undirected graph
void add_edge(Graph* G, int from_vertex, int to_vertex, int weight) {
    EdgeNodePtr newEdgeNode = createEdgeNode(to_vertex, weight);
    newEdgeNode->next = G->edges[from_vertex].head;
    G->edges[from_vertex].head = newEdgeNode;
}




// Function to print the adjacency list of graph
void print_graph(Graph* G) {
    for (int v = 0; v < G->V; v++) {
        EdgeNodePtr temp = G->edges[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (temp) {
            printf("-> %d(%d)", temp->edge.to_vertex, temp->edge.weight);
            temp = temp->next;
        }
        printf("\n");
    }
}
