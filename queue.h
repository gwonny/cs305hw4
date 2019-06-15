/* Author: Tammy VanDeGrift
 * CS 305 HW 4
 * queue.h
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "maze.h"

#define MAX_Q 5000  // 1 more than what can be stored in the queue
                    // in this application, the mazes are on the small
                    // side

/* data to store into queue */
typedef coord QueueData;  // putting coordinates into queue

/* queue data structure */
typedef struct QueueTag QueueType;
typedef struct QueueTag* Queue; // pointer to queue struct
                                // so when it is passed, the values
                                // can be updated in functions

struct QueueTag {
  int head;
  int tail;
  QueueData data[MAX_Q]; // space for items in queue
};

/* function prototypes on queues */
Queue initQueue();
int emptyQueue(Queue Q);
void enqueue(Queue Q, QueueData d);
QueueData dequeue(Queue Q);
void freeQueue();
int full(Queue Q);

#endif
  
