;;=============================================================
;; CS 2110 - Fall 2022
;; Homework 5 - fiveCharacterStrings
;;=============================================================
;; Name: 
;;=============================================================

;; 	Pseudocode (see PDF for explanation)
;;
;; 	int count = 0; (keep count of number of 5-letter words)
;; 	int chars = 0; (keep track of length of each word)
;; 	int i = 0; (indexer into each word)
;; 	String str = "I enjoy CS 2110 and assembly makes me smile! "; (sample string)
;;  while(str[i] != '\0') {
;;		if (str[i] != ' ')  {
;;			chars++;
;;		}
;;		else {
;;			if (chars == 5) {
;;				count++;   
;			}
;;			chars = 0;
;;		}
;;		i++;
;;	}
;;	mem[ANSWER] = count;
;;
;; ***IMPORTANT***
;; - Assume that all strings provided will end with a space (' ').
;; - Special characters do not have to be treated differently. For instance, strings like "who's" and "Wait," are considered 5 character strings.

.orig x3000
	;; count -> R1
	AND R1, R1, #0

	;; chars -> R2
	AND R2, R2, #0

	;; i -> R3
	AND R3, R3, #0


	;;while loop 
	WHILE1 ADD R4, R4, 0
	;; str[i] -> R4
	LD R0, STRING
	ADD R0, R3, R0
	LDR R4, R0, #0
	BRz ENDW1
		LD R5, SPACE
		IF1 ADD R0, R4, R5
		BRz ELSE1
		ADD R2, R2, #1
		BR ENDIF1
		ELSE1
			IF2 ADD R0, R2, #-5
			BRnp ENDIF2
			ADD R1, R1, #1
			ENDIF2
			AND R2, R2, #0
		ENDIF1
	ADD R3, R3, #1
	BR WHILE1
	ENDW1 NOP

	ST R1, ANSWER
	HALT

;; DO NOT CHANGE THESE VALUES
SPACE 	.fill #-32
STRING	.fill x4000
ANSWER 	.blkw 1
.end

.orig x4000				;; DO NOT CHANGE THE .orig STATEMENT
	.stringz "I enjoy CS 2110 and assembly makes me smile! " ;; You can change this string for debugging!
.end