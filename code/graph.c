#include "graph.h"
#include <stdlib.h>

/**
 * @brief Initializes vertices and edges
 * 
 * @param vertices_num Number of desired vertices
 * @param edges_num Number of desired vertices
 *
 * @details Allocates memory space based on sizes given as parameters
 *
 * @returns Reference to newly create Graph
 */

Graph* graph_initializer(int vertices_num, int edges_num){
	if (vertices_num >= MAX_SIZE || edges_num >= MAX_SIZE) return NULL;

	Graph *g = (Graph*) malloc(sizeof(Graph));
	g->vertices = (STRING) malloc(sizeof(char) * vertices_num + 1);
	g->edges = (STRING) malloc(sizeof(char) * edges_num + 1);


	return g;
}

void graph_add_vertice(Graph* graph, const char* vertice){
	if (graph->vertices_num >= SISE_STR) {
        printf("Error: the limit has been reached.\n");
        return;
    }
	//usar strcpy para adiconar no lugar certo
	graph->vertices_num++;

}
void graph_add_edge(Graph* graph, const char* source, const char* destination){
	int source_index = -1;
    int destination_index = -1;

	//find vertice

	//a validation
	if (source_index == -1 || destination_index == -1) {
        printf("Error: vertice not found.\n");
        return;
    }

	//conecte the edge

}


void graph_destroy(Graph* graph) {
	//ver se pode usar a função free 
    free(graph->vertices);
    free(graph->edges);
    free(graph);
}