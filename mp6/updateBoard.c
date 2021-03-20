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

int neighbors = 0;

    for(int i=row-1;i >= row-1 && i <= row+1; i++){
        if(i >= 0 && i <= boardRowSize -1){
            for(int j =col-1; j >= col-1 && j <= col+1;j++){
                if(j>=0 && j <= boardColSize-1){
                    if((board + boardColSize*row + col) != (board + boardColSize*i + j)){
                        if(*(board+boardColSize*i+j)==1){
                            neighbors++;
                        }
                    }
                }
            }
        }
    }
return neighbors;
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
    int liveN=0;
    int newboard[boardColSize*boardRowSize];
   
    for(int i =0; i<= boardRowSize*boardColSize-1; i++){
            newboard[i] =0;
            newboard[i]= board[i];
    } 
    for(int row = 0; row<=boardRowSize-1; row++ ){
        for(int col=0; col <= boardColSize-1; col++){
            liveN = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);
              if(board[boardColSize*row +col]==0 && liveN==3){
                  newboard[boardColSize*row + col] = 1;
               }
               if(liveN<2 || liveN>3){
                    newboard[boardColSize*row + col] = 0;
                }
        }
    }
     for(int k =0; k<= boardRowSize*boardColSize-1; k++){
            board[k] = newboard[k];
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
    int alive = 0;
    for(int row=0; row<=boardRowSize-1; row++){
        for(int col=0; col<=boardColSize-1; col++){
            alive = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);
            if (board[boardColSize*row +col] == 1){
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


				
				
			

