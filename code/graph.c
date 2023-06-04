#include "graph.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Initializes vertices and edges
 * 
 * @param number_of_vertices Number of desired vertices
 * @param number_of_edges Number of desired vertices
 * @param flag Flag to control insertion of edges
 *
 * @details Allocates memory space based on sizes given as parameters
 *
 * @returns Reference to newly create Graph
 */

Graph* graph_initializer(int number_of_vertices, int number_of_edges, int flag){
	if ( number_of_vertices >= MAX_AMOUNT || number_of_edges >= MAX_AMOUNT ) {
		printf("ERROR: You have reached the maximum number of vertices and edges in your Graph (%d)\n", MAX_AMOUNT);
		return NULL;
	}

	Graph *g = (Graph*) malloc( sizeof(Graph) );

	g->vertices = (STRING*) malloc( sizeof(STRING) * number_of_vertices + 1 );
	g->vertices_allocated = number_of_vertices;

	g->edges = (STRING**) malloc( sizeof(STRING*) * number_of_vertices + 1 );
	g->edges_allocated = number_of_edges;

	g->edges_neighbours = (int*) calloc( number_of_vertices, sizeof(int) );

	g->transitive_closure = (STRING**) malloc( sizeof(STRING*) * number_of_vertices + 1 );

	g->num_transitive_closure = (int*) calloc( number_of_vertices, sizeof(int) );

	g->flag = flag;

	return g;
}

/**
 * @brief Insert given vertice into graph
 *
 * @param graph Graph to have the new vertice
 * @param vertice Vertice to be inserted
 *
 * @details Receives a vertice, verify if there is free space to add it and if it is unique in our graph.
 *
 * @retuns If allocation was successfully, returns where vertice was inserted
 *         OTHERWISE, returns -1 (ERROR) 
 */

int graph_add_vertice(Graph* graph, STRING vertice){
	int	controller = -1,
		aux	   =  0,
		position   =  0;

	if ( graph->vertices_amount > graph->vertices_allocated ) {
		printf("ERROR: the limit (%d) has been reached.\n", graph->vertices_allocated);
		return controller;
	}

	if ( ( aux = graph_vertice_finder(graph, vertice) ) != -1 ) {
		printf("ERROR: vertice (%s) was already found in Graph at position: %d\n", vertice, aux);
		return controller;
	}
	
	position = graph->vertices_amount;

	// Alocatting memory on demand
	graph->vertices[position] = (STRING) malloc( sizeof(char) * STR_SIZE + 1);
	strcpy( graph->vertices[position], vertice );
	graph->vertices_amount++;

	graph->edges[position] = (STRING*) malloc( sizeof(STRING) * graph->vertices_allocated );
	graph->transitive_closure[position] = (STRING*) malloc( sizeof(STRING) * graph->vertices_allocated );
	
	return position;
}

/**
 * @brief Insert edges on given vertices
 *
 * @param graph Graph to have the new edge
 * @param first_vertice Vertice to have a new edge added
 * @param second_vertice Vertice to have a new edge added
 *
 * @details Receives two vertices in order to create a new edge between them. 
 * FLAG variable defines if the insertion will be directed or non-directed.
 * Using auxiliary array (edges_neighbours) to control the amount of neighbours that given vertice has, 
 * 	useful to know which is the next line so we can add a new neighbour.
 *
 * The position that given vertice has on Vertices Array is equal to the position of its neighbours on Edges Array
 * ( So, basically Edges Array = Actual neighbours of given vertice ) 
 *
 * @returns IF vertices not found in graph OR vertice is already in its Edges Array, return -1 (ERROR)
 * 	    OTHERWISE, return 0 (INSERTION OK)
           
 */

int graph_add_edge(Graph* graph, const char* first_vertice, const char* second_vertice){
	int	controller = -1,
		pos_first  =  0,
		pos_second =  0;

	// Vertice not found in graph
	if ( (( pos_first = graph_vertice_finder(graph, first_vertice)) == -1 ) || (( pos_second = graph_vertice_finder(graph, second_vertice)) == -1 ) )  {
		printf("ERROR: Atleast one of your vertices (%s - %s) was not found in your graph.\n", first_vertice, second_vertice);
		return controller;
	}

	// Non-direct graph 
	if ( graph->flag == NON_DIRECTED ) {
		int	first_neighbours_amount = graph->edges_neighbours[pos_first], 
			second_neighbours_amount = graph->edges_neighbours[pos_second];

		// Atleast one of the vertices is already inserted
		if( graph_edge_finder(graph, pos_first, second_vertice) != -1 || graph_edge_finder(graph, pos_second, first_vertice) != -1 ){
			printf("ERROR: One of your vertices (%s %s) was already inserted in List of Neighbours\n", first_vertice, second_vertice);
			return controller;
		}

		// Alocatting lines on demand
		graph->edges[pos_first][first_neighbours_amount]   = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );
		graph->edges[pos_second][second_neighbours_amount] = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );

		// Inserting values on lines
		strcpy( graph->edges[pos_first][first_neighbours_amount], second_vertice );
		strcpy( graph->edges[pos_second][second_neighbours_amount], first_vertice );

		// Incrementing number of neighbours that given vertice has
		graph->edges_neighbours[pos_first] += 1;
		graph->edges_neighbours[pos_second] += 1;

	} else {
		int	first_neighbours_amount = graph->edges_neighbours[pos_first];
		
		// Other vertice is already inserted
		if ( graph_edge_finder(graph, pos_first, second_vertice) != -1 ) {
			printf("ERROR: Your destination vertice (%s) is already inserted in List of Neighbours of source (%s)\n", second_vertice, first_vertice);
			return controller;
		}
		// Alocatting line on demand
		graph->edges[pos_first][first_neighbours_amount] = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );

		// Inserting value on line
		strcpy( graph->edges[pos_first][first_neighbours_amount], second_vertice );
		
		// Incrementing number of neighbours that given vertice has
		graph->edges_neighbours[pos_first] += 1;
	}

	return 0;
}


/**
 * @brief Returns, if existing, the position of given vertice
 *
 * @param graph Graph to be iterated
 * @param vertice Vertice to be found
 *
 * @details Iterate through graph vertices list until END OF MATRIX or vertice found.
 *
 * @returns IF END OF MATRIX, return -1 (Vertice not found)
 * 	    OTHERWISE, return index of give vertice
 */

int graph_vertice_finder(Graph* graph, const char* vertice) {
	int	position = -1,
		i 	 =  0;


	for ( ; i < graph->vertices_amount ; i++ ) {
		if( strcmp(graph->vertices[i], vertice) == 0 ) {
			position = i;
			return position;
		}
	}

	return position;
}

/**
 * @brief Returns, if existing, the position of given vertice's neighbours in Edge list
 * 
 * @param graph Graph to be iterated
 * @param vertice_position Position of the vertice's Neighbours list
 * @param to_be_found Vertice to be found as neighbour
 *
 * @details Iterate through vertice_position Edge list until END OF LIST or to_be_found found.
 * 
 * @returns IF END OF LIST, return -1 (Neighbour not found)
 * 	    OTHERWISE, return index of given vertice
 * 
 */

int graph_edge_finder(Graph* graph, int vertice_position, const char* to_be_found){
	int	position    = -1,
		i 	   	 	=  0,
		neighbours_amount = graph->edges_neighbours[vertice_position];


	for( ; i < neighbours_amount; i++ ){
		if( strcmp(graph->edges[vertice_position][i], to_be_found ) == 0 ) {
			position = i;
			return position;
		}
	}

	return position;
}

/**
 * @brief Constructs direct transitive closure of all graph vertices
 *
 * @param graph Graph to be iterated
 *
 * @details Using depth-first search with a stack for traversal, the direct transitive 
 *          closure of all vertices of the graph is formed.
 */
void direct_transitive_closure(Graph* graph) {
	Stack *s = initStack(graph->vertices_allocated);

	// Helper structure to know if the vertex was already inserted in the stack during traversal
	// 0 for not entered, 1 if already entered
	int *vertex_visited = (int*) calloc( graph->vertices_allocated, sizeof(int) );
	int pos = 0;
	int pos_neighboring_vertex = -1;
	int pos_current_vertex = -1;
	STRING vertice = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );

	for(int i = 0; i < graph->vertices_allocated; i++) {
		push(s, graph->vertices[i]);
		vertex_visited[i] = 1; 
	
		while ( ! isEmpty(s)) {
			// Remove top vertex from stack
			strcpy(vertice, "");
			strcpy(vertice, pop(s));
			pos_current_vertex = graph_vertice_finder(graph, vertice);
			
			if (pos_current_vertex != -1) {
				// Loop through all neighbors of vertex popped from stack
				for (int k = 0; k < graph->edges_neighbours[pos_current_vertex]; k++) {
					pos_neighboring_vertex = graph_vertice_finder(graph, graph->edges[pos_current_vertex][k]);
					
					// If neighboring vertex has already been pushed onto the stack
					if (pos_neighboring_vertex != -1 && vertex_visited[pos_neighboring_vertex] == 0) {
						// Add unvisited neighbor vertex in stack and direct transitive closure
						push(s, graph->edges[pos_current_vertex][k]);
						graph->transitive_closure[i][pos] = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );
						strcpy(graph->transitive_closure[i][pos], "");
						strcpy( graph->transitive_closure[i][pos], s->stack[s->top] );
						vertex_visited[pos_neighboring_vertex] = 1; 
						graph->num_transitive_closure[i] += 1;
						pos++;
					}
				}
			}
		}

		// Update visited vertices to the transitive closure of the next vertex
		for (int j = 0; j < graph->vertices_allocated; j++) {
			vertex_visited[j] = 0;
		}
		pos = 0;
	}
}	

void graph_print_vertices(Graph* graph){
	int	i = 0;

	printf("Vertices of your graph: \n\t");
	for( ; i < graph->vertices_amount; i++){
		printf("%s-\t", graph->vertices[i]); 
	}
	printf("\n");
}

void graph_print_edges(Graph* graph){
	int	i = 0,
		j = 0; 

	printf("Edges of your graph: \n");	

	for( ; i < graph->vertices_amount ; i++ ){
		
		printf("%s's neighbours: \n\t", graph->vertices[i]);
		int	neighbours = graph->edges_neighbours[i];
		if ( neighbours == 0 ) { printf("EMPTY\n"); }
		else {
			for( j = 0; j < neighbours; j++ ){
				printf("%s-\t", graph->edges[i][j]);
			}
		}
		printf("\n");
	}
}

void graph_print_direct_transitive_closure(Graph* graph) {
	int	i = 0,
		j = 0; 

	printf("\nDirect transitive closure of your graph: \n");	

	for( ; i < graph->vertices_amount ; i++ ){
		
		printf("%s's direct transitive closure: \n\t", graph->vertices[i]);
		int	num_vertices_transitive_closure = graph->num_transitive_closure[i];
		if ( num_vertices_transitive_closure == 0 ) { printf("EMPTY\n"); }
		else {
			for( j = 0; j < num_vertices_transitive_closure; j++ ){
				printf("%s-\t", graph->transitive_closure[i][j]);
			}
		}
		printf("\n");
	}
}

void graph_destroy(Graph* graph) {
	//ver se pode usar a função free 
	free(graph->vertices);
	free(graph->edges);
	free(graph);
}
