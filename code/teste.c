#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int main(void){
	int	vertices = 0, edges = 0;


	printf("Desired ammount of vertices: ");
	scanf("%d", &vertices);
	printf("\nDesired ammount of edges: ");
	scanf("%d", &edges);

	printf("%d, %d\n", vertices, edges);
	Graph *g = graph_initializer(vertices, edges);


	graph_add_vertice(g, "a");
	graph_add_vertice(g, "b");
	graph_add_vertice(g, "c");
	graph_add_edge(g, "a", "b", 0);
	graph_add_edge(g, "a", "c", 1);
	
	graph_print_vertices(g);
	graph_print_edges(g);

	return 0;	
}
