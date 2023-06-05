  /***** =========== ****/
 /***** DEFINITIONS ****/
/***** =========== ****/

/**
 * @file Transitive-Reduction/graph.h
 *
 * @brief Struct of a Graph
 *
 */
#ifndef GRAPH_H_
#define GRAPH_H_

	/**
	 * @name Graph definitions
	 */
	/**@{*/
	#define STRING			char*
	#define STR_SIZE		30		/* Max size of a string */
	#define MAX_AMOUNT		1000		/* Max number amount of vertices AND edges */
	#define NON_DIRECTED 		0		/* Graph not directed */
	#define DIRECTED		1		/* Graph directed */
	/**@}*/

	typedef struct Graph {

		/**
		 * @name General graph information
		 */
		/**@{*/
		int flag;				/* Information about Graph's direction of edges */
		/**@}*/

		/**
		 * @name Graph vertices information
		 */
		/**@{*/
		STRING*	 vertices;				/* Vertices values */
		int	 vertices_amount;			/* Number of vertices in Graph at the moment */
		int	 vertices_allocated;			/* Number of allocated vertices at the initialization time */		
		STRING** transitive_closure;			/* Direct transitive closure of all vertices of the graph */
		int*	 num_transitive_closure;		/* Number of vertices in transitive closure */
		/**@}*/
			

		/**
		 * @name Graph edges information
		 */
		/**@{*/
		STRING** edges;			/* Edges values */
		int	 edges_amount;		/* Number of edges in Graph at the moment */
		int	 edges_allocated;	/* Number of allocated edges at the initialization time */
		int*	 edges_neighbours;	/* Number of each vertice's neighbours */
		/**@}*/

	} Graph;


#endif /* GRAPH_H_ */

  /***** =========== ****/
 /***** PROTOTYPES *****/
/***** =========== ****/
/**
 * @name Graph operations
 */
/**@{*/
extern Graph* graph_initializer(int number_of_vertices, int number_of_edges, int flag);
extern Graph* graph_clone(Graph* graph);
extern int  graph_add_vertice(Graph* graph, STRING vertice);
extern int  graph_add_edge(Graph* graph, const char* source, const char* destination);
extern void graph_destroy(Graph* graph);
extern int  graph_vertice_finder(Graph* graph, const char* vertice);
extern int  graph_edge_finder(Graph* graph, int vertice_position, const char* to_be_found);
extern void direct_transitive_closure(Graph* graph);
extern void graph_print_direct_transitive_closure(Graph* graph);

extern void graph_print_vertices(Graph* graph);
extern void graph_print_edges(Graph* graph);
/**@}*/
