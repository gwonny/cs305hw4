/* Author: Tammy VanDeGrift
 * CS 305 HW 4
 * stack.h
 */

#ifndef STACK_H
#define STACK_H

#include "maze.h"

#define BAD {-1, -1}  // coordinate off maze

/* data to store into stack */
typedef coord StackData;  

/* stack data structures */
typedef struct NodeTag Node;
typedef struct StackTag StackType;
typedef struct StackTag* Stack;

/* linked list implementation of stacks */
struct NodeTag {
  StackData data;
  Node *next;
};

struct StackTag {
  Node * top;
};

/* function prototypes on stacks */
Stack initStack();
int emptyStack(Stack S);
void push(Stack S, StackData d);
StackData pop(Stack S);
void freeStack(Stack S);

#endif
