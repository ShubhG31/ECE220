/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/*
** Introductory paragraph: I followed exactly what the wiki listed. Namely, I implemented
** the set_seed, the start_game, and the make_guess functions. To implement the set_seed function
** I used sscanf to see if there is exactly 1 integer input in the string. If not, I returned 0. 
** If there is exactly 1 integer input, then it is valid, so I called srand() with the given seed 
** input and returned 1. For the start_game function, I used rand()%8 to generate a pseudo random
** number from 0 to 7, and used that as an index to generate a random string from the pool array.
** I did this four times to copy four pseudorandom strings from pool to solutions using the strcpy 
** function. To end, I initialized the guess_number variable to 1 and the max_score var to -1. Finally,
** to implement the make_guess function, I first checked if the input guess_str array is valid. Again, 
** I made use of the sscanf function to check there are exactly four strings (valid input), and if so,
** put them in another array of strings. If the input was not valid, I printed the invalid prompt 
** and returned 0. If exactly four strings, I continue to check if those four strings are in the pool
** array and if they are valid. If they are not, then again I print the invalid prompt and return 0. 
** Once the validity of the guess input is verified, I can then compare the guess with the solutions.
** To do this, I first calculated the number of perfect matches by iterating over all elements in the
** solutions and guesses array in order. If there is a match, I mark that element as matched. After, 
** I can then check for misplaced matches by iterating over each unmatch guess, with each iteration 
** iterating over each unmatched solution, to check if they are in the solution. If they are, then 
** I can mark that guess and solution as matched. Then, we can calculate the current and max score,
** and print the prompt displaying the number of guesses, score, and max score. At the end, I increment
** the guess_number variable, and decide whether to return 2 for a perfectly correct answer or return 1
** for a not perfectly correct answer.
**
** Partners: clegras2, htd2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
        // either no integer input, or both integer and some string, or multiple integers, or anything other than an integr
        // print error and return 0
        printf("set_seed: invalid seed\n");
        return 0;
    } else {
        // 1 integer is read so call srand and return 1
        srand(seed);
        return 1;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    // fill solutions array with 4 random strings from the pool array
    for (int i=0; i<4; i++) {
        // generate random integer from 0 to 7
        int randIndex = rand()%8;
        // copy string from pool to solutions
        strcpy(solutions[i], pool[randIndex]);
    }
    guess_number = 1;
    max_score = -1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
    // first check if guess_str is valid
    // sscanf (seed_str, "%d%1s", &seed, post) != 1
    char excess[2];
    char separatedGuesses[4][10];
    if (sscanf(guess_str, "%s %s %s %s %1s", separatedGuesses[0], separatedGuesses[1], separatedGuesses[2], separatedGuesses[3], excess) != 4) {
        // guess_str is not exactly only 4 strings so invalid
        // since invalid, print error message and return 0
        printf("make_guess: invalid guess\n");
        return 0;
    }
    // we have possibly valid guesses in the array separatedGuesses
    // we need to check each of them individually if they are in the pool and valid
    for (int i=0; i<4; i++) {
        if (!is_valid(separatedGuesses[i])) {
            // the input guess string is not in pool and is invalid
            // since invalid, print error message and return 0
            printf("make_guess: invalid guess\n");
            return 0;
        }
    }

    // now we can compare the guess with the solution
    int misplaced=0, perfect=0;

    // put all unmatched guess and solution indexes in an array
    int unmatchedGuess[4] = {0,1,2,3}, unmatchedSolution[4] = {0,1,2,3};
    // we will use the convention that if the index is -1, the index has already been matched

    // first we will compute the number of perfect matches
    for (int i=0; i<4; i++) {
        if (strcmp(solutions[i], separatedGuesses[i]) == 0) {
            // perfect match, so we can mark index i as matched in
            // unmatchedGuess and unmatchedSolution array, indicated by -1
            unmatchedGuess[i] = -1;
            unmatchedSolution[i] = -1;
            // Now increase the perfect match counter
            perfect++;
        }
    }

    // now we can compute the number of misplaced matches
    for (int i=0; i<4; i++) {
        // iterate over each unmatched guess
        // we know if unmatchedGuess[i]=-1, then it is already matched
        // so move on to next possible unmatched guess
        if (unmatchedGuess[i]==-1) {
            continue;
        }
        for (int j=0; j<4; j++) {
            // iterate over each unmatched solution to find a match for the guess
            // we know if unmatchedSolution[j]=0, then it is already matched
            // so move to next possible unmatched solution
            if (unmatchedSolution[j]==-1) {
                continue;
            }
            // Now we can check if the unmatched guess is the same as the unmatched solution
            if (strcmp(separatedGuesses[i], solutions[j]) == 0) {
                // we have found a match of the guess in solution, so increase misplaced counter
                misplaced++;
                // we can then mark it as matched
                unmatchedGuess[i] = -1;
                unmatchedSolution[j] = -1;
                // Now, break out of the inner for loop to move on to the next unmatched guess
                // in the outer for loop (if there are any remaining)
                break;
            }
        }
    }

    // Calculate the current score
    int currentScore = perfect*1000 + misplaced*100;
    // Adjust max_score if currentScore is higher
    max_score = (currentScore>max_score) ? currentScore : max_score;


    // Print the number of perfect and misplaced matches
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
    printf("Your score is %d and cur max score is %d.\n", currentScore, max_score);

    // Increment guess number. Note that in the main function, it would print the 
    // wrong number of guesses it took to get it right.
    guess_number++;

    // Now if the guess is correct (4 perfect guesses), we return 2
    // else, return 1 since guess is valid but not perfectly correct

    if (perfect==4) {
        return 2;
    } else {
        return 1;
    }

}


