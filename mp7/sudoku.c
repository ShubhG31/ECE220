#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/* Intro paragraph:
** I implemented the is_val_in_row function by iterating over all columns in the given row.
** I implemented the is_val_in_col function by iterating over all rows in the given column.
** I implemented the is_val_in_3x3_zone function by first calculating the starting index of the 
** local 3x3 grid the current index to check is in, and then iterating over all elements in the 3x3 grid.
** To implement the solve_sudoku function, I followed the pseudocode as written on the wiki page:
** Check if the board is filled, and if so, return 1 since we are done. If not, find the next unfilled cell 
** and attempt to fill that by iterating over all possibile numbers to fill. Then, for each number filled, 
** check if it is possibile to solve the board with that value. If so, return true since we are done. If not, 
** then backtrack by filling that cell with 0 and try another number (if there is one). If all the possible
** numbers have been exhausted and none of them yield a solution, then return 0 at the end to indicate
** to the calling solve_sudoku function that none of the possibilities work as a solution.
**
** Partners: clegras2, htd2
 */

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  assert(i>=0 && i<9);

  // BEG TODO
  
  // iterate over all column elements in one row
  for (int j=0; j<9; j++) {
    if (sudoku[i][j] == val) {
      // val exists in some column of the ith row
      return 1;
    }
  }

  // if we reach here, then none of the elements in the row match
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  
  // iterate over all row elements in one column
  for (int i=0; i<9; i++) {
    if (sudoku[i][j] == val) {
      // val exists in some column of the ith row
      return 1;
    }
  }

  // if we reach here, then none of the elements in the column match

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO

  /* 
  floor(row/3) * 3 <-- starting row
  floor(col/3) * 3 <-- starting col
  */
  // iterate over 

  int beginRow = (i/3) * 3;
  int beginCol = (j/3) * 3;

  for (int row=beginRow; row<beginRow+3; row++) {
    for (int col=beginCol; col<beginCol+3; col++) {
      if (sudoku[row][col] == val) {
        // value matches current element being checked
        return 1;
      }
    }
  }

  // all elements in 3x3 grid do not match val so return 0
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO

  // Check if val is in row, col, or in 3x3 grid
  // If it is, then val is not valid, so return 0

  if (is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)) {
    // Value is not valid as it is already somewhere where it cannot be
    return 0;
  }
  
  // Val is not in row, col, or in 3x3 grid
  // So, val is valid
  return 1;

  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.

  int i, j, singleIndex;
  // Iterate through board and look for an element of 0, which means
  // an unfilled cell. If an element of 0 is found, break out of the loop.
  for (singleIndex=0; singleIndex<(9*9); singleIndex++) {
    i=singleIndex/9;
    j=singleIndex%9;
    if (sudoku[i][j] == 0) {
      break;
    }
  }
  // i, j is now the index of an element 0 (unfilled cell)
  // if there was no element 0, ie the board was complete,
  // then singleIndex must be beyond the sudoku board, ie
  // singleIndex=9*9
  if (singleIndex==(9*9)) {
    return 1;
  }

  // iterate over all possibilities to fill cell
  for (int num=1; num<=9; num++) {
    if (is_val_valid(num, i, j, sudoku)) {
      sudoku[i][j] = num;
      // call solve_sudoku to try filling next empty cell
      // if it returns 1, then board is filled, and we are done
      // so return true as well
      // if it returns 0, none of the possibilities worked,
      // so we need to backtrack and try a different number
      if (solve_sudoku(sudoku)) {
        return 1;
      }
      sudoku[i][j] = 0;
    }
  }

  // we tried all posibilities of filling cell, and none of them worked,
  // so return 0 to let the caller solve_sudoku know no possibility worked
  return 0;

  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9]) {
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}