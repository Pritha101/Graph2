#include "graph.h"
#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTICES 50
#define NUM_EDGES 200

int main() {
    Graph graph1 = generate_random_graph(NUM_VERTICES, NUM_EDGES, UNIFORM_WEIGHTS);
    Graph graph2 = generate_random_graph(NUM_VERTICES, NUM_EDGES, EMAIL_FREQUENCY_WEIGHTS);

    // Print the original graphs
    printf_s("Graph with Uniform Weights:\n");
    print_graph(&graph1);
    printf_s("\nGraph with Email Frequency Weights:\n");
    print_graph(&graph2);

    // Apply Dijkstra’s algorithm from a source email address node
    int sourceVertex = 0;
    printf_s("\nShortest paths from vertex %d with Uniform Weights:\n", sourceVertex);
    dijkstra(&graph1, sourceVertex);
    printf_s("\nShortest paths from vertex %d with Email Frequency Weights:\n", sourceVertex);
    dijkstra(&graph2, sourceVertex);

    // Analyze and compare the results obtained with different edge weights

    // Free allocated memory
    free_graph(&graph1);
    free_graph(&graph2);

    return 0;
}
