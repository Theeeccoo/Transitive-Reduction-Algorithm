#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int main(void){
	int	vertices = 0, edges = 0;


	printf("Desired ammount of vertices: ");
	scanf("%d", &vertices);
	fflush(stdin);
	printf("\nDesired ammount of edges: ");
	scanf("%d", &edges);
	fflush(stdin);

	printf("%d, %d", vertices, edges);
	Graph *g = graph_initializer(vertices, edges);
	return 0;	
}
