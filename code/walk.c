#include "graph.h"
#include "stack.h"
#include "walk.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * @brief Compares two transitive closures
 *
 * @param graph Graph to be iterated
 *
 * @details Receives two graphs and compare its transitive closures
 *
 * @returns IF EQUALS, return 1 
 * 	        OTHERWISE, return 0
 */
int isEqual(Graph* original, Graph* modified){
    int	i = 0; 

    for (; i < original->vertices_amount ; i++) {
        printf("original: %d - modified: %d\n", original->num_transitive_closure[i] , modified->num_transitive_closure[i]);
        if(original->num_transitive_closure[i] != modified->num_transitive_closure[i]) return 0;
    }
    
    return 1;
}

/**
 * @brief Transitive redction through walking method
 *
 * @param graph Graph to be iterated
 *
 * @details Receives a graph and iterates through to find transitive reduction
 * 
 * @returns Graph
 *
 */
Graph* walk(Graph* graph) {
    Graph* clone_graph;
    clone_graph = graph_clone(graph);
    int pos_non_directed = -1;
    int pos_vertice_del_non_directed = -1;
    STRING vertice_del = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );
    STRING vertice_del_non_directed = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );

    for( int i = 0; i < graph->vertices_amount ; i++ ){
		
		int	neighbours = clone_graph->edges_neighbours[i];
        for( int j = 0; j < neighbours; j++ ) {
            // Remove edge from graph and save removed edge
            strcpy(vertice_del, "");
            strcpy(vertice_del, clone_graph->edges[i][j]);
            
            if (graph->flag == NON_DIRECTED) {
                printf("nao pode entrar aqui\n");
                // Remove edge from other vertex also when graph is undirected
                pos_non_directed = graph_vertice_finder(clone_graph, clone_graph->edges[i][j]);
                if (pos_non_directed != -1) {
                    strcpy(vertice_del_non_directed, "");
                    strcpy(vertice_del_non_directed, clone_graph->vertices[i]);
                    pos_vertice_del_non_directed = graph_edge_finder(clone_graph, pos_non_directed, clone_graph->vertices[i]);
                    free(clone_graph->edges[pos_non_directed][pos_vertice_del_non_directed]);
                    strcpy(clone_graph->edges[pos_non_directed][pos_vertice_del_non_directed], "");
                    clone_graph->edges_neighbours[pos_non_directed]--;
                }
            }
            printf("vertice: %s\n", vertice_del);
            free(clone_graph->edges[i][j]);
            strcpy(clone_graph->edges[i][j], "");
            clone_graph->edges_neighbours[i]--;

            direct_transitive_closure(clone_graph);
            graph_print_direct_transitive_closure(clone_graph);

            if (isEqual(graph, clone_graph) == NON_EQUAL) {
                printf("ENTREEEEEEI; %d\n\n", isEqual(graph, clone_graph));
                // If the transitive closure is not equal to the original graph, return the edge to where it was
                clone_graph->edges[i][j] = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );
                strcpy(clone_graph->edges[i][j], "");
                strcpy(clone_graph->edges[i][j], vertice_del);
                clone_graph->edges_neighbours[i]++;
                
                if (graph->flag == NON_DIRECTED) {
                    clone_graph->edges[pos_non_directed][pos_vertice_del_non_directed] = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );
                    strcpy(clone_graph->edges[pos_non_directed][pos_vertice_del_non_directed], "");
                    strcpy(clone_graph->edges[pos_non_directed][pos_vertice_del_non_directed], vertice_del_non_directed);
                    clone_graph->edges_neighbours[pos_non_directed]++;
                }
            }
            // Release transitive closure to next iteration
            free_direct_transitive_closure(clone_graph);
        }
	}

    return clone_graph;
}
