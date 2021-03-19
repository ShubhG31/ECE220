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

    for(int i=0; i >= row-1 && i <= row+1; i++){
        if(row >= 0 && row <= boardRowSize -1){
            for(int j =0; j >= col-1 && j <= col+1;j++){
                if(col>=0 && col <= boardColSize+1){
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
    int *newboard = board;
    for(int row = 0; row<=boardRowSize-1; row++ ){
        for(int col=0; col <= boardColSize-1; col++){
            liveN = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);
            if(liveN>=2 &&liveN<=3 && *(board+ boardColSize*row +col)==1){
                *(newboard + boardColSize*row + col) = 1;
            }
           else if(*(board+ boardColSize*row +col)==0 && liveN==3){
                *(newboard + boardColSize*row + col) = 1;
            }
            else{
                *(newboard + boardColSize*row + col) = 0;
            }
        }
    }
    for(int i =0; i<= boardRowSize-1; i++){
        for(int j =0; j<= boardColSize-1; j++){
            *(board + boardColSize*i +j)= *(newboard + boardColSize*i +j);
        }
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
    int old_alive=0;
    int new_alive=0;
    int* changed_board=board;
    for(int row=0; row<=boardRowSize-1; row++){
        for(int col=0; col<=boardColSize-1; col++){
            *(changed_board + boardColSize*row +col) = *(board+ boardColSize*row +col);
            if(*(board + boardColSize*row + col)==1){
                old_alive++;
            }
        }
    }
    updateBoard(changed_board, boardRowSize, boardColSize);
    for(int row=0; row<=boardRowSize-1; row++){
        for(int col=0; col<=boardColSize-1; col++){
            if(*(changed_board + boardColSize*row + col)==1){
                new_alive++;
            }
        }
    }
    if(new_alive==old_alive){
        return 1;
    }
    return 0;
}


				
				
			

