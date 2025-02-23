#pragma once

typedef struct edge {
	int to_vertex;
	int weight;
} Edge;

typedef struct edgeNode {
	Edge edge;
	struct edgeNode* next;
} *EdgeNodePtr;

typedef struct edgeList {
	EdgeNodePtr head;
} EdgeList;

typedef struct graph {
	int V;
	EdgeList* edges;
} Graph;

typedef enum {
	UNIFORM_WEIGHTS,
	EMAIL_FREQUENCY_WEIGHTS
} WeightConfig;


void insert_at_front(EdgeNodePtr* head, int to_vertex, int weight);
Graph new_graph(int V);
void add_edge(Graph* G, int from_vertex, int to_vertex, int weight);
void free_graph(Graph* G);
void print_graph(Graph* G);
//bool edgeExists(Graph* graph, int src, int dest);
Graph generate_random_graph(int numVertices, int numEdges, WeightConfig weightConfig);