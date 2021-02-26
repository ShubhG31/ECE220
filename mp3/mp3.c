#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;
  long computation = 1 ;          // Long unsigned variable is declared and intialized to be used later

  printf("Enter a row index: ");
  scanf("%d",&row);

/* Introduction Paragraph: This program prints out a specific row of the pascal triangle. The code takes the input value 
 which is the row number. The code uses a formula given to calculate each value in the row. */
// partners: clegras2, htd2

  // Write your code here
  for(int k = 0; k<=row; k++){      // for loop for the number of thr number printed 
    computation = 1;                // Resets computation to value of 1
    for (int i=1 ; i<=k; i++){      // For loop for each coefficient value printed 
    computation *=(row + 1 - i);    // the numerator of the pascal triangle equation 
    computation /= i;               // the denominator of the pascal triangle equation 
    }
    printf(" %lu", computation);    // the value is printed when the computation is complete    
  }
  printf("\n");                     // new line is printed when row is printed
  return 0;
}