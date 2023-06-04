#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

/**
 * @brief Splits a edge into pieces containing vertices
 *
 * @param edge to be splitted 
 *
 * @details Receives a line of edge and split it on blank spaces, ex: a b = 1 (a) 2(b)
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

    *splitted_string = (char*) malloc( sizeof(char) );
    strcpy(*splitted_string, "\0");
    

    splitted_string -= aux;
    return splitted_string;
}

int main(void){
	int	vertices = 0, edges = 0, flag = 0, control = 0;
	char vertice[STR_SIZE];
	char edge[STR_SIZE];
	STRING* split_edge;
	FILE *entrada = fopen("grafo.txt", "rt");

	if (entrada == NULL) {
		printf("ERROR: Invalid opening of archive\n");
	} else {
		fscanf(entrada, "%d", &vertices);
		fscanf(entrada, "%d", &edges);
		fscanf(entrada, "%d", &flag);

		if (vertices <= 0) {
			printf("ERROR: Graph null");

		} else if (edges <= 0){
			printf("ERROR: Graph without edges\n");

		} else if (flag != 0 && flag != 1){
			printf("ERROR: Invalid flag\n");

		} else {
			// Allocates memory space for graph
			Graph *g = graph_initializer(vertices, edges, flag);

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

			graph_print_vertices(g);
			graph_print_edges(g);
		}
	}
	
	fclose(entrada);
	return 0;	
}
