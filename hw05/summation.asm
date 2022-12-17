;;=============================================================
;; CS 2110 - Fall 2022
;; Homework 5 - summation
;;=============================================================
;; Name: 
;;=============================================================

;;  Pseudocode (see PDF for explanation)
;;
;;  int x = 6; (sample integer)
;;  int sum = 0;
;;  while (x > 0) {
;;      sum += x;
;;      x--;
;;  }
;;  mem[ANSWER] = sum;

.orig x3000
    ;; YOUR CODE HERE
    LD R1, x

    AND R2, R2, #0

    
    WHILE1 ADD R1, R1, #0
        BRnz ENDW1
        ADD R2, R2, R1
        ADD R1, R1, #-1
        BR WHILE1
    ENDW1 NOP
    ST R2, ANSWER

    HALT

    x      .fill 6      ;; You can change this value for debugging!
    ANSWER .blkw 1
.end