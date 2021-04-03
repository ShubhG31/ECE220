#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

    // assign initial value to rows
    mygame->rows = rows;
    // assign initial value to col
    mygame->cols = cols;

    // assign initial value to all cells
    // all cells start empty, so they must contain -1
    // iterate over the whole cell board and set individual cells to -1
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            mygame->cells[i*cols+j] = -1;
        }
    }

    // assign initial value to score
    mygame->score = 0;

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct

    // reinitialize rows and cols
    (*_cur_game_ptr)->rows = new_rows;
    (*_cur_game_ptr)->cols = new_cols;

    // reassign initial value to all cells
    // all cells start empty, so they must contain -1
    // iterate over the whole cell board and set individual cells to -1
    for (int i=0; i<new_rows; i++) {
        for (int j=0; j<new_cols; j++) {
            (*_cur_game_ptr)->cells[i*new_cols+j] = -1;
        }
    }

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    
    // check if row or col is out of bounds, and if so, return 0
    if (row<0 || row>=(cur_game->rows) || col<0 || col>=(cur_game->cols)) {
        return NULL;
    }

    // return a pointer corresponding to the cell at row, col
    // find beginning pointer to cells
    cell* specifiedCellPtr = cur_game->cells;
    // add correct offset
    specifiedCellPtr += row*(cur_game->cols) + col;
    // return the pointer
    return specifiedCellPtr;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE

    // to avoid having to use bool, we will define the convention that
    // haveMerged contains the index of the last cell that was created 
    // by merging. For example, haveMerged=5 means that the cell at index
    // 5 was formed by merging, so we cannot merge with it. haveMerged=-1
    // means that no cells have been merged yet for that specific column.
    int haveMerged;

    // we will also define the convention that haveChanged=0 means that
    // the cells did not change, while haveChanged=1 means that sliding
    // up changed some cells
    int haveChanged=0;

    // first iterate over all the cols, in left to right order
    for (int currentCol=0; currentCol<(cur_game->cols); currentCol++) {
        // set haveMerged for this col
        haveMerged = -1;
        // now iterate over all the elements in a single column,
        // starting from top to bottom element
        for (int currentRow=0; currentRow<(cur_game->rows); currentRow++) {
            // first check if cell contains element or is empty
            // if it contains an element, then we decide how to shift/merge it
            // if it is empty, continue to next iteration
            if (cur_game->cells[currentRow*(cur_game->cols)+currentCol] != -1) {
                // current cell is not empty
                // search for possible empty cell above to move the cell
                // nextFreeRow is going to be set to the closest row above that is free
                // if none of the rows above are free, nextFreeRow is -1
                int nextFreeRow = currentRow-1;
                while(nextFreeRow>=0) {
                    if ( *(get_cell(cur_game, nextFreeRow, currentCol)) != -1 ) {
                        // cell is not empty. This is the first non-empty cell,
                        // so nextFreeRow index is one plus this row, unless
                        // nextFreeRow is the currentRow, in which case we set it to -1
                        // just a TOUCH of this SPECIAL DRESSING to makes it work - Gordon Ramsay
                        nextFreeRow = (nextFreeRow+1==currentRow) ? -1 : nextFreeRow+1;
                        break;
                    }
                    if (nextFreeRow-1<0) {
                        // Check if this is the last free cell
                        break;
                    }
                    nextFreeRow--;
                }
                
                // If nextFreeRow is -1, then there is nowhere to move the cell up, 
                // since all cells above is filled
                // If nextFreeRow is not -1, then we can move the current cell to 
                // nextFreeRow
                if (nextFreeRow != -1) {
                    // move cell in currentRow to nextFreeRow
                    cur_game->cells[nextFreeRow*(cur_game->cols)+currentCol] = *(get_cell(cur_game, currentRow, currentCol));
                    // set cell in currentRow to -1, as we moved it
                    cur_game->cells[currentRow*(cur_game->cols)+currentCol] = -1;
                    // set haveChanged since we moved a cell
                    haveChanged = 1;
                }

                // Calculate the potentialMergeRow based from nextFreeRow and possible merging. 
                // potentialMergeRow is the index of the row to check for meging.
                
                // Set potentialMergeRow to the potential merging row index. If nextFreeRow 
                // is not -1, then set potentialMergeRow to nextFreeRow-1. If it is -1, 
                // then set potentialMergeRow to currentRow-1
                // special SAUCE that makes this work !!
                int potentialMergeRow = (nextFreeRow==-1) ? currentRow-1 : nextFreeRow-1; 

                // Check if potentialMergeRow is a valid row, and if it 
                // was not formed by merging
                if (potentialMergeRow>=0 && (potentialMergeRow>haveMerged)) {
                    // Check if the cell values match
                    if ( *(get_cell(cur_game, potentialMergeRow, currentCol)) == *(get_cell(cur_game, potentialMergeRow+1, currentCol)) ) {
                        // Merging is possible, so add cell in potentialMergeRow+1 to the cell in potentialMergeRow (above it)
                        // This is equal to doubling its value
                        cur_game->cells[potentialMergeRow*(cur_game->cols)+currentCol] *= 2;
                        // set cell in potentialMergeRow+1 to -1, as we moved it
                        cur_game->cells[(potentialMergeRow+1)*(cur_game->cols)+currentCol] = -1;
                        // Set haveMerged so we don't merge again with this row
                        haveMerged = potentialMergeRow;
                        // Set haveChanged since we merged cells
                        haveChanged = 1;
                    }
                }

            }
        }
    }

    if (haveChanged) {
        (cur_game->score)=+1;
        return 1;
    } else {
        return 0;
    }
};

/* For the move_s, move_a, and move_d functions, the code is very similar 
to move_w, so the comments are not repeated, unless necessary. */

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE

    // debugging
    print_game(cur_game);

    int haveMerged;
    int haveChanged=0;

    // first iterate over all the cols, in left to right order
    for (int currentCol=0; currentCol<(cur_game->cols); currentCol++) {
        // set haveMerged for this col
        // in this case, it is intialized to one below the maximum row
        haveMerged = (cur_game->rows);
        // now iterate over all the elements in a single column,
        // starting from bottom to top element
        for (int currentRow=(cur_game->rows)-1; currentRow>=0; currentRow--) {
            // first check if cell contains element or is empty
            // if it contains an element, then we decide how to shift/merge it
            // if it is empty, continue to next iteration
            if (cur_game->cells[currentRow*(cur_game->cols)+currentCol] != -1) {
                // current cell is not empty
                // search for possible empty cell below to move the cell
                // nextFreeRow is going to be set to the closest row below that is free
                // if none of the rows below are free, nextFreeRow is -1
                int nextFreeRow = currentRow+1;
                while( nextFreeRow<(cur_game->rows) ) {
                    if ( *(get_cell(cur_game, nextFreeRow, currentCol)) != -1 ) {
                        // cell is not empty. This is the first non-empty cell,
                        // so nextFreeRow index is one minus this row, unless
                        // nextFreeRow is the currentRow, in which case we set it to -1
                        // just a TOUCH of this SPECIAL DRESSING to makes it work - Gordon Ramsay
                        nextFreeRow = (nextFreeRow-1==currentRow) ? (cur_game->rows) : nextFreeRow-1;
                        break;
                    }
                    if (nextFreeRow+1>=(cur_game->rows) ) {
                        // Check if this is the last free cell
                        break;
                    }
                    nextFreeRow++;
                }
                
                // If nextFreeRow is cur_game->rows, then there is nowhere to move the cell down, 
                // since all cells below is filled
                // If nextFreeRow is not cur_game->rows, then we can move the current cell to 
                // nextFreeRow
                if (nextFreeRow != cur_game->rows) {
                    // move cell in currentRow to nextFreeRow
                    cur_game->cells[nextFreeRow*(cur_game->cols)+currentCol] = *(get_cell(cur_game, currentRow, currentCol));
                    // set cell in currentRow to -1, as we moved it
                    cur_game->cells[currentRow*(cur_game->cols)+currentCol] = -1;
                    // set haveChanged since we moved a cell
                    haveChanged = 1;
                }

                // Calculate the potentialMergeRow based from nextFreeRow and possible merging. 
                // potentialMergeRow is the index of the row to check for meging.
                
                // Set potentialMergeRow to the potential merging row index. If nextFreeRow 
                // is not cur_game->rows, then set potentialMergeRow to nextFreeRow+1. If it is cur_game->rows,, 
                // then set potentialMergeRow to currentRow+1
                // special SAUCE that makes this work !!
                int potentialMergeRow = (nextFreeRow==(cur_game->rows)) ? currentRow+1 : nextFreeRow+1; 

                // Check if potentialMergeRow is a valid row, and if it 
                // was not formed by merging
                if (potentialMergeRow<(cur_game->rows) && (potentialMergeRow<haveMerged)) {
                    // Check if the cell values match
                    if ( *(get_cell(cur_game, potentialMergeRow, currentCol)) == *(get_cell(cur_game, potentialMergeRow-1, currentCol)) ) {
                        // Merging is possible, so add cell in potentialMergeRow-1 to the cell in potentialMergeRow (below it)
                        // This is equal to doubling its value
                        cur_game->cells[potentialMergeRow*(cur_game->cols)+currentCol] *= 2;
                        // set cell in potentialMergeRow-1 to -1, as we moved it
                        cur_game->cells[(potentialMergeRow-1)*(cur_game->cols)+currentCol] = -1;
                        // Set haveMerged so we don't merge again with this row
                        haveMerged = potentialMergeRow;
                        // Set haveChanged since we merged cells
                        haveChanged = 1;
                    }
                }

            }
        }
    }

    if (haveChanged) {
        (cur_game->score)=+1;
        return 1;
    } else {
        return 0;
    }
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    
    // debugging
    print_game(cur_game);

    int haveMerged;
    int haveChanged=0;

    // first iterate over all the rows, in top to bottom order
    for (int currentRow=0; currentRow<(cur_game->rows); currentRow++) {
        // set haveMerged for this row
        // in this case, it is intialized to -1
        haveMerged = -1;
        // now iterate over all the elements in a single row,
        // starting from left to right element
        for (int currentCol=0; currentCol<(cur_game->cols); currentCol++) {
            // first check if cell contains element or is empty
            // if it contains an element, then we decide how to shift/merge it
            // if it is empty, continue to next iteration
            if (cur_game->cells[currentRow*(cur_game->cols)+currentCol] != -1) {
                // current cell is not empty
                // search for possible empty cell to the left to move the cell
                // nextFreeCol is going to be set to the closest col on the left is free
                // if none of the cols on the left are free, nextFreeCol is -1
                int nextFreeCol = currentCol-1;
                while( nextFreeCol>=0 ) {
                    if ( *(get_cell(cur_game, currentRow, nextFreeCol)) != -1 ) {
                        // cell is not empty. This is the first non-empty cell,
                        // so nextFreeCol index is one plus this col, unless
                        // nextFreeCol is the currentCol, in which case we set it to -1
                        // just a TOUCH of this SPECIAL DRESSING to makes it work - Gordon Ramsay
                        nextFreeCol = (nextFreeCol+1==currentCol) ? -1 : nextFreeCol+1;
                        break;
                    }
                    if (nextFreeCol-1<0) {
                        // Check if this is the last free cell
                        break;
                    }
                    nextFreeCol--;
                }
                
                // If nextFreeCol is -1, then there is nowhere to move the cell left, 
                // since all cells to the left is filled
                // If nextFreeRow is not -1, then we can move the current cell to 
                // nextFreeCol
                if (nextFreeCol != -1) {
                    // move cell in currentCol to nextFreeCol
                    cur_game->cells[currentRow*(cur_game->cols)+nextFreeCol] = *(get_cell(cur_game, currentRow, currentCol));
                    // set cell in currentCol to -1, as we moved it
                    cur_game->cells[currentRow*(cur_game->cols)+currentCol] = -1;
                    // set haveChanged since we moved a cell
                    haveChanged = 1;
                }

                // Calculate the potentialMergeCol based from nextFreeCol and possible merging. 
                // potentialMergeCol is the index of the col to check for meging.
                
                // Set potentialMergeCol to the potential merging col index. If nextFreeCol 
                // is not -1, then set potentialMergeCol to nextFreeCol-1. If it is -1, 
                // then set potentialMergeCol to currentCol-1
                // special SAUCE that makes this work !!
                int potentialMergeCol = (nextFreeCol==-1) ? currentCol-1 : nextFreeCol-1; 

                // Check if potentialMergeCol is a valid col, and if it 
                // was not formed by merging
                if (potentialMergeCol>=0 && (potentialMergeCol>haveMerged)) {
                    // Check if the cell values match
                    if ( *(get_cell(cur_game, currentRow, potentialMergeCol)) == *(get_cell(cur_game, currentRow, potentialMergeCol+1)) ) {
                        // Merging is possible, so add cell in potentialMergeCol+1 to the cell in potentialMergeCol (left of it)
                        // This is equal to doubling its value
                        cur_game->cells[currentRow*(cur_game->cols)+potentialMergeCol] *= 2;
                        // set cell in potentialMergeCol+1 to -1, as we moved it
                        cur_game->cells[currentRow*(cur_game->cols)+potentialMergeCol+1] = -1;
                        // Set haveMerged so we don't merge again with this row
                        haveMerged = potentialMergeCol;
                        // Set haveChanged since we merged cells
                        haveChanged = 1;
                    }
                }

            }
        }
    }

    if (haveChanged) {
        (cur_game->score)=+1;
        return 1;
    } else {
        return 0;
    }
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

    // debugging
    print_game(cur_game);

    int haveMerged;
    int haveChanged=0;

    // first iterate over all the rows, in top to bottom order
    for (int currentRow=0; currentRow<(cur_game->rows); currentRow++) {
        // set haveMerged for this row
        // in this case, it is intialized to cur_game->cols
        haveMerged = cur_game->cols;
        // now iterate over all the elements in a single row,
        // starting from right to left element
        for (int currentCol=(cur_game->cols)-1; currentCol>=0; currentCol--) {
            // first check if cell contains element or is empty
            // if it contains an element, then we decide how to shift/merge it
            // if it is empty, continue to next iteration
            if (cur_game->cells[currentRow*(cur_game->cols)+currentCol] != -1) {
                // current cell is not empty
                // search for possible empty cell to the right to move the cell
                // nextFreeCol is going to be set to the closest col on the right that is free
                // if none of the cols on the right are free, nextFreeCol is cur_game->cols
                int nextFreeCol = currentCol+1;
                while( nextFreeCol<cur_game->cols ) {
                    if ( *(get_cell(cur_game, currentRow, nextFreeCol)) != -1 ) {
                        // cell is not empty. This is the first non-empty cell,
                        // so nextFreeCol index is one plus this col, unless
                        // nextFreeCol is the currentCol, in which case we set it to cur_game->cols
                        // just a TOUCH of this SPECIAL DRESSING to makes it work - Gordon Ramsay
                        nextFreeCol = (nextFreeCol-1==currentCol) ? (cur_game->cols) : nextFreeCol-1;
                        break;
                    }
                    if ( nextFreeCol+1>=(cur_game->cols) ) {
                        // Check if this is the last free cell
                        break;
                    }
                    nextFreeCol++;
                }
                
                // If nextFreeCol is cur_game->cols, then there is nowhere to move the cell right, 
                // since all cells to the right is filled
                // If nextFreeRow is not -1, then we can move the current cell to 
                // nextFreeCol
                if (nextFreeCol != cur_game->cols) {
                    // move cell in currentCol to nextFreeCol
                    cur_game->cells[currentRow*(cur_game->cols)+nextFreeCol] = *(get_cell(cur_game, currentRow, currentCol));
                    // set cell in currentCol to -1, as we moved it
                    cur_game->cells[currentRow*(cur_game->cols)+currentCol] = -1;
                    // set haveChanged since we moved a cell
                    haveChanged = 1;
                }

                // Calculate the potentialMergeCol based from nextFreeCol and possible merging. 
                // potentialMergeCol is the index of the col to check for meging.
                
                // Set potentialMergeCol to the potential merging col index. If nextFreeCol 
                // is not cur_game->cols, then set potentialMergeCol to nextFreeCol+1. If it is cur_game->cols, 
                // then set potentialMergeCol to currentCol+1
                // special SAUCE that makes this work !!
                int potentialMergeCol = (nextFreeCol==(cur_game->cols)) ? currentCol+1 : nextFreeCol+1; 

                // Check if potentialMergeCol is a valid col, and if it 
                // was not formed by merging
                if (potentialMergeCol<(cur_game->cols) && (potentialMergeCol<haveMerged)) {
                    // Check if the cell values match
                    if ( *(get_cell(cur_game, currentRow, potentialMergeCol)) == *(get_cell(cur_game, currentRow, potentialMergeCol-1)) ) {
                        // Merging is possible, so add cell in potentialMergeCol-1 to the cell in potentialMergeCol (right of it)
                        // This is equal to doubling its value
                        cur_game->cells[currentRow*(cur_game->cols)+potentialMergeCol] *= 2;
                        // set cell in potentialMergeCol-1 to -1, as we moved it
                        cur_game->cells[currentRow*(cur_game->cols)+potentialMergeCol-1] = -1;
                        // Set haveMerged so we don't merge again with this row
                        haveMerged = potentialMergeCol;
                        // Set haveChanged since we merged cells
                        haveChanged = 1;
                    }
                }

            }
        }
    }

    if (haveChanged) {
        (cur_game->score)=+1;
        return 1;
    } else {
        return 0;
    }
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE

    // Iterate across all cells in the whole board
    // Check for an empty cell. If a cell is empty, a legal move is possible, so return 1.
    // Check for all adjacent cells directly above, below, left, and right of the cell. If 
    // the cells have matching values, then a legal move is possible, so return 1.
    // If none of the scenarios above is found, then no legal move is possible and return 0.

    for (int i=0; i<(cur_game->rows); i++) {
        for (int j=0; j<(cur_game->cols); j++) {
            int cellValue = cur_game->cells[i*(cur_game->cols)+j];
            // Check if cell is empty
            if (cellValue == -1) {
                // legal move is possible, so return 1
                return 1;
            }
            // Check for neighboring cells
            // With the simplest way, and there being only 4 directions,
            // manually check each
            // Because of short circuit (lazy) evaluation, we can place the bounds
            // checker before the logical &&, and if it fails, we are not
            // going to evaluate the second term anymore
            if (i-1>=0 && cur_game->cells[(i-1)*(cur_game->cols)+j] == cellValue) {return 1;}
            if (i+1<(cur_game->rows) && cur_game->cells[(i+1)*(cur_game->cols)+j] == cellValue) {return 1;} 
            if (j-1>=0 && cur_game->cells[i*(cur_game->cols)+j-1] == cellValue) {return 1;}
            if (j+1<(cur_game->cols) && cur_game->cells[i*(cur_game->cols)+j+1] == cellValue) {return 1;}
        }
    }
    // No legal moves found so return 0
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}