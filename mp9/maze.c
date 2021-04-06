#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE *file_p; // File pointer
    maze_t *value=(maze_t*)malloc(sizeof(maze_t));
    file_p= fopen(fileName,"r"); // sets the pointer of the file to the start of the contents of the file 

    fscanf(file_p, "%d%d", value->width,value->height);
   
    //value->startColumn=(int*)malloc(sizeof(int));
    //value->startRow=(int*)malloc(sizeof(int));
    value->startColumn=0;
    value->startRow=0;
    
    char maze[(value->height)-1][(value->width)-1];

    for(int r=0; r<(value->height);r++){
        for(int c=0; c<(value->width);c++){
            if(r>=0 && r<(value->height) && c>=0 && c<(value->width) ){
                fscanf(file_p,"%c",maze[r][c]);
            }
        }
    }

    fclose(file_p);

    for(int row=0; row<(value->height);row++){
        for(int col=0; col<(value->width);col++){
            if(row>=0 && row<(value->height) && col>=0 && col<(value->width) ){
              if(maze[row][col]=="S"){
                value->startColumn=col;
                value->startRow=row;
               }
                if(maze[row][col]=="E"){
                    value->endColumn=col;
                    value->endRow=row;
                } 
            }
        }
    }
    //sets the cells double pointer to the column size of the maze width
    value->cells=(char**)malloc((value->width)*sizeof(char));
    
    for(int k=0; k<(value->width);k++){
        if(k>=0 && k<(value->width)){
            *((value->cells)+k)=(char*)malloc((value->height)*sizeof(char));
        }
    }
    for(int z=0; z<(value->height);z++){
        for(int x=0; x<(value->width);x++){
            if(k>=0 && k<(value->height) && x>=0 && x<(value->width) ){
                *(*(value->cells)+((value->width)*z)+x)=maze[z][x];
            }
        }
    }

    return value;
   // fclose(file_p);

    //return NULL;//Omit
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
     for(int z=0; z<(maze->height);z++){
        for(int x=0; x<(maze->width);x++){
            if(z>=0 && z<(maze->height) && x>=0 && x<(maze->width) ){
                free((*(maze->cells)+((maze->width)*z)+x));
            }
        }
    }
    for(int k=0; k<(maze->width);k++){
         if(k>=0 && k<(maze->width)){
            free(((maze->cells)+k));
         }
    }
    free(maze->cells);
    free(maze);

}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
      // Your code here.
    for(int z=0; z<(maze->height);z++){
        for(int x=0; x<(maze->width);x++){
            if(z>=0 && z<(maze->height) && x>=0 && x<(maze->width) ){
                printf("%c",*(*(maze->cells)+((maze->width)*z)+x));
            }
        }
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    return 0;
}
