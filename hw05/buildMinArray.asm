;;=============================================================
;; CS 2110 - Fall 2022
;; Homework 5 - buildMinArray
;;=============================================================
;; Name: 
;;=============================================================

;; 	Pseudocode (see PDF for explanation)
;;
;;	int A[] = {-4, 2, 6}; (sample array)
;;	int B[] = {4, 7, -2}; (sample array)
;;	int C[3]; (sample array)
;;	int length = 3; (sample length of above arrays)
;;
;;	int i = 0;
;;	while (i < length) {
;;		if (A[i] < B[i]) {
;;			C[i] = A[i];
;;		}
;;		else {
;;			C[i] = B[i];
;;		}
;;		i++;
;;	}

.orig x3000
	LD R1, LENGTH

	;; setting i
	AND R2, R2, #0

	;; calculate i - length < 0 
	NOT R1, R1
	ADD R1, R1, #1

	WHILE1 ADD R0, R2, R1
		BRp ENDW1
		
		;;calculate A[i] --> R4
		
		LD R0, A
		ADD R0, R0, R2
		LDR R4, R0, #0

		LD R0, B
		ADD R0, R0, R2
		LDR R5, R0, #0

		NOT R6, R5
		ADD R6, R6, #1
		;;Begin if 
		ADD R6, R4, R6
		BRp EL1
		IF1
		LD R0, C 
		ADD R0, R0, R2
		STR R4, R0, #0
		BR ENDIF1
		EL1
		LD R0, C 
		ADD R0, R0, R2
		STR R5, R0, #0
		ENDEL1
		ENDIF1
		

		ADD R2, R2, #1
		BR WHILE1
	ENDW1 NOP
	
	HALT

A 		.fill x3200		;; DO NOT CHANGE
B 		.fill x3300		;; DO NOT CHANGE
C 		.fill x3400		;; DO NOT CHANGE
LENGTH 	.fill 3			;; You can change this value if you increase the size of the arrays below
.end

.orig x3200				;; Array A : You can change these values for debugging! DO NOT CHANGE THE .orig STATEMENT
	.fill -4
	.fill 2
	.fill 6
.end

.orig x3300				;; Array B : You can change these values for debugging! DO NOT CHANGE THE .orig STATEMENT
	.fill 4
	.fill 7
	.fill -2
.end

.orig x3400				;; DO NOT CHANGE THE .orig STATEMENT
	.blkw 3				;; Array C: Make sure to increase block size if you add more values to Arrays A and B!
.end