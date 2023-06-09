/***** =========== ****/
/***** DEFINITIONS ****/
/***** =========== ****/

/**
 * @file Transitive-Reduction/permutation.h
 *
 * @brief Struct that contains all valid paths between two vertices of a graph
 *
 */
#ifndef PERMUTATION_H_
#define PERMUTATION_H_

  /**
  * @name Permutation definitions
  */
  /**@{*/
    #define INVALID		    0		      /* Information if permuted path is invalid */
    #define VALID         1         /* Information if permuted path is valid   */
  /**@}*/

  typedef struct Paths {

    /**
     * @name General paths information
     */
    /**@{*/
    int amount_paths;             /* Number of inserted permuted paths */
    int paths_allocated;          /* Maximum number of permuted paths */
    int position_greatest_path;   /* Position of the greatest path */
    int* number_edges;				    /* Number of edges in each valid permuted path */
    STRING** paths;			          /* Vector containing the permuted valid paths */
    /**@}*/      
  } Paths;
	
#endif /* PERMUTATION_H_ */

/***** =========== ****/
/***** PROTOTYPES *****/
/***** =========== ****/
/**
 * @name Permutation operations
 */
/**@{*/
extern Paths* path_initializer(int number_of_paths);
extern int path_add(Paths* p, STRING* path, int size_path);
extern void print_paths(Paths* p);
extern int calculate_number_of_possible_paths(Graph* graph);
extern void swap(STRING first_vertice, STRING second_vertice);
extern int path_valid(STRING* path, Graph* graph, int size_path);
extern void permute(Graph* graph, STRING* sequence, Paths* paths, STRING vertex_origin, STRING destination_vertex, int size_sequence, int number_vertices_between, int index);
extern void permuted_paths (Graph* graph, Paths* paths, STRING vertex_origin, STRING destination_vertex);
extern void free_paths(Paths* paths);
extern void delete_path_disjoint(Graph* graph, Paths* paths);
extern Graph* permutation(Graph* graph);
/**@}*/