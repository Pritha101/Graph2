#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void insert_at_front(EdgeNodePtr* head, int to_vertex, int weight) {
    EdgeNodePtr newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        fprintf_s(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    newNode->edge.to_vertex = to_vertex;
    newNode->edge.weight = weight;
    newNode->next = *head;
    *head = newNode;
}

Graph new_graph(int V) {
    Graph G = { 0 };
    G.V = V;
    G.edges = malloc(V * sizeof(EdgeList));
    if (G.edges == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < V; i++) {
        G.edges[i].head = NULL;
    }
    return G;
}

void add_edge(Graph* G, int from_vertex, int to_vertex, int weight) {
    insert_at_front(&(G->edges[from_vertex].head), to_vertex, weight);
}


void free_graph(Graph* G) {
    for (int i = 0; i < G->V; i++) {
        EdgeNodePtr current = G->edges[i].head;
        while (current != NULL) {
            EdgeNodePtr temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(G->edges);
}

void print_graph(Graph* G) {
    printf("Graph: \n");
    for (int i = 0; i < G->V; ++i) {
        printf("Vertex %d: ", i);
        EdgeNodePtr current = G->edges[i].head;
        while (current != NULL) {
            printf("-> [%d, %d] ", current->edge.to_vertex, current->edge.weight);
            current = current->next;
        }
        printf("\n");
    }
}


int main() {
    Graph G;

    int V;
    if (scanf_s("%d", &V) != 1) {
        fprintf_s(stderr, "Invalid.\n");
        return 1;
    }


    G = new_graph(V);

    int* in_degrees = malloc(V * sizeof(int));
    if (in_degrees == NULL) {
        fprintf_s(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < V; i++) {
        int nEdges;
        if (scanf_s("%d", &nEdges) != 1) {
            fprintf_s(stderr, "Invalid.\n");
            return 1;
        }
        in_degrees[i] = 0;

        for (int j = 0; j < nEdges; j++) {
            int to_vertex, weight;
            if (scanf_s("%d,%d", &to_vertex, &weight) != 2) {
                fprintf_s(stderr, "Invalid input.\n");
                return 1;
            }
            add_edge(&G, i, to_vertex, weight);
        }
    }
    // Loop through all vertices and their edge lists to increment in-degrees
    for (int i = 0; i < V; i++) {
        EdgeNodePtr current = G.edges[i].head;
        while (current != NULL) {
            in_degrees[current->edge.to_vertex]++;
            current = current->next;
        }
    }

    print_graph(&G);

    printf("In-degrees:\n");
    for (int i = 0; i < V; i++) {
        printf("%d ", in_degrees[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(in_degrees);
    free_graph(&G);

    return 0;
}
