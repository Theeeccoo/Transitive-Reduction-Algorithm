  /***** =========== ****/
 /***** DEFINITIONS ****/
/***** =========== ****/

/**
 * @file Transitive-Reduction/stack.h
 *
 * @brief Struct of a stack
 *
 */
#ifndef STACK_H_
#define STACK_H_
	
	/**
	 * @name Stack definitions
	 */
	/**@{*/
	#define STRING			    char*   /* String */
    #define STR_SIZE		    30		/* Max size of a string */
	#define MAX_SIZE_STACK      100     /* Max size of a stack */
	/**@}*/


    typedef struct Stack {
        /**
		 * @name General stack information
		 */
		/**@{*/
        STRING* stack;        /* Stack of vertices */
        int top;              /* Pointer to the last position with a vertex in the stack */
		/**@}*/

    } Stack;

#endif /* STACK_H_ */

  /***** =========== ****/
 /***** PROTOTYPES *****/
/***** =========== ****/
/**
 * @name Stack operations
 */
/**@{*/
extern Stack* initStack(int number_of_vertices);
extern int isEmpty(Stack* s);
extern int isFull(Stack* s);
extern void push(Stack* s, STRING vertice);
extern STRING pop(Stack* s);
extern void stack_print_vertices(Stack* s);
/**@}*/


