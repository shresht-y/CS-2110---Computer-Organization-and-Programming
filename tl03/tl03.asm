;; TLDR Linked List Structure:
;;
;; For this Timed Lab, you are given a doubly-linked list and you need to check
;; if its data is a palindrome ignoring case.
;; Each node in the doubly-linked list is represented by three consecutive words in memory.
;; Each node has data, the address of the previous node, and the address of the next node.
;;
;; Given the address `node`, you can do
;; * `mem[node]` to get the data
;; * `mem[node + 1]` to get the address of the previous node
;; * `mem[node + 2]` to get the address of the next node

; Data for the one test
.orig x6000
        .fill 'a'
        .fill x0000
        .fill x4000
.end

.orig x4000
        .fill 'b'
        .fill x6000
        .fill x5000
.end

.orig x5000
        .fill 'A'
        .fill x4000
        .fill x0000
.end

.orig x3000

    ; One test is at the bottom of this file
    BR test_start


;; to_lowercase function
;; Parameter c: Character encoded in ASCII
;; Returns: Lowercase version of c if it's in the range 'A' to 'Z'; otherwise
;;          just c unchanged
;;
;; Examples:
;; * to_lowercase('a') == 'a'
;; * to_lowercase('A') == 'a'
;; * to_lowercase('5') == '5'

to_lowercase
.fill x1dba
.fill x7f84
.fill x7b83
.fill x1ba2
.fill x7180
.fill x7381
.fill x6344
.fill x2015
.fill x1040
.fill x080c
.fill x2013
.fill x1040
.fill x0209
.fill x2011
.fill x1040
.fill x7143
.fill x6180
.fill x6381
.fill x1d63
.fill x6f42
.fill x6b41
.fill xc1c0
.fill x7343
.fill x6180
.fill x6381
.fill x1d63
.fill x6f42
.fill x6b41
.fill xc1c0
.fill xffbf
.fill xffa6
.fill x0020


;; This function takes in two nodes from the doubly-linked list as input. It
;; outputs whether they contain equal data ignoring case. Note that case is
;; ignored. All the characters should be taken to lowercase before comparing
;; them.
;;
;; Parameter node1: The address of a node in the doubly-linked list
;; Parameter node2: The address of a node in the doubly-linked list
;; Returns: 1 if both nodes have the same data ignoring case, 0 otherwise
;;
;; Examples:
;; * are_letters_equal on node1 containing 'A' and node2 containing 'A' returns 1
;; * are_letters_equal on node1 containing 'A' and node2 containing 'a' returns 1
;; * are_letters_equal on node1 containing '5' and node2 containing '6' returns 0
;;
;; Pseudocode:
;; // (Checkpoint 1)
;; are_letters_equal(Node node1 (address), Node node2 (address)) {
;;      char letter1 = mem[node1];
;;      char letter2 = mem[node2];
;;
;;      letter1 = to_lowercase(letter1);
;;      letter2 = to_lowercase(letter2);
;;
;;      if (letter1 == letter2) {
;;          return 1;
;;      } else {
;;          return 0;
;;      }
;; }

are_letters_equal

    ;; TODO
    ;;stack buildup for 2 inputs
    ADD R6, R6, -4
    STR R7, R6, 2
    STR R5, R6, 1
    ADD R5, R6, 0
    ADD R6, R6, -5
    STR R0, R5, -1
    STR R1, R5, -2
    STR R2, R5, -3
    STR R3, R5, -4
    STR R4, R5, -5

    ;; pop address of letter1 -> R0
    LDR R0, R5, 4
    LDR R0, R0,0 

    ;; pop address of letter2 -> R0
    LDR R1, R5, 5
    LDR R1, R1,0 

    ;;push arguments for method call
    ADD R6, R6, -1
    STR R0, R6, 0
    JSR to_lowercase
    ;;pop lowercase value -> R0
    LDR R0, R6, 0 
    ADD R6, R6, 1

    ;;push arguments
    ADD R6, R6, -1
    STR R1, R6, 0
    ;;pop return value
    JSR to_lowercase
    LDR R1, R6, 0
    ADD R6, R6, 1

    ;;begin if statement

    ;;letter1-letter2==0
    NOT R1, R1
    ADD R1, R1, 1
    IF1 ADD R2, R1, R0
    BRnp ELSE
    AND R2, R2, 0 
    ADD R2, R2, 1 
    STR R2, R5, 3
    BR ENDIF1
    ELSE
    AND R2, R2, 0 
    STR R2, R5, 3
    ENDIF1


    ;;stack teardown 
    LDR R4, R5, -5
    LDR R3, R5, -4
    LDR R2, R5, -3
    LDR R1, R5, -2
    LDR R0, R5, -1
    ADD R6, R5, 0
    LDR R7, R5, 2
    LDR R5, R5, 1
    ADD R6, R6, 3



    RET

;; Takes in both the head and tail addresses for a doubly-linked list, and
;; returns whether the data contained inside is a palindrome ignoring case. Note
;; that case is ignored. All the characters should be taken to lowercase before
;; comparing them.
;;
;;
;; Parameter head: The address of the first node in the doubly-linked list
;; Parameter tail: The address of the last node in the doubly-linked list
;; Returns: 1 if the list's data represents a palindrome ignoring case; 0
;;          otherwise
;;
;; Examples:
;; * is_palindrome on "aba" returns 1
;; * is_palindrome on "abA" returns 1
;; * is_palindrome on "abba" returns 1
;; * is_palindrome on "ab!" returns 0
;; * is_palindrome on "Happy Birthday!" returns 0
;;
;; Pseudocode:
;; is_palindrome(Node head (address), Node tail (address)) {
;;      // (Checkpoint 2 - Base Case)
;;      if (head == 0 || tail == 0) {
;;          return 1;
;;      }
;;
;;      if (are_letters_equal(head, tail) == 0) {
;;          return 0;
;;      }
;;
;;      // (Checkpoint 3 - Recursion)
;;      Node new_head = mem[head + 2];
;;      Node new_tail = mem[tail + 1];
;;
;;      return is_palindrome(new_head, new_tail);
;; }

is_palindrome

    ;; TODO

    ;;stack buildup
    ADD R6, R6, -4
    STR R7, R6, 2
    STR R5, R6, 1
    ADD R5, R6, 0
    ADD R6, R6, -5
    STR R0, R5, -1
    STR R1, R5, -2
    STR R2, R5, -3
    STR R3, R5, -4
    STR R4, R5, -5

    ;;pop head -> R0
    LDR R0, R5, 4
    LDR R0, R0, 0

    ;;pop tail -> R1 
    LDR R1, R5, 5
    LDR R1, R1, 0

    ;;if head ==0 -> end recursion
    IF4 ADD R4, R0, 0 
    BRnp ENDIF4
    AND R4, R4, 0 
    ADD R4, R4, 1
    STR R4, R5, 3
    BR ENDRECURSION
    ENDIF4

    ;;if tail == 0 -> end recursion
    IF2 ADD R4, R1, 0 
    BRnp ENDIF2
    AND R4, R4, 0
    ADD R4, R4, 1
    STR R4, R5, 3
    BR ENDRECURSION
    ENDIF2
    
    ;;push values for subroutine
    LDR R0, R5, 4
    LDR R1, R5, 5
    ADD R6, R6, -2  

    STR R0, R6, 0 
    STR R1, R6, 1 
    JSR are_letters_equal
    ;;pop return values and arguments
    ;;return value -> R2
    LDR R2, R6, 0 
    ADD R6, R6, 3

    ;;if return value = 0, return 0 
    IF3 ADD R2, R2, 0 
    BRnp ENDIF3
    AND R4, R4, 0 
    STR R4, R5, 3
    BRz ENDRECURSION
    ENDIF3

    ;;get head address -> R0, then add 2, then load the value 
    LDR R0, R5, 4
    ADD R0, R0, 2
    LDR R0, R0, 0

    ;;get tail address -> R1, then add 1, then load the value 
    LDR R1, R5, 5 
    ADD R1, R1, 1 
    LDR R1, R1, 0 

    ;; push arguments for recursion 
    ADD R6, R6, -2 
    STR R0, R6, 0 
    STR R1, R6, 1
    JSR is_palindrome
    ;;pop return value into R0, and pop off arguments 
    LDR R0, R6, 0
    STR R0, R5, 3
    ADD R6, R6, 3
    BR ENDRECURSION


    ENDRECURSION
    ;;stack teardown 
    LDR R4, R5, -5
    LDR R3, R5, -4
    LDR R2, R5, -3
    LDR R1, R5, -2
    LDR R0, R5, -1
    ADD R6, R5, 0
    LDR R7, R5, 2
    LDR R5, R5, 1
    ADD R6, R6, 3
    RET


; Helper code that runs one test
test_start

    ; Set up the stack
    LD R6, initial_r6

    ; Place arguments on the stack
    LD R0, head_addr
    LD R1, tail_addr
    ADD R6, R6, -2
    STR R0, R6, 0
    STR R1, R6, 1

    ; Set all the other registers to notable values
    ; Done to ease debugging
    LD R0, initial_r0
    LD R1, initial_r1
    LD R2, initial_r2
    LD R3, initial_r3
    LD R4, initial_r4
    LD R5, initial_r5
    LD R7, initial_r7

    ; Call the function
    ; Pop off return value and arguments
    JSR is_palindrome
    ADD R6, R6, 3

    HALT

; Easy to recognize initial values for registers
; Chosen to ease debugging
initial_r0 .fill xDEAD
initial_r1 .fill xBEEF
initial_r2 .fill x2110
initial_r3 .fill x2200
initial_r4 .fill x4290
initial_r5 .fill xCAFE
initial_r6 .fill xF000
initial_r7 .fill x8000

; Arguments to pass to the subroutine
head_addr .fill x6000
tail_addr .fill x5000

.end
