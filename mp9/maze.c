#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* Intro paragraph:
** I implemented the createMaze function by opening the file,
** parsing the right maze size, then dynamically allocating
** the correct maze size into cells. To do this, I first allocated
** for the outer dimension, then iterated over that (rows/height)
** to allocate memory for the inner dimension. If the cell is to
** contain the start symbol, ie it is the start cell, I leave the
** cell blank since I use the convention that 'S' on a cell means
** the start cell has been visited.
**
** I implemented the destroyMaze function by freeing first the 
** inner dimensions of cells (width) for every outer dimension (height).
** Then, I can free the outer dimensions. Finally, I can free the 
** dynamically allocated maze_t struct itself.
**
** To implement the printMaze function, I interated over all cells, 
** starting with the innermost dimension and printing the contents.
** After every row (height), I print the newline character.
**
** For the solveMazeDFS function, I used the convention that 'S' on a cell
** means the start cell, and also means that it has been visited. I first 
** check for all the base cases in this order: index is out of bounds, 
** end of maze has been reached, or cell is filled. After handling the 
** base cases, I handle the recursive cases. To prepare for that, I first
** set the cell as part of the solutuon by setting it to '*', unless it 
** is the start cell in which case I set it to 'S'. Then, in order, recursively
** call solveMazeDFS on the cell to the left, right, up, and down. If either
** of these cases returns 1, it means the maze has been solved, so return 1.
** If none of these cases returns 1, backtrack by marking the cell as visited
** with '~', unless it is the start cell in which we just leave 'S' in the cell.
** Then, return 0 since a solution was not found for all posibilities of 
** movements from this particular cell.
**
** Partners: htd2, clegras2
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName) {
    FILE* mazeSrc = fopen(fileName, "r");
    
    if (mazeSrc == NULL) return NULL;

    maze_t* maze = (maze_t*)malloc(sizeof(maze_t));

    int width, height;
    fscanf(mazeSrc, "%d %d", &width, &height);
    maze->width = width;
    maze->height = height;

    // Allocate space for cells
    int i, j;
    maze->cells = (char**)malloc(height*sizeof(char*));
    for (i=0; i<height; i++) {
        maze->cells[i] = (char*)malloc(width*sizeof(char));
    }

    // Initialize cell values
    char currentChar;
    for (i=0; i<height; i++) {
        // get rid of newline character
        fgetc(mazeSrc);
        for (j=0; j<width; j++) {
            currentChar = fgetc(mazeSrc);
            maze->cells[i][j] = currentChar;
            // Set startColumn and startRow if S char is found
            if (currentChar == 'S') {
                maze->startColumn = j;
                maze->startRow = i;
            }
            // Set endColumn and endRow if E char is found
            if (currentChar == 'E') {
                maze->endColumn = j;
                maze->endRow = i;
            }
        }
    }

    // CLose file
    fclose(mazeSrc);

    // Return pointer to dynamically created maze_t
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t* maze) {
    // First free all the inner dimensions of cells
    int i;
    for (i=0; i<maze->height; i++) {
        free(maze->cells[i]);
    }
    // Free outer dimension
    free(maze->cells);

    // Finally free out maze
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
void printMaze(maze_t * maze) {
    // Iterate over all cells and print
    // Also print newline after each row
    int i, j;
    for (i=0; i<maze->height; i++) {
        for (j=0; j<maze->width; j++) {
            printf("%c",maze->cells[i][j]);
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
int solveMazeDFS(maze_t * maze, int col, int row) {
    // Check for base cases

    // Out of bounds
    if (row<0 || row>=maze->height || col<0|| col>=maze->width) return 0;

    // Reached end of maze, so return 1
    if (maze->cells[row][col] == 'E') return 1;    

    // Cell is filled or we are at start of maze, with 'S' symbol
    // 'S' means we haven't visited it yet 
    if (maze->cells[row][col] != 'S' && maze->cells[row][col] != ' ') return 0;

    // All base cases have been checked, so handle recursive cases

    // Set cell as part of solution
    maze->cells[row][col] = '*';

    // In order, go left, right, up, and down
    // If any of these solveMazeDFS recursive calls returns 1, we have found sol 
    // So, remark start cell as 'S' and return 1
    if (solveMazeDFS(maze, col-1, row) || solveMazeDFS(maze, col+1, row) || solveMazeDFS(maze, col, row+1) || solveMazeDFS(maze, col, row-1)) {
        maze->cells[maze->startRow][maze->startColumn] = 'S';
        return 1;
    }

    // No solution found for all possibilities of moving left, right, up, down
    // from this particular cell, so backtrack by umarking cell, mark it as visited,
    // and return 0

    // Mark as visited
    maze->cells[row][col] = '~';
    
    return 0;
}