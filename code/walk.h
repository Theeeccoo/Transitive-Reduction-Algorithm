  /***** =========== ****/
 /***** DEFINITIONS ****/
/***** =========== ****/

/**
 * @file Transitive-Reduction/walk.h
 *
 * @brief Struct of a walk
 *
 */
#ifndef WALK_H_
#define WALK_H_

    /**
	 * @name Walk definitions
	 */
	/**@{*/
    #define NON_EQUAL		    0		/* Direct transitive closure is not equal*/
	/**@}*/

	
#endif /* STACK_H_ */

  /***** =========== ****/
 /***** PROTOTYPES *****/
/***** =========== ****/
/**
 * @name Walk operations
 */
/**@{*/
extern int isEqual(Graph* original, Graph* modified);
extern Graph* walk(Graph* graph);
/**@}*/