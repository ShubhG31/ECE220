;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
; you will need to insert your code to print the histogram here

; Introduction: This part of the code takes the value loaded in the memory locations that have the values of repetition of characters. The memory values
; are loaded with the hex code and displayed to the user. The code goes through each character displays of the alphabet and displays the frequency of the 
; character is displayed in the hex value. The Hex would be calculated using loops that determine whether the decimal value is a letter or number, and 
; display it. 
; partners: htd2, clegras2

; R0 is used to store what is going to be outputted
; R1 will be used as the counter for how many lines will be displayed 
; R2 will used to store the address of where the histogram starts 
; R3 will counter for the inner loop for each HEX value 
; R4 is used to store the current Symbol (Starting with @)
; R5 stores the value inside HIST_ADDR (R2)
; R6 stores counter for the 16bit shifter 
; R7 is normal arithmetic 

	AND R0, R0, #0		; Clear R0 before use 	
	AND R1, R1, #0 		; Clear R1 before use 
	AND R2, R2, #0 		; Clear R2 before use
	AND R3, R3, #0 		; Clear R3 before use
	AND R4, R4, #0		; Clear R4 before use 
	AND R5, R5, #0 		; Clear R5 before use
	AND R6, R6, #0 		; Clear R6 before use
	AND R7, R7, #0 		; Clear R7 before use 

; Initialize the Registers to hold ascii values and histogram addresses
	LD R4, LETTER_1		; Loads R4 with x3F
	LD R1, NUM_BINS 	; Stores the number of lines to 
	LD R2, HIST_ADDR	; R2 stores the address of the histogram 
	

; This is a branch where the symbol and space is loaded into R0 and printed
NEXT	

	ADD R4, R4, #1		; Next symbol is loaded into R4 by incrementing value of LETTER_1
	AND R0, R0, #0		; Clear R0 so new value can be stored in R0 
	ADD R0, R0, R4		; Symbol is loaded in R0
	OUT			; Symbol is printed 
	
	LD R0,SPACE		; R0 is loaded with the ascii value of space character in SPACE
	OUT			; SPACE is printed 

; Hex Value printing code starts from here, the loop counter is intialized  

	AND R6, R6, #0		; R6 is cleared so it can be loaded with other values
	ADD R6, R6, #4		; initialize R6 Counter with 4 to be used as a counter for hex value
	
	
	LDR R5, R2, #0		; Value of histogram address is stored from R2 to R5 

; LOOP2 is used for each 4 bit section of the hex value

LOOP2	AND R3, R3, #0		; Clear R3 so it can be intialized with the value for the counter
	ADD R3, R3, #4		; R3 is stored with 4 so a fourth of hex code is stored in R0 
	AND R0, R0, #0		; Clear R0	

; LOOP is used for Left Bit shifting R0, 4 times   

LOOP	ADD R0, R0, R0 		; Left Bit Shift R0 by one 
	ADD R5, R5, #0		; Set CC for R5
	BRzp Counter		; if R5>= 0 then go to Counter
	ADD R0, R0, #1		; if R5<0 then R0 = R0 +1
Counter ADD R5, R5, R5		; Left Shift R5
	ADD R3, R3, #-1		; R3 counter is decremented 
	BRp LOOP		; If R3>0 then go to Loop
	
;Checks if its a Number or Letter 	
	AND R7, R7, #0		; R7 is cleared to be initialized
	ADD R7, R7, #-9		; R7 is initialized with -9
	
	ADD R7, R0, R7		; R7 is equal to the sum of R0 and -9
	BRnz NUMBER		; if Negative or zero go to Number Branch
	
;Loads Letter in R0 for hex code when R0-9 is positive   
	LD R0, LETTER_		; base ASCII Value of letter is loaded
	ADD R0, R0, R7		; ASCII Value of letter is Loaded
	OUT			; OUTPUT Value 
	ADD R6, R6, #-1		; Decrease HEX counter
	BRp LOOP2		; If counter positive go to loop branch
	BRnz RESET		; ELSE go to reset branch

;Loads Number in R0 for hex code when R0-9 is zero or negative
NUMBER 
	LD R0, NUMBER_		; base ASCII value of Number is loaded in R0 
	ADD R0, R0, R7		; ASCII value of Number is loaded in R0
	OUT			; OUTPUT Value
	ADD R6, R6, #-1 	; Decrease HEX counter 
	BRp LOOP2		; If counter positive go to loop branch
	BRnz RESET		; ELSE go to reset branch

; This part ends the line by printing out the new line and incrementing addresses and decrementing counter for lines 
RESET	
	AND R0, R0, #0 		; R0 is cleared so it can store a new value
	LD R0, NL		; New Line Character is stored in R0
	OUT 			; OUTPUT New Line character so next line can be printed
	ADD R2, R2, #1		; Increment address of Histogram to access values of the next character
	ADD R1, R1, #-1		; Decrement Line Counter 
	BRp NEXT		; If positive go to NEXT Branch ELSE end program
		



; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address 
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
 ;STR_START	.FILL STRING	; string starting address
 ;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."

SPACE 		.FILL x0020	; STORES ASCII value of SPACE
NL		.FILL x000A	; New Line ASCII Value
LETTER_		.FILL x0040	; The ASCII Value of '@'
NUMBER_		.FILL x0039	; The ASCII Value of '0'
LETTER_1	.FILL x003F	; The ascii value of ? before @

	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
