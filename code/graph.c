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
