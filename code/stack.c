#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Initializing stack
 * 
 * @param number_of_vertices Number of desired vertices in stack
 *
 * @details Allocates memory space based on sizes given as parameters
 *
 * @returns Reference to newly create Stack
 */
Stack* initStack(int number_of_vertices) {
    if ( number_of_vertices >= MAX_SIZE_STACK) {
		printf("ERROR: You have reached the maximum number of vertices in your Stack (%d)\n", MAX_SIZE_STACK);
		return NULL;
	}

    Stack *s = (Stack*) malloc( sizeof(Stack) );

    s->stack = (STRING*) malloc( sizeof(STRING) * number_of_vertices + 1 );

    s->top = -1;

    return s;
}

/**
 * @brief Check if stack is empty
 * 
 * @param s Stack to be checked
 *
 * @details Information if stack is empty, 1 for empty and 0 otherwise
 *
 * @returns 1 for empty and 0 otherwise
 */
int isEmpty(Stack* s) {
    return (s->top == -1);
}

/**
 * @brief Check if stack is full
 * 
 * @param s Stack to be checked
 *
 * @details Information if stack is full, 1 for full and 0 otherwise
 *
 * @returns 1 for full and 0 otherwise
 */
int isFull(Stack* s) {
    return (s->top == MAX_SIZE_STACK - 1);
}

/**
 * @brief Insert element into stack
 * 
 * @param s         Stack that will have the inserted elements
 * @param vertice   Vertex that will be inserted into the stack
 *
 * @details Insert element into stack
 */
void push(Stack* s, STRING vertice) {
    if (isFull(s)) {
        printf("ERROR: Stack overflow\n");
        return;
    }
    s->top++;
    s->stack[s->top] = (STRING) malloc( sizeof(char) * STR_SIZE + 1);
    strcpy(s->stack[s->top], "");
    strcpy(s->stack[s->top], vertice);
}

/**
 * @brief Remove a vertex from the stack
 * 
 * @param s Stack that will have vertex removed
 *
 * @details Remove a vertex from the stack
 *
 * @returns vertex removed
 */
STRING pop(Stack* s) {
    if (isEmpty(s)) {
        printf("ERROR: Stack underflow\n");
        return "";
    }
    STRING vertice = (STRING) malloc( sizeof(char) * STR_SIZE + 1);
    strcpy(vertice, "");
    strcpy(vertice, s->stack[s->top]);
    s->top--;
    return vertice;
}

/**
 * @brief Show vertices on stack
 * 
 * @param s Stack that wants to print the vertices
 *
 * @details Show vertices on stack
 */
void stack_print_vertices(Stack* s) {
	int	i = 0;

	printf("Vertices of your stack: \n\t");
	for( ; i <= s->top; i++){
		printf("%s-\t", s->stack[i]); 
	}
	printf("\n");
}