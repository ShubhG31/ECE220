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
    fscanf(file_p, "%d %d", &(value->height),&(value->width));
    //char newline;
    //value->startColumn=(int*)malloc(sizeof(int));
    //value->startRow=(int*)malloc(sizeof(int));
    value->startColumn=0;
    value->startRow=0;
    
  /*  char maze[(value->height)][(value->width)];
    int r,c;
    for(r=0; r<(value->height);r++){
        for(c=0; c<=(value->width);c++){
            
               fscanf(file_p,"%c",&(maze[r][c]));
               //maze[r][c]=fgetc(file_p);
        }
       // fgetc(file_p);
       fscanf(file_p,"%c",&newline);
    }

    fclose(file_p);*/
    /*int row, col;
    for(row=0; row<(value->height);row++){
        for(col=0; col<=(value->width);col++){
            //if(row>=0 && row<(value->height) && col>=0 && col<(value->width) ){ // redudantw
              if(maze[row][col]==START){ 
                    value->startColumn=col;
                    value->startRow=row;
               }
                if(maze[row][col]==END){
                    value->endColumn=col;
                    value->endRow=row;
                } 
           // }
        }
    }*/
  //  printf("%d",value->endColumn);
  //  printf("%d",value->endRow);
    //sets the cells double pointer to the column size of the maze height
    value->cells=(char**)malloc((value->height)*sizeof(char*));
    
    //sets the value of each row to the pointer of the width of the maze 
    int k;
    for(k=0; k<(value->height);k++){
       // if(k>=0 && k<(value->height)){
           // *((value->cells)+k)=(char*)malloc((value->width)*sizeof(char));
           value->cells[k]=(char*)malloc((value->width)*sizeof(char));
       // }
    }
    int z,x,c;
    for(z=0; z<(value->height);z++){
        for(x=0; x<(value->width);x++){
            if(z>=0 && z<(maze->height) && x>=0 && x<(maze->width) ){
            c = fgetc(file_p);
            if (c != '\n'){
                value-> cells[z][x] = c;
            }
            else{
                x--;
            }
            if (value -> cells[z][x] == START){
                value -> startRow = z;
                value -> startColumn = x;
             }
            else if (value -> cells[z][x] == END){
                value -> endRow = z;
                value -> endColumn = x;
            }
            }
           
           
            //if(z>=0 && z<(value->height) && x>=0 && x<(value->width) ){
               // *(*((value->cells)+z)+x)=maze[z][x];
            //(value->cells)[z][x]=maze[z][x];
            //}
        }
    } 
    fclose(file_p);
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
    int z,x;
     for(z=0; z<(maze->height);z++){
        for(x=0; x<(maze->width);x++){
            //if(z>=0 && z<(maze->height) && x>=0 && x<(maze->width) ){
               free((*((maze->cells)+z)+x));
                //free(maze->cells[z][x]);
           // }
        }
    }
    int k;
    for(k=0; k<(maze->width);k++){
        // if(k>=0 && k<(maze->width)){
            free(((maze->cells)+k));
        // }
    }
   // free(maze->cells);
    free(maze);
    maze=NULL;

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
    int z,x;
    for(z=0; z<(maze->height);z++){
        for(x=0; x<(maze->width);x++){
            if(z>=0 && z<(maze->height) && x>=0 && x<(maze->width) ){
                //printf("%c",*(*((maze->cells)+z)+x));
                printf("%c",maze->cells[z][x]);
            }
        }
        printf("\n");
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
    if(col< 0 || col>=maze->height || row<0 ||row>=maze->width){
        return 0;
    }
    if(maze->cells[row][col]== " "){
        return 0;
    }
      if(maze->cells[row][col]==END){
        return 1;
    }
    maze->cells[row][col]="*";
    if(solveMazeDFS(maze, col-1, row)==1){
        return 1;
    }
     if(solveMazeDFS(maze, col+1, row)==1){
        return 1;
    }
    if(solveMazeDFS(maze, col, row-1)==1){
        return 1;
    }
     if(solveMazeDFS(maze, col, row+1)==1){
        return 1;
    }
    maze->cells[row][col]="~";
    return 0;
}
