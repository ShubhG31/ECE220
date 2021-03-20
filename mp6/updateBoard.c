
/*Introduction: This file contain 3 functions that are used by the main function to create the 
game of life. CountLiveNeighbor checks the nearby cells of a certain locations to see if they are alive (1) 
and stores the number of alive cells in an integer and returns the number to main.c. The function 
updateBoard uses the number of alive neighbors and updates the cell to the next value. The function aliveStable
checks if the board has changed or stayed the same from previous board
Partners: clegras2, htd2*/
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

int neighbors = 0; //initialized the counter for live cells to 0

    for(int i=row-1;i >= row-1 && i <= row+1; i++){              //row counter for loop; goes through all possible row values  
        if(i >= 0 && i <= boardRowSize -1){                     //i is checked to see if it is in the row domain of the array
            for(int j =col-1; j >= col-1 && j <= col+1;j++){    //column counter for loop; goes through all possible column values
                if(j>=0 && j <= boardColSize-1){                //j is checked to if it is in the column domain of the array
                    if((board + boardColSize*row + col) != (board + boardColSize*i + j)){   //checks if the the address of specified cell by the arguement is the same as the cell specified by the for loops
                        if(*(board+boardColSize*i+j)==1){       //if the cell is alive then increment counter 
                            neighbors++;                        // increment alive cell counter
                        }
                    }
                }
            }
        }
    }
return neighbors;                                               //return alive cell counter to main function
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int liveN=0;                                                //Initialize neighbor alive cell value to 0
    int newboard[boardColSize*boardRowSize];                    //newboard array is initialized with size of boardColSize*boardRowSize
   
    for(int i =0; i<= boardRowSize*boardColSize-1; i++){        //for loop to go through all values of 1D array
            newboard[i] =0;                                     //newboard array of all indexes is intialized to 0
            newboard[i]= board[i];                              //newboard is set to board array for every index value incremented by for loop
    } 
    for(int row = 0; row<=boardRowSize-1; row++ ){              //for loop is set to increment for all row index values
        for(int col=0; col <= boardColSize-1; col++){           //for loop is set to increment for all column index values
            liveN = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);    //liveN is set to value of all neighbors that are alive
              if(board[boardColSize*row +col]==0 && liveN==3){  //if cell is dead and has 3 live neighbors then set newboard array cell to 1
                  newboard[boardColSize*row + col] = 1;         //set newboard array cell to 1
               }
               if(liveN<2 || liveN>3){                          //if live neighbors is less than 2 or greater than 3 then set newboard array cell to 0
                    newboard[boardColSize*row + col] = 0;       // set newboard array cell to 0
                }
        }
    }
     for(int k =0; k<= boardRowSize*boardColSize-1; k++){       // for loop to go through all values of 1D array
            board[k] = newboard[k];                             // board array is set to values stored in newboard array
        }
    
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int alive = 0;                                                  // alive neighbors variable initialized and set to 0
    for(int row=0; row<=boardRowSize-1; row++){                     // for loop that goes through each row index value 
        for(int col=0; col<=boardColSize-1; col++){                 // for loop that goes through each column index value
            alive = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);    //alive is set to alive cell neighbors 
            if (board[boardColSize*row +col] == 1){                 // if board of specified cell by for loop is alive then execute next statement
                if(alive!=3 && alive!=2){                           
                    return 0;
                }
             continue;
            }
            else {
                if(alive==3){
                    return 0;
                }
                continue;
            }
             
        }
    }
    return 1;
}


				
				
			

