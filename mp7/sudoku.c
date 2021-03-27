#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for (int col=0; col<=8; col++){
      if(val==sudoku[i][col]){
        return 1;
      }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for (int row=0; row<=8; row++){
      if(val==sudoku[row][j]){
        return 1;
      }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  int row;//=(i/3)*3;
  int col;//=(j/3)*3;
  switch(i/3){
    case 0:
      row=0;
      break;
    case 1:
      row=3;
      break;
    case 2:
      row=6;
      break;
  }
  switch(j/3){
    case 0:
      col=0;
      break;
    case 1:
      col=3;
      break;
    case 2:
      col=6;
      break;
  }
  // BEG TODOs
  for(int k=0; k<3; k++){
    for(int l=0; l<3;l++){
      if(val==sudoku[row+k][col+l]){
        return 1;
      }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_col(val, j, sudoku)!=1 || is_val_in_row(val, i, sudoku)!=1 || is_val_in_3x3_zone(val, i, j, sudoku)!= 1){
    return 0;
  }
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  // BEG TODO.
int i, j;
int counter=0;
  /*for(i=0; i<=8; i++){
    for(j=0; j<=8; j++){
        if(sudoku[i][j]==0){
          break;
        }
    }
    if(sudoku[i][j]==0){
       break;
    }
  }
  if(i>8 && j>8){
    return 1;
  }*/

for(i=0; i<=8; i++){
    for(j=0; j<=8; j++){
      if(sudoku[i][j]==0){
        break;
      }
    }
  if(sudoku[i][j]==0){
    break;
  }
}
if(i>8 && j>8){
return 1;
}
if(sudoku[i][j]==0){
for (int num =1; num<=9; num++){
  if(is_val_valid(num, i, j, sudoku)==1){
    sudoku[i][j]=num;
    if(solve_sudoku(sudoku)==1){
      return 1;
    }
    else{
      sudoku[i][j]=0;
    }
  }
}
  //return 0;
}
return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
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





