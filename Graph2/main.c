#include "graph.h"
#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int V = 5; // Number of vertices in the graph

    // Create a graph
    Graph graph = new_graph(V);

    // Add edges to the graph
    add_edge(&graph, 0, 1, 10);
    add_edge(&graph, 0, 2, 3);
    add_edge(&graph, 1, 2, 1);
    add_edge(&graph, 1, 3, 7);
    add_edge(&graph, 2, 3, 5);
    add_edge(&graph, 2, 4, 8);
    add_edge(&graph, 3, 4, 2);

    // Print the graph
    printf("Graph:\n");
    print_graph(&graph);

    // Compute shortest paths from vertex 0
    printf("\nShortest paths from vertex 0:\n");
    dijkstra(&graph, 0);
    //free_graph(&graph);

    return 0;
}
