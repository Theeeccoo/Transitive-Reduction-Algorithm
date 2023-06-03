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
	#define STRING		char*
	#define SISE_STR	30
	#define MAX_SIZE	1000
	/**@}*/

	typedef struct Graph {
		/**
		 * @name Graph general variables
		 */
		/**@{*/
		STRING	vertices;
		STRING	edges;
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
extern Graph* graph_initializer(int, int);
extern void graph_add_vertice(Graph* graph, const char* vertice);
extern void graph_add_edge(Graph* graph, const char* source, const char* destination);
extern void graph_destroy(Graph* graph);
/**@}*/
