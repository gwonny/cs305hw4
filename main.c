/* Author: Tammy VanDeGrift
   CS 305 Spring 2018
   Homework 4: mazes
   This is the main function: it opens the file specified at the command line,
   creates a maze object, and determines if the maze is solvable.
*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

#define NUM_PARAMS 2

/* prototype */
void usage(char * executable);

/* main
   executable_name input_filename.txt
   opens input_filename.txt for reading
   creates maze object
   runs the maze solver
   frees maze
*/
// function completed for the CS 305 students: DO NOT MODIFY (Unless you find a bug)   
int main(int argc, char * argv[]) {
  if(argc != NUM_PARAMS) {
    usage(argv[0]);
    return EXIT_FAILURE;
  }    
  
  // open file for reading
  FILE *fp = NULL;
  fp = fopen(argv[1], "r");
  if(fp == NULL) {
    fprintf(stderr, "Error opening input file %s. Exiting.\n", argv[1]);
    return EXIT_FAILURE;
  }
  
  // create maze objects
  // need 2 since we are running BFS on one (which modifies the
  // maze with the path marker character)
  // need clean copy of maze for DFS
  maze * the_maze = create_maze(fp);
  rewind(fp); // resets file pointer to beginning of file
  maze * the_maze2 = create_maze(fp);
  
  // done with file at this point
  fclose(fp);
  fp = NULL;  

  // check maze to see if it was created successfully
  if(the_maze == NULL || the_maze2 == NULL) {
    fprintf(stderr, "Error creating maze data structure\n");
    return EXIT_FAILURE;
  }
  
  // run breadth-first-search on maze
  printf("\nSolving using breadth-first search.\n");
  int a = solve_bfs(the_maze);

  // run depth-first-search on maze
  printf("\nSolving using depth-first search:\n");
  int b = solve_dfs(the_maze2);

  printf("\ncan solve BFS: %d, can solve DFS: %d\n\n", a, b);

  // free memory and exit
  free_maze(the_maze);
  free_maze(the_maze2);
  return EXIT_SUCCESS;
}

/* usage
   prints error message to user
*/
void usage(char * executable) {
  printf("Usage: \n%s maze_file.txt\n", executable);
}
