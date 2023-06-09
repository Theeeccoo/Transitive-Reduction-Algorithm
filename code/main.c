#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"
#include "walk.h"
#include "permutation.h"

/**
 * @brief Splits a edge string into pieces containing vertices
 *
 * @param edge to be splitted 
 *
 * @details Receives a line of edge and split it on blank spaces, ex: a-b = 1 (a) 2(b)
 *
 */
char** splitInstruction(char *edge){
    char    **splitted_string = (char**) malloc(( 2 * (sizeof(char*)) ));
    char    *delimiter = "-";
    char    *token;
    int     aux = 0;

    token = strtok(edge, delimiter);
    while( token != NULL ) {
        *splitted_string = (char*) malloc( STR_SIZE * sizeof(char) );
        strcpy(*splitted_string, token); 
        splitted_string++;
        aux++;
        token = strtok(NULL, delimiter);
    }    

    splitted_string -= aux;
    return splitted_string;
}

int main(void){
	int	vertices = 0,
		edges = 0, 
		flag = 0, 
		control = 0;
	Graph	*g = NULL; 
	Graph	*cloned = NULL;

	char	vertice[STR_SIZE],
		edge[STR_SIZE];

	STRING* split_edge;
	
	FILE *entrada = fopen("grafo3.txt", "rt");
	if (entrada == NULL) {
		printf("ERROR: Invalid opening of file\n");
	} else {
		fscanf(entrada, "%d", &vertices);
		fscanf(entrada, "%d", &edges);
		fscanf(entrada, "%d", &flag);

		// Basic verifications to make sure that the Graph can be created.
		if (vertices <= 0) {
			printf("ERROR: Graph null\n");

		} else if (edges <= 0){
			printf("ERROR: Graph without edges\n");

		} else if (flag != 0 && flag != 1){
			printf("ERROR: Invalid flag\n");

		} else {
			// Allocates memory space for graph
			g = graph_initializer(vertices, edges, flag);
		
			// g == NULL only if vertices OR edges > MAX_AMOUNT
			if ( g != NULL ) {
				// Vertex reading
				while ( ! feof(entrada) && control < vertices) {
					strcpy(vertice, "");
					fscanf(entrada, "%s", vertice);
					graph_add_vertice(g, vertice);
					control++;
				}

				// Edge reading
				control = 0;
				while ( ! feof(entrada) && control < edges) {
					strcpy(edge, "");
					fscanf(entrada, "%s", edge);
					split_edge = splitInstruction(edge);
					graph_add_edge(g, split_edge[0], split_edge[1]);
					control++;
				}
				cloned = graph_clone(g);
		                printf("ORIGINAL GRAPH\n");
				graph_print_vertices(g);
				graph_print_edges(g);


			} // Ending Graph null verification
		} // Ending Graph's variables verification
	} // Ending file properly opened verification


	// Testing direct transitive closure
	direct_transitive_closure(g);
	//graph_print_direct_transitive_closure(g);

	direct_transitive_closure(cloned);

	Graph *pTR = NULL;

		
	if ( !isCyclic(g) ) {
		clock_t start, end;
		double duration;
		int option = 0;
		printf("\nWalk 1: \nPermutate 2:\nOption: ");
		scanf("%d", &option);
		switch(option){
			case 1:
			    start = clock();
			    Graph *tr = walk(g);
			    graph_print_vertices(tr);
			    graph_print_edges(tr);
			    end = clock();
			    duration = ((double)end - start)/CLOCKS_PER_SEC;
			    printf("Time to get Transitive Reduction through Walking in seconds: %g\n", duration);
			    break;

			case 2:
			    start = clock();
			    pTR = permutation(g);
			    graph_print_vertices(pTR);
			    graph_print_edges(pTR);

			    direct_transitive_closure(pTR);
			    graph_print_direct_transitive_closure(pTR);
			    end = clock();
			    duration = ((double)end - start)/CLOCKS_PER_SEC;
			    printf("Time to get Transitive Reduction through Permutation in seconds: %g\n", duration);
			    break;

			default:
			    printf("Invalid option!!!\n");
	       }
	} else {
		printf("ERROR: Your graph contains cycle! Analysis can't be done.\n");
	} 
    /*
	if(isEqual(g, pTR) == ! NON_EQUAL) {
		printf("\nFecho transitivo direto igual \\o/\n\n");
	}*/

	fclose(entrada);
	return 0;	
}
