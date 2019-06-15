/* author: Tammy VanDeGrift
   CS 305 HW 4
   maze.c -- defines create_maze (populates maze data structure)
   and free_maze to free the memory stored for the maze
*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

maze * create_maze(FILE *in) {
  // create maze
  maze * new_maze = (maze *) malloc(sizeof(maze));
  
  // read first line of in
  int start_row;
  int start_col;
  int end_row;
  int end_col;
  int num_rows;
  int num_cols;

  // start line
  char * line = malloc(sizeof(char)*100);   // start buffer out at 100
  size_t num_read;
  
  getline(&line, &num_read, in);
  if(sscanf(line, "%d %d %d %d %d %d", &num_rows, &num_cols, &start_row, &start_col, &end_row, &end_col) != 6) {
    fprintf(stderr, "Maze file format invalid. Top line must include 6 numbers.\n");
    return NULL;
  }
  // if any are negative values, return NULL
  if(start_row < 0 || start_col < 0 || end_row < 0 || end_col < 0 || num_rows < 0 || num_cols < 0) {
    fprintf(stderr, "Maze file format invalid. Maze file numbers in first row must be non-negative.\n");
    return NULL;
  }

  // make sure start_row is in bounds
  if(start_row >= num_rows) {
    fprintf(stderr, "Maze file format invalid. Start row must be < num rows in maze.\n");
    return NULL;
  }

  // make sure end_row is in bounds
  if(end_row >= num_rows) {
    fprintf(stderr, "Maze file format invalid. End row must be < num rows in maze.\n");
    return NULL;
  }

  // make sure start_col is in bounds
  if(start_col >= num_cols) {
    fprintf(stderr, "Maze file format invalid. Start col must be < num cols in maze.\n");
    return NULL;
  }

  // make sure end_col is in bounds
  if(end_col >= num_cols) {
    fprintf(stderr, "Maze file format invalid. Start col must be < num cols in maze.\n");
    return NULL;
  }

  // assign maze members
  new_maze->entry.row = start_row;
  new_maze->entry.col = start_col;
  new_maze->exit.row = end_row;
  new_maze->exit.col = end_col;
  new_maze->width = num_cols;
  new_maze->height = num_rows;

  // allocate memory for maze data
  new_maze->data = (char **) malloc(sizeof(char *)*num_rows);
  int i;
  for(i=0; i<num_rows; i++) {
    new_maze->data[i] = (char *) malloc(sizeof(char)*num_cols);
  }
  
  // get characters from file, one line at a time
  size_t num_vals_read = 0;
  for(i=0; i<num_rows; i++) {
    num_vals_read = getline(&line, &num_read, in);
    if(num_vals_read != num_cols + 1) { //account for newline character
      fprintf(stderr, "Maze file format invalid. Found %d chars on line %d and the width is %d.\n", 
	      (num_vals_read-1), i, new_maze->width);
      return NULL;
    }
    // parse out line
    int j;
    for(j=0; j<num_cols; j++) {
      if(line[j] != ' ' && line[j] != '*') {
	fprintf(stderr, "Maze file format invalid. Maze file data must contain spaces and stars. Read %c.\n", line[j]);
	return NULL;
      }
      new_maze->data[i][j] = line[j];
    }
  }
  // try to read more data
  char c;
  if((c = fgetc(in)) != EOF) {
    fprintf(stderr, "Maze file format invalid. Too many characters past %d rows.\n", num_rows);
    return NULL;
  }

  free(line);
  return new_maze;
}

/* frees memory used by the_maze */
void free_maze(maze * the_maze) {
  // first free the data
  // need to free rows of data, then data
  int i;
  for(i = 0; i < the_maze->height; i++) {
    free(the_maze->data[i]);
  }
  free(the_maze->data);
  free(the_maze);
  return;
}
