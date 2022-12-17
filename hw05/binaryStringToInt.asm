;;=============================================================
;; CS 2110 - Fall 2022
;; Homework 5 - binaryStringToInt
;;=============================================================
;; Name: Shreshta Yadav
;;=============================================================

;;  Pseudocode (see PDF for explanation)
;;
;;  String binaryString = "00010101"; (sample binary string)
;;  int length = 8; (sample length of the above binary string)
;;  int base = 1;
;;  int value = 0;
;;  int i = length - 1;
;;  while (i >= 0) {
;;      int x = binaryString[i] - 48;
;;      if (x == 1) {
;;          if (i == 0) {
;;              value -= base;
;;          } else {
;;              value += base;
;;          }
;;      }     
;;      base += base;
;;      i--;
;;  }
;;  mem[mem[RESULTIDX]] = value;

.orig x3000
    ;;base -> R7
    AND R7, R7, #0
    ADD R7, R7, #1
    ;; Binary String -> R1
    LD R1, BINARYSTRING
    ;; length -> R2
    LD R2, LENGTH
    ;; value -> R3
    AND R3, R3, #0
    ;; i = length - 1 --> R2
    ADD R2, R2, #-1

    WHILE1 ADD R0, R2, #0
    BRn ENDW1
    
    ;;x = binaryString[i] - 48 -> R4
    LD R0, BINARYSTRING
    ADD R0, R0, R2
    LDR R4, R0, #0

    LD R0, ASCII

    ADD R4, R4, R0
    ;;if x == 1, then x - 1 = 0
    ADD R0, R4, #-1
    BRz IF1 
    BR ENDIF1
    IF1
        ADD R2, R2, #0
        BRz IF2
        BR ELSE1

        IF2
        NOT R0, R7
        ADD R0, R0, #1
        ADD R3, R3, R0
        BR ENDIF1
        ELSE1
        ADD R3, R3, R7
        BR ENDIF1
        ENDIF2
    ENDIF1

    ADD R7, R7, R7
    ADD R2, R2, #-1
    BR WHILE1
    ENDW1 NOP

    
    STI R3, RESULTIDX

    HALT
    
;; DO NOT CHANGE THESE VALUES
ASCII           .fill -48
BINARYSTRING    .fill x5000
LENGTH          .fill 8
RESULTIDX       .fill x4000
.end

.orig x5000                    ;;  DO NOT CHANGE THE .orig STATEMENT
    .stringz "00010101"        ;; You can change this string for debugging!
.end
