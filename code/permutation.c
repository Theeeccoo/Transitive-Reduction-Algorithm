#include "graph.h"
#include "permutation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief   Initializes the structure containing valid permuted paths between 
 *          two vertices
 * 
 * @param number_of_paths   Maximum number of paths interchanged between two 
 *                          vertices, according to the total number of vertices
 * 
 * @details Allocates memory space for structure containing valid permuted 
 *          paths between two vertices
 *
 * @returns Reference to newly create Paths
 */

Paths* path_initializer(int number_of_paths) {

	Paths *p = (Paths*) malloc( sizeof(Paths) );

    p->position_greatest_path = -1;
    p->paths_allocated = number_of_paths;
    p->amount_paths = 0;

    p->number_edges = (int*) calloc( number_of_paths, sizeof(int) );
    p->paths = (STRING**) malloc( sizeof(STRING*) * number_of_paths);

	return p;
}

/**
 * @brief Insert path
 *
 * @param p Structure that will store the path
 * @param path Path to be inserted
 * @param size_path Number of vertices in the path
 *
 * @details Insert a path into the structure that stores the valid paths generated 
 *          by the permutation. The variable containing the position of the longest 
 *          stored path is also updated if the new path is the longest.
 * 
 * @returns IF the number of paths exceeds the maximum number, return -1 (ERROR)
 *          OTHERWISE, return 0 (INSERTION OK)
 */

int path_add(Paths* p, STRING* path, int size_path) {
    int	controller = -1;
    
    if ( p->amount_paths >= p->paths_allocated ) {
		printf("ERROR: The limit (%d) of paths has been reached.\n", p->paths_allocated);
		return controller;
	}

    // Allocate memory for an array of strings that will hold the entered path
    int	position = p->amount_paths;
    p->paths[position] = (STRING*) malloc( sizeof(STRING) * size_path);

    if (p->paths[position] != NULL) {
        for(int i = 0; i < size_path; i++) {
            // Allocate memory for vertex in path
            p->paths[position][i] = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );
            strcpy( p->paths[position][i], path[i]);
        }

        // Number of edges in the inserted path
        p->number_edges[position] = size_path - 1;

        p->amount_paths++;

        // Update variable containing position of longest path
        if (p->position_greatest_path != -1) {
            if (p->number_edges[position] > p->number_edges[p->position_greatest_path]) {
                p->position_greatest_path = position;
            }
        } else {
            p->position_greatest_path = position;
        }
    } else {
        return controller;
    }

	return 0;
}

/**
 * @brief Print all stored valid paths
 *
 * @param p Structure that contains the paths that will be printed
 *
 * @details Print all stored valid paths
 */
void print_paths(Paths* p) {
    int number_vertices = 0;

    printf("\n\nPermuted Paths:");
    for(int i = 0; i < p->amount_paths; i++) {

        printf("\nPath %d: ", (i + 1));
        number_vertices = p->number_edges[i] + 1;
        
        for (int j = 0; j < number_vertices; j++) {
            if(p->paths[i][j] != NULL) {
                printf("%s  ", p->paths[i][j]);
            }
        }
    }
    printf("\nLongest paths are in position: %d\n", p->position_greatest_path);
}

/**
 * @brief Calculates the number of all paths between two vertices
 *
 * @param graph Graph to be iterated
 *
 * @details Calculates the number of all paths between two vertices
 * 
 * @returns Number of all paths between two vertices
 */
int calculate_number_of_possible_paths(Graph* graph) {
    int amount_paths = 1;   /* Starts with 1 considering a direct edge between source vertex and destination vertex */
    int number_vertices_between = 1; /* Number of vertices between source and destination */
    int result_amount_vertices_between = 1; /* Partial result of the number of permutations with a specific number of vertices between source and destination */
    int number_permuted_vertices = graph->vertices_allocated - 2; /* As origin and destination are fixed, the number of different paths generated is related to the number of vertices that can be interchanged */

    while (number_vertices_between <= number_permuted_vertices) {
        /* Calculate the number of different paths with a given number of vertices */
        for (int i = 0; i < number_vertices_between; i++) {
            result_amount_vertices_between = result_amount_vertices_between * (number_permuted_vertices - i);
        }
        /* Add the previous result to the calculated number of permutations and restart variables to calculate a new permutation */
        amount_paths += result_amount_vertices_between;
        number_vertices_between++;
        result_amount_vertices_between = 1;
    }

    return amount_paths;
}

/**
 * @brief Swap vertices
 *
 * @param first_vertice First vertex to be swapped
 * @param second_vertice Second vertex to be swapped
 *
 * @details Swap vertices to be able to swap through path variations
 */
void swap(STRING first_vertice, STRING second_vertice) {
    STRING temp = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );
    strcpy(temp, first_vertice);
    strcpy(first_vertice, second_vertice);
    strcpy(second_vertice, temp);
}

/**
 * @brief Validate if generated permuted path is valid
 *
 * @param graph Graph that contains the real paths
 * @param path Path to be validated
 * @param size_path Size of the path that will be validated
 *
 * @details Check if each edge in the path exists in the graph, if all 
 *          edges exist the path is valid, otherwise it is invalid
 * 
 * @return Return 1 if path is valid, otherwise 0
 */
int path_valid(STRING* path, Graph* graph, int size_path) {
    int controll = 0,
        i = 0,
        first_vertice = -1,
        second_vertice = -1;

    // Check if each edge in the path exists in the graph, if any do not exist then the path is not valid
    for (i = 0; i < (size_path -1); i++) {
        first_vertice = graph_vertice_finder(graph, path[i]);

        // Check if vertex exists
        if (first_vertice != -1) {
            // Check if path exists from current vertex to next vertex in path
            second_vertice = graph_edge_finder(graph, first_vertice, path[i + 1]);
            if (second_vertice == -1) {
                i = size_path;
            }
        } else {
            i = size_path;
        }
    }

    // The entire path has been checked and the edges exist in the graph
    if (i == (size_path -1)) {
        controll = 1;
    }

    return controll;
}

/**
 * @brief Permut paths with a specified number of vertices between source and destination vertices
 *
 * @param graph Graph that contains the real paths
 * @param sequence Sequence of vertices that do not contain the source and destination vertex
 * @param paths Structure that stores the permuted valid paths
 * @param vertex_origin First vertex of the path, is the origin vertex
 * @param destination_vertex Last vertex of the path is the destination vertex
 * @param size_sequence Size of sequence that does not have source and destination vertices
 * @param number_vertices_between Number of vertices swapped between source and destination vertices
 * @param index Auxiliary variable to permute using recursion
 *
 * @details Permut the paths, parses which ones are valid, and stores the valid ones in the structure
 */
void permute(Graph* graph, STRING* sequence, Paths* paths, STRING vertex_origin, STRING destination_vertex, int size_sequence, int number_vertices_between, int index) {
    
    if (index == number_vertices_between) {
        // Reserve space in memory for a swapped path
        STRING* path = (STRING*) malloc( sizeof(STRING) * number_vertices_between + 3);
        int pos = 0;

        // Reserve space for source vertex and insert it into path
        path[0] = (STRING) malloc( sizeof(char) * (STR_SIZE + 1) );
        
        // Reserve space for vertices that are between source and destination and insert them into the path
        for (int i = 0; i < (number_vertices_between + 2); i++) {
            path[i] = (STRING) malloc( sizeof(char) * (STR_SIZE + 1) );
            if (i == 0) {
                strcpy(path[i], "");
                strcpy(path[i], vertex_origin);
            } else if (i == (number_vertices_between + 1)) {
                strcpy(path[i], "");
                strcpy(path[i], destination_vertex);
            } else {
                strcpy(path[i], "");
                strcpy(path[i], sequence[pos]);
                pos++;
            }
        }

        // If valid path it is added in structure
        if (path_valid(path, graph, number_vertices_between + 2) == VALID) {
            path_add(paths, path, number_vertices_between + 2);
        }        

        // Free up swapped path memory as a new one will be generated
        if (path != NULL) {
            for (int i = 0; i < (number_vertices_between + 2); i++) {
                if (path[i] != NULL) {
                    free(path[i]);
                }
            }
            free(path);
        }
        return;
    }

    for (int i = index; i < size_sequence; i++) {
        swap(sequence[i], sequence[index]);
        permute(graph, sequence, paths, vertex_origin, destination_vertex, size_sequence, number_vertices_between, index + 1);
        swap(sequence[i], sequence[index]);
    }
}

/**
 * @brief Permut paths with all possible combinations according to a fixed source and destination vertex
 *
 * @param graph Graph that contains the real paths
 * @param paths Structure that stores the permuted valid paths
 * @param vertex_origin First vertex of the path, is the origin vertex
 * @param destination_vertex Last vertex of the path is the destination vertex
 * 
 * @details Permut paths with all possible combinations, from no vertex from source 
 *          to destination, to all vertices in the path
 */
void permuted_paths (Graph* graph, Paths* paths, STRING vertex_origin, STRING destination_vertex) {
    int size_sequence = graph->vertices_amount - 2;
    STRING* sequence = (STRING*) malloc( sizeof(STRING) * size_sequence);
    int position_origin = graph_vertice_finder(graph, vertex_origin);
    int position_destination = graph_vertice_finder(graph, destination_vertex);
    int position_sequence = 0;
    int number_vertices_between = 0;
    
    // Form vector without origin and destination vertices
    for (int i = 0; i < graph->vertices_amount; i++) {

        if (i != position_origin && i != position_destination) {
            sequence[position_sequence] = (STRING) malloc( sizeof(char) * STR_SIZE + 1 );
            strcpy(sequence[position_sequence], graph->vertices[i]);
            position_sequence++;
        }
    }
    
    // Permuted paths with vertices between origin and destination, from 0 to the number of vertices in the sequence between origin and destination
    while(number_vertices_between <= size_sequence) {
        permute(graph, sequence, paths, vertex_origin, destination_vertex, size_sequence, number_vertices_between, 0);
        number_vertices_between++;
    }
}

/**
 * @brief Frees the memory of stored paths
 *
 * @param paths Structure that has the paths that will be released
 * 
 * @details Frees the memory of stored paths
 */
void free_paths(Paths* paths) {
    int number_vertices = 0,
        i = 0;

    // Freeing memory of each vector that contains the paths
    for( i = 0; i < paths->amount_paths; i++) {
        number_vertices = paths->number_edges[i] + 1;

        if (paths->paths[i] != NULL) {
            for (int j = 0; j < number_vertices; j++) {
                // Freeing memory from each vertex of the path
                if (paths->paths[i][j] != NULL) {
                    free(paths->paths[i][j]);
                }
            }
        }
    }

    // Reset path control variables
    paths->amount_paths = 0;
    paths->position_greatest_path = -1;

    for(i = 0; i < paths->paths_allocated; i++) {
        paths->number_edges[i] = 0;
    }
}

/**
 * @brief Checks if the paths are disjoint
 *
 * @param paths Structure containing the permuted paths
 * @param shortest_path_position Position of the shortest path that will be 
 *                               compared with the longest path
 *
 * @details If all edges of the shortest path are different from the longest 
 *          path, then the paths are disjoint.
 * 
 * @return Returns 1 if the paths are disjoint, otherwise 0
 */
int is_disjoint_path(Paths* paths, int shortest_path_position) {
    int controll = 1,
        first_vertice = -1;
    int number_edges_less = paths->number_edges[shortest_path_position];
    int number_edges_bigger = paths->number_edges[paths->position_greatest_path];

    for (int i = 0; i < number_edges_less; i++) {
        first_vertice = -1;
        for (int j = 0; j < number_edges_bigger; j++) {
            // If first vertex equals
            if (strcmp(paths->paths[shortest_path_position][i], paths->paths[paths->position_greatest_path][j]) == 0) {
                first_vertice = j;
                j = number_edges_bigger;
            }
        }

        if (first_vertice != -1) {
            for (int j = first_vertice + 1; j < number_edges_bigger; j++) {
                // If second vertex equals
                if (strcmp(paths->paths[shortest_path_position][i + 1], paths->paths[paths->position_greatest_path][j]) == 0) {
                    j = number_edges_bigger;
                    controll = 0;
                    i = number_edges_less;
                }
            }
        }
    }

    return controll;
}

/**
 * @brief Remove minor paths that are disjoint from the longest path between two vertices
 *
 * @param graph Graph that will have the paths removed
 * @param paths Structure that has the paths that will be compared if they are disjoint
 * 
 * @details If paths are disjoint then minor can be removed
 */
void delete_path_disjoint(Graph* graph, Paths* paths) {
    int i = 0,
        number_edges = 0,
        first_vertice = -1,
        second_vertice = -1;

    for (i = 0; i < paths->amount_paths; i++) {
        // Analyze path that is different from longest path
        if (i != paths->position_greatest_path) {

            // If the shortest path is disjoint from the long one, it will be removed
            if (is_disjoint_path(paths, i) == IS_DISJOINT) {

                // Remove disjoint path from graph
                number_edges = paths->number_edges[i];
                for (int j = 0; j < number_edges; j++) {
                    
                    first_vertice = graph_vertice_finder(graph, paths->paths[i][j]);
                    if (first_vertice != -1) {

                        second_vertice = graph_edge_finder(graph, first_vertice, paths->paths[i][j + 1]);

                        if (second_vertice != - 1) {
                            free_edge(graph, first_vertice, second_vertice);
                            graph->edges_amount -= 1;
                            
                            
                            // Remove the edge as if it were the opposite path, as it is an undirected graph
                            if (graph->flag == NON_DIRECTED) {
                                first_vertice = graph_vertice_finder(graph, paths->paths[i][j + 1]);

                                if (first_vertice != -1) {
                                    second_vertice = graph_edge_finder(graph, first_vertice, paths->paths[i][j]);
                                    if (second_vertice != -1) {
                                        free_edge(graph, first_vertice, second_vertice);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Transitive reduction through the permutation method
 *
 * @param graph Graph to be iterated
 *
 * @details It takes a graph and swaps the possible paths until it finds the 
 *          transitive reduction. It is swapped between all possible paths 
 *          between two vertices of the original graph, the valid paths are 
 *          filtered. Among the valid ones, the one with the greatest number 
 *          of edges is chosen between two vertices and the others that are 
 *          disjoint from this path are excluded.
 * 
 * @returns Transitive reduction of graph
 */
Graph* permutation(Graph* graph) {
    Graph* clone_graph;
    clone_graph = graph_clone(graph);

    int amount_paths = calculate_number_of_possible_paths(graph);      /* Number of all permuted paths in a graph */
    Paths* paths = path_initializer(amount_paths);

    for( int i = 0; i < (graph->vertices_amount - 1); i++ ){
        for (int j = i + 1; j < graph->vertices_amount; j++) {
            //printf("Caminhos gerados: %s - %s\n", clone_graph->vertices[i], clone_graph->vertices[j]);

            permuted_paths(clone_graph, paths, clone_graph->vertices[i], clone_graph->vertices[j]);
            //print_paths(paths);
            
            // Remove minor paths that are disjoint from the longest path if there is more than one valid permuted path
            if (paths->amount_paths > 1) {
                delete_path_disjoint(clone_graph, paths);
            }

            /*  Free up memory of the generated paths, as new permutations will be generated in the 
                structure for other source and destination vertices 
            */
            free_paths(paths);
        }
	}

    // Permut the transpose graph
    if (graph->flag == DIRECTED) {

        for( int i = graph->vertices_amount - 1; i > 0; i-- ){
            for (int j = i - 1; j >= 0; j--) {
                //printf("Caminhos gerados: %s - %s\n", clone_graph->vertices[i], clone_graph->vertices[j]);

                permuted_paths(clone_graph, paths, clone_graph->vertices[i], clone_graph->vertices[j]);
                //print_paths(paths);
                
                // Remove minor paths that are disjoint from the longest path if there is more than one valid permuted path
                if (paths->amount_paths > 1) {
                    delete_path_disjoint(clone_graph, paths);
                }

                /*  Free up memory of the generated paths, as new permutations will be generated in the 
                    structure for other source and destination vertices 
                */
                free_paths(paths);
            }
        }
    }

    return clone_graph;
}