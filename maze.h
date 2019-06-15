/* Author: Tammy VanDeGrift
   CS 305 Homework 4
   Mazes
   Header file maze.h
   defines coord and maze structs and function prototypes on mazes
*/
#ifndef MAZE_H
#define MAZE_H

/* struct definition for coord */
typedef struct coord {
  int row;
  int col;
} coord;

/* struct definition for maze */
typedef struct maze {
  coord entry;
  coord exit;
  int width;
  int height;
  char ** data;
} maze;

/* prototypes */
/* in maze.c */
maze * create_maze(FILE *in);
void free_maze(maze * the_maze);

/* in solve.c */
int solve_bfs(maze * the_maze);
int solve_dfs(maze * the_maze);
void print_maze(maze * the_maze);
coord * make_coord(int r, int c);
void print_coord(coord c);

#endif
