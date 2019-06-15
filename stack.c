/* Tammy VanDeGrift
 * CS 305 HW 4
 * stack.c
 * implements functions on stacks: initStack, empty, push, pop, and freeStack
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* initializes a new stack */
Stack initStack() {
  Stack s = (Stack) malloc(sizeof(StackType));
  s->top = NULL;
  return s;
}

/* empty returns 0 if S is empty and non-zero if S is not empty */
int emptyStack(Stack S) {
  return (S->top == NULL);
}

/* pushes d to S */
void push(Stack S, StackData d) {
  Node * n = (Node *)malloc(sizeof(Node));
  n->data = d;
  n->next = S->top;
  S->top = n;
}

/* pops top item from S */
StackData pop(Stack S) {
  if(emptyStack(S)) {
    printf("Stack is empty. Attempting to pop an empty stack. Exiting program.\n");
    exit(1);  // exiting program
  }
  // there is data to pop
  StackData toReturn = S->top->data;
  Node * tmp = S->top;  // in order to free this later
  S->top = S->top->next;  // move pointer to next item in stack
  free(tmp);
  return toReturn;
}

/* frees stack memory */
void freeStack(Stack S) {
  while(!emptyStack(S)) {
    pop(S);
  }
  free(S);
}
