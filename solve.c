/* 
 * Johnny Huang
 * CS 305 HW 4
 * solve.c
 */

#include <stdio.h>//here's the grand imports!
#include <stdlib.h>
#include "maze.h"
#include "stack.h"
#include "queue.h"

void print_maze(maze * the_maze)//will be called regardless if exit coord is found or not
{
	(*the_maze).data[(*the_maze).entry.row][(*the_maze).entry.col]='S';//marks entrance with S for "starting point"
	(*the_maze).data[(*the_maze).exit.row][(*the_maze).exit.col]='F';//marks exit with F for "finishing point"
	for(int i=0; i<(*the_maze).height; i++)
	{
		for(int j=0; j<(*the_maze).width; j++)
		{
			printf("%c",(*the_maze).data[i][j]);//double for-loop to print 2d char array
		}
		printf("\n");
	}
}

coord * make_coord(int r, int c)//used to make intermediate coordinates between entry coord and exit
{
	coord* coord_gen = malloc(sizeof(coord));//gives enough memory for it
	(*coord_gen).row = r;//assigns row and columns to the (dereferenced) coord pointer
	(*coord_gen).col = c;
	return coord_gen;
}

void print_coord(coord c)
{
	printf("(%d, %d)",c.row,c.col);//for debugging needs
}

int solve_bfs(maze * the_maze)//breadth-first - first way to solve maze
{
	Queue Q = initQueue();//makes an empty queue
	enqueue(Q, (*the_maze).entry);//queues up the entryway
	while(!(emptyQueue(Q)))//will occur until exit is found or entire maze is searched and no exit
	{
		QueueData to_explore = dequeue(Q);//first, takes out entryway, then, from there, takes every top, right, bottom, and left (in that order) coordinate
		if((to_explore.row == (*the_maze).exit.row) && (to_explore.col == (*the_maze).exit.col))//checks if the dequeued coord is the exit
		{
			print_maze(the_maze);//prints out maze and returns success
			return 1;
		}
		else
		{
			(*the_maze).data[to_explore.row][to_explore.col]='o';//fills searched area to mark searched
			
			if((to_explore.row-1>=0) && (to_explore.row-1<=(*the_maze).height) && ((*the_maze).data[to_explore.row-1][to_explore.col]==' '))//queues up top, right, bottom, and left coords if whitespace area
			{
				enqueue(Q, *(make_coord(to_explore.row-1,to_explore.col)));//make_coord makes the intermediate coordinate and dereferences the pointer made to plug into the queue
			}
			if((to_explore.col+1>=0) && (to_explore.col+1<=(*the_maze).width) && ((*the_maze).data[to_explore.row][to_explore.col+1]==' '))
			{
				enqueue(Q, *(make_coord(to_explore.row,to_explore.col+1)));
			}
			if((to_explore.row+1>=0) && (to_explore.row+1<=(*the_maze).height) && ((*the_maze).data[to_explore.row+1][to_explore.col]==' '))
			{
				enqueue(Q, *(make_coord(to_explore.row+1,to_explore.col)));
			}
			if((to_explore.col-1>=0) && (to_explore.col-1<=(*the_maze).width) && ((*the_maze).data[to_explore.row][to_explore.col-1]==' '))
			{
				enqueue(Q, *(make_coord(to_explore.row,to_explore.col-1)));
			}
			
		}
	}
	print_maze(the_maze);//if exit never found and queue empties up, prints maze anyway
	freeQueue(Q);//frees the queue
	return 0;//result failure :(
}

int solve_dfs(maze * the_maze)//same intention as queue, but done as a stack. LIFO will be applied on what is pushed
{
	Stack S = initStack();
	push(S, (*the_maze).entry);
	while(!(emptyStack(S)))
	{
		StackData to_explore = pop(S);
		if((to_explore.row == (*the_maze).exit.row) && (to_explore.col == (*the_maze).exit.col))
		{
			print_maze(the_maze);
			return 1;
		}
		else
		{
			(*the_maze).data[to_explore.row][to_explore.col]='o';
			
			if((to_explore.row-1>=0) && (to_explore.row-1<=(*the_maze).height) && ((*the_maze).data[to_explore.row-1][to_explore.col]==' '))
			{
				push(S, *(make_coord(to_explore.row-1,to_explore.col)));
			}
			if((to_explore.col+1>=0) && (to_explore.col+1<=(*the_maze).width) && ((*the_maze).data[to_explore.row][to_explore.col+1]==' '))
			{
				push(S, *(make_coord(to_explore.row,to_explore.col+1)));
			}
			if((to_explore.row+1>=0) && (to_explore.row+1<=(*the_maze).height) && ((*the_maze).data[to_explore.row+1][to_explore.col]==' '))
			{
				push(S, *(make_coord(to_explore.row+1,to_explore.col)));
			}
			if((to_explore.col-1>=0) && (to_explore.col-1<=(*the_maze).width) && ((*the_maze).data[to_explore.row][to_explore.col-1]==' '))
			{
				push(S, *(make_coord(to_explore.row,to_explore.col-1)));
			}
		}
	}
	print_maze(the_maze);
	freeStack(S);
	return 0;
}
