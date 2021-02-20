;
;
;
.ORIG x3000
	
; The program's main loop involves checking input 
; for, in specific order: '=' (equals sign), ' '
; (space), '+' (plus sign), '-' (minus sign), 
; '*' (multiply sign), '/' (divide sign), '^'
; (exponent sign), and a number between 0-9, inclusive.
; If the input does not match any of these, then
; the program goes into the INVALID_EXPRESSION
; subroutine to output "Invalid Expression". The program
; continues until an '=' is found. If successful, then
; the result is displayed in hexadecimal format to
; the screen, and also stored into R5. If at any point
; there is an error, such as attempting to perform 
; an operation without anything on the stack (underflow)
; then the program goes into INVALID_EXPRESSION subroutine.
; To make the program cleaner, a SAFE_POP2 and a SAFE_PUSH
; subroutine is made that calls the POP and PUSH subroutine,
; and also handles any error that occurs (such as over/underflow)
; by going into the INVALID_EXPRESSION subroutine.

; Partners: clegras2, htd2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here

; Read entered char into R0 and echo to screen
; Go to FINISH once an '=' sign has been typed in
; Uses R1 and R2 to check for '='
INPUT 
	GETC				; Get char into R0
    OUT					; Echo back char typed
	;Same thing as IN 
TEST_EQUALS
	; Check for '='
	LD R1, ASCII_VAL_NEG_EQUALS
    ADD R1, R1, R0
	BRnp TEST_SPACE
	JSR FINISH
TEST_SPACE
	; Check for space
	LD R1, ASCII_VAL_NEG_SPACE
    ADD R1, R1, R0
	BRnp TEST_PLUS
	BRnzp INPUT
TEST_PLUS
	; Check for '+'
	LD R1, ASCII_VAL_NEG_PLUS
    ADD R1, R1, R0
	BRnp TEST_MINUS
	JSR PLUS
	BRnzp INPUT
TEST_MINUS
	; Check for '-'
	LD R1, ASCII_VAL_NEG_MINUS
    ADD R1, R1, R0
	BRnp TEST_MULTIPLY
	JSR MINUS
	BRnzp INPUT
TEST_MULTIPLY
	; Check for '*'
	LD R1, ASCII_VAL_NEG_MULTIPLY
    ADD R1, R1, R0
	BRnp TEST_DIVIDE
	JSR MULTIPLY
	BRnzp INPUT
TEST_DIVIDE
	; Check for '/'
	LD R1, ASCII_VAL_NEG_DIVIDE
    ADD R1, R1, R0
	BRnp TEST_EXPONENT
	JSR DIVIDE
	BRnzp INPUT
TEST_EXPONENT
	; Check for '^'
	LD R1, ASCII_VAL_NEG_EXPONENT
    ADD R1, R1, R0
	BRnp TEST_FOR_NUM
	JSR EXPONENT
	BRnzp INPUT
TEST_FOR_NUM
	; Check if in between '0' and '9'
	; If it is a num, push its value to the stack
	LD R1, ASCII_VAL_NEG_0
    ADD R0, R1, R0
	; If result is negative, ASCII char is below '0'
	; and is not a number, so invalid expression.
	BRzp TEST_NUM_UPPER_LIMIT
	JSR INVALID_EXPRESSION
TEST_NUM_UPPER_LIMIT
	ADD R1, R0, #-9
	; If result is positive, ASCII char is above '9'
	; and is not a number, so invalid expression.
	BRnz #2
	JSR INVALID_EXPRESSION
	BRnzp INPUT
	JSR HANDLE_INPUT_NUM
	BRnzp INPUT

; Stores the 2s complements of the ASCII values of characters to check
ASCII_VAL_NEG_EQUALS		.FILL xFFC3
ASCII_VAL_NEG_SPACE			.FILL xFFE0
ASCII_VAL_NEG_PLUS			.FILL xFFD5
ASCII_VAL_NEG_MINUS			.FILL xFFD3
ASCII_VAL_NEG_MULTIPLY		.FILL xFFD6
ASCII_VAL_NEG_DIVIDE		.FILL xFFD1
ASCII_VAL_NEG_EXPONENT		.FILL xFFA2
ASCII_VAL_NEG_0				.FILL xFFD0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; operate in R0
HANDLE_INPUT_NUM
	ST R7, HANDLE_INPUT_NUM_SAVE_R7
	
	JSR SAFE_PUSH

	LD R7, HANDLE_INPUT_NUM_SAVE_R7
	RET

HANDLE_INPUT_NUM_SAVE_R7 .BLKW 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ST R7, PLUS_SAVE_R7

	JSR SAFE_POP2
	ADD R0, R3, R4			; Add two popped operands
	JSR SAFE_PUSH
	
	LD R7, PLUS_SAVE_R7
	RET

PLUS_SAVE_R7 .BLKW 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MINUS
; Computes the 2s complement of R3 and then computes R0 <- R4 - R3
	ST R7, MINUS_SAVE_R7

	JSR SAFE_POP2
	NOT	R3, R3
	ADD R3, R3, #1
	ADD R0, R3, R4
	JSR SAFE_PUSH

	LD R7, MINUS_SAVE_R7
	RET

MINUS_SAVE_R7 .BLKW 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MULTIPLY
; Computes R0 <- R3 * R4
	ST R7, MULTIPLY_SAVE_R7
	
	JSR SAFE_POP2
	; Actual multiply algorithm
	; Uses R3 as a counter
	; Adds R4 to R0, R3 times
	AND R0, R0, #0		; Clear R0 to hold the result
	ADD R3, R3, #0		; Set CC
MULT_LOOP
	BRz MULTIPLY_DONE
	ADD R0, R0, R4
	ADD R3, R3, #-1
	BRnzp MULT_LOOP
MULTIPLY_DONE
; Push the results once the multiplication is done
	JSR SAFE_PUSH

	LD R7, MULTIPLY_SAVE_R7
	RET
	
MULTIPLY_SAVE_R7 .BLKW 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIVIDE
	ST R7, DIVIDE_SAVE_R7

	JSR SAFE_POP2
	; Actual divide algorithm
	; Uses R3 as divisor and R4 as divided number
	; Stores R4/R3 to R0
	; Uses R1 as temporary register for calculations
	; Uses R2 to store negative R3
	; Discards any remainder
	AND R0, R0, #0			; Prepare R0 to hold result
	NOT R2, R3				; Check if R4<R3
	ADD R2, R2, #1			; by R4-R3
DIVIDE_LOOP
	ADD R1, R4, R2			; and checking 
	BRn DIVIDE_DONE			; CC
	ADD R4, R4, R2			; Subtract R3 from R4
	ADD R0, R0, #1			; Increment result count
	BRnzp DIVIDE_LOOP

DIVIDE_DONE
	JSR SAFE_PUSH			; Push result in R0 to stack

	LD R7, DIVIDE_SAVE_R7
	RET
	
DIVIDE_SAVE_R7 .BLKW 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXPONENT
;your code goes here
	ST R7, EXPONENT_SAVE_R7

	JSR	SAFE_POP2
	; Calculates R4^R3
	; Stores result in R0
	; Multiply R4 to R4, R3 times
	AND R0, R0, #0
	ADD R0, R0, #1
	ADD R3, R3, #0		; Set CC
EXPONENT_LOOP
	; EXPONENT_LOOP loops R3 times
	BRz	EXPONENT_DONE

	; Multiply algorithm
	; Multiply R4 by R0 and store into R0
	; Uses R1 as a counter (temp register to store R0
	; during calculations)
	; Adds R4 to R0, R1 times
	; R0 holds result
	ADD R1, R0, #0		; Copy R0 to R1
	AND R0, R0, #0		; Clear R0
	ADD R1, R1, #0		; set CC
EXPONENT_MULT_LOOP
	BRz EXPONENT_MULTIPLY_DONE
	ADD R0, R0, R4
	ADD R1, R1, #-1
	BRnzp EXPONENT_MULT_LOOP
EXPONENT_MULTIPLY_DONE

	ADD R3, R3, #-1		; Decrement exponents done counter
	BRnzp EXPONENT_LOOP

EXPONENT_DONE

	JSR SAFE_PUSH		; Push result into stack

	LD R7, EXPONENT_SAVE_R7
	RET

EXPONENT_SAVE_R7 		.BLKW 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

FINISH
; ''=' has been typed
; For checking if expression is valid
; Valid if only 1 value left in stack

	; Pop top value off
	JSR POP
	; Check if pop was successful
	ADD R5, R5, #0
	BRz STACK_HAS_VALUE
	JSR INVALID_EXPRESSION
STACK_HAS_VALUE
	; Check if stack pointer is to x4000
	; to see if only 1 value was in the stack
	LD R5, STACK_TOP
	LD R4, FINISH_NEG_STACK_TOP
	ADD R5, R5, R4
	BRz STACK_ONLY_ONE_VAL
	JSR INVALID_EXPRESSION
STACK_ONLY_ONE_VAL
	; Everything is valid
	; Print hex value
	ADD R5, R0, #0			; Load result into R5
	ADD R3, R0, #0			; Load result into R3
	JSR PRINT_HEX			; Don't care about saving R7 since we HALT after
	HALT

FINISH_NEG_STACK_TOP	.FILL xC000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	; R3 contains value to be printed
	; R4 is temp register for calculations
	; R5 is number of bits in one 4-bit group processed counter
	; R6 is number of 4-bit groups processed counter

	; Save registers
	ST R3, PRINT_HEX_SAVE_R3
	ST R4, PRINT_HEX_SAVE_R4
	ST R5, PRINT_HEX_SAVE_R5
	ST R6, PRINT_HEX_SAVE_R6
	ST R7, PRINT_HEX_SAVE_R7

	; Initialize counter for how many 4-bit groups processed
	AND R6, R6, #0
	ADD R6, R6, #4

PRCS_NXT_BIT_GRP
	; Load R0 with upper 4 bits of the histogram entry
	AND R5, R5, #0		; Initialize counter for how many bits 
	ADD R5, R5, #4		; in one 4-bit group currently processed
	AND R0, R0, #0		; Clear R0 to prepare for new set of 4-bit group

GET_NXT_BIT
	ADD	R0, R0, R0		; Left shift R0
	ADD R3, R3, #0		; Set CC
	BRzp SKIP
	ADD R0, R0, #1		; Add 1 digit to R0
SKIP
	ADD R3, R3, R3		; Left shift R3
	ADD R5, R5, #-1		; Decrement bits processed counter
	BRp GET_NXT_BIT


; Check if R0 is a letter or number hexadecimal value
	ADD R4, R0, #-9		; Sets condition codes depending on letter or number hexadecimal value
	BRnz R0_IS_NUM 
	ADD R0, R0, #-9		; R0 is alpha so subtract 10 to get correct offset value from @ ASCII value
	LD R4, AT_VAL		; Load R4 with ASCII value of @ to calculate correct letter
	ADD R0, R0, R4
	OUT
	BRnzp CHK_ENTRY_CMPLT

R0_IS_NUM
	LD R4, ZERO_VAL		; Load R7 with ASCII value of 0 to calculate correct number
	ADD R0, R0, R4
	OUT

CHK_ENTRY_CMPLT
; Checks if all 4 groups of 4-bits is complete
	ADD R6, R6, #-1
	BRp PRCS_NXT_BIT_GRP

; Restore all registers
	LD R3, PRINT_HEX_SAVE_R3
	LD R4, PRINT_HEX_SAVE_R4
	LD R5, PRINT_HEX_SAVE_R5
	LD R6, PRINT_HEX_SAVE_R6
	LD R7, PRINT_HEX_SAVE_R7
	RET

AT_VAL		.FILL x0040		; ASCII value of @
ZERO_VAL	.FILL x0030		; ASCII value of 0
PRINT_HEX_SAVE_R3	.BLKW 1
PRINT_HEX_SAVE_R4	.BLKW 1
PRINT_HEX_SAVE_R5	.BLKW 1
PRINT_HEX_SAVE_R6	.BLKW 1
PRINT_HEX_SAVE_R7	.BLKW 1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

INVALID_EXPRESSION
; For invalid expressions
; Note we don't care about overwriting registers anymore since
; we will HALT immediately after
	LEA R0, INVALID_STRING_PROMPT
	PUTS
	HALT				; We are done

INVALID_STRING_PROMPT .STRINGZ "Invalid Expression"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Safe POP2 and PUSH routines
; Performs pop and push if everything is successful
; Jumps to INVALID_EXPRESSION if any error occurs
; Safe POP2 pops top two values off into R3 and R4

; SAFE PUSH
; Input: R0
; If anything goes wrong, calls INVALID_EXPRESSION
SAFE_PUSH
	ST R5, SAFE_PUSH_SAVE_R5
	ST R7, SAFE_PUSH_SAVE_R7
	JSR PUSH
	ADD R5, R5, #0				; Set CC
	BRz NUM_PUSH_SUCCESS
	JSR INVALID_EXPRESSION
NUM_PUSH_SUCCESS
	LD R5, SAFE_PUSH_SAVE_R5
	LD R7, SAFE_PUSH_SAVE_R7
	RET

SAFE_PUSH_SAVE_R5	.BLKW 1
SAFE_PUSH_SAVE_R7	.BLKW 1

; SAFE POP 2
; Output: topmost value to R3, second topmost to R4
; If anything goes wrong, calls INVALID_EXPRESSION
SAFE_POP2
	ST R0, SAFE_POP2_SAVE_R0
	ST R5, SAFE_POP2_SAVE_R5
	ST R7, SAFE_POP2_SAVE_R7
	; Attempt to topmost value
	JSR POP
	ADD R5, R5, #0				; Set CC
	BRz NUM_POP2_1_SUCCESS
	JSR INVALID_EXPRESSION
NUM_POP2_1_SUCCESS
	ADD R3, R0, #0				; Get topmost value in R3
	; Attempt to pop next value
	JSR POP
	ADD R5, R5, #0				; Set CC
	BRz NUM_POP2_2_SUCCESS
	JSR INVALID_EXPRESSION
NUM_POP2_2_SUCCESS
	ADD R4, R0, #0				; Get second topmost value in R4
	; Restore registers
	LD R0, SAFE_POP2_SAVE_R0
	LD R5, SAFE_POP2_SAVE_R5
	LD R7, SAFE_POP2_SAVE_R7
	RET

SAFE_POP2_SAVE_R0	.BLKW 1
SAFE_POP2_SAVE_R5	.BLKW 1
SAFE_POP2_SAVE_R7	.BLKW 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; PUSH and POP routines as given are below

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
