#include <stdio.h>
#include "graph.h"
#include "dijkstra.h"

int main() {
    int numVertices = 5;
    int numEdges = 8;

    Graph* graph = generateRandomGraph(numVertices, numEdges);
    printGraph(graph);

    dijkstra(graph, 0);  // Compute shortest paths from vertex 0

    return 0;
}
