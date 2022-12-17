;;=============================================================
;;  CS 2110 - Fall 2022
;;  Homework 6 - Selection Sort
;;=============================================================
;;  Name:
;;============================================================

;;  In this file, you must implement the 'SELECTION_SORT' subroutine.

;;  Little reminder from your friendly neighborhood 2110 TA staff: don't run
;;  this directly by pressing 'Run' in complx, since there is nothing put at
;;  address x3000. Instead, call the subroutine by doing the following steps:
;;      * 'Debug' -> 'Simulate Subroutine Call'
;;      * Call the subroutine at the 'SELECTION_SORT' label
;;      * Add the [arr (addr), length] params separated by a comma (,) 
;;        (e.g. x4000, 5)
;;      * Proceed to run, step, add breakpoints, etc.
;;      * SELECTION_SORT is an in-place algorithm, so if you go to the address
;;        of the array by going to 'View' -> 'Goto Address' -> 'Address of
;;        the Array', you should see the array (at x4000) successfully 
;;        sorted after running the program (e.g [2,3,1,1,6] -> [1,1,2,3,6])

;;  If you would like to setup a replay string (trace an autograder error),
;;  go to 'Test' -> 'Setup Replay String' -> paste the string (everything
;;  between the apostrophes (')) excluding the initial " b' ". If you are 
;;  using the Docker container, you may need to use the clipboard (found
;;  on the left panel) first to transfer your local copied string over.

.orig x3000
    ;; You do not need to write anything here
    HALT

;;  SELECTION_SORT Pseudocode (see PDF for explanation and examples)
;; 
;;  SELECTION_SORT(int[] arr (addr), int length) {
;;      if (length <= 1) {
;;          return;
;;      }
;;      int largest = 0;
;;      for (int i = 1; i < length; i++) {
;;          if (arr[i] > arr[largest]) {
;;              largest = i;
;;          }
;;      }
;;      int temp = arr[length - 1];
;;      arr[length - 1] = arr[largest];
;;      arr[largest] = temp;
;;
;;      SELECTION_SORT(arr, length - 1);
;;      return;
;;  }

SELECTION_SORT ;; Do not change this label! Treat this as like the name of the function in a function header
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

    ;;pop length value 
    LDR R0, R5, 5

    ;;length - 1 <= 0
    ENDCONDITION ADD R1, R0, #-1
    BRnz ENDSELECTIONSORT

    ;;int largest = 0
    AND R1, R1, #0
    
    ;;begin for loop 
    ;;int i = 1
    AND R2, R2, #0
    ADD R2, R2, #1

    FOR1
    LDR R0, R5, 5
    ;;-i 

    NOT R3, R2
    ADD R3, R3, #1
    ADD R3, R3, R0
    BRnz ENDFOR1

        ;;getting arr[i]
        LDR R0, R5, 4
        ADD R0, R0, R2
        LDR R3, R0, #0
        ;;getting arr[largest]
        LDR R0, R5, 4
        ADD R0, R0, R1 
        LDR R4, R0, #0
        ;;-arr[largest]
        NOT R4, R4 
        ADD R4, R4, #1
        ;; if arr[i] - arr[largest] > 0 
        IF1 ADD R4, R3, R4 
        BRnz ENDIF1
            AND R1, R1, #0
            ADD R1, R1, R2
        ENDIF1

    ;;i++
    ADD R2, R2, #1
    BR FOR1
    ENDFOR1
    ;;Getting length again, length -1
    LDR R0, R5, 5
    ADD R0, R0, #-1
    ;;Grabbing address 
    LDR R2, R5, 4
    ;;int temp = arr[length -1]
    AND R3, R3, #0
    ADD R2, R2, R0
    LDR R3, R2, #0

    ;;arr[length - 1] = arr[largest];
    
    LDR R4, R5, 4
    ADD R0, R4, R1
    LDR R0, R0, #0
    STR R0, R2, #0 

    ;;arr[largest] = temp
    LDR R4, R5, 4
    ADD R1, R4, R1
    STR R3, R1, #0

    ;; push arguments for recursion 
    ADD R6, R6, -2
    ;;address -> R2
    LDR R2, R5, 4

    ;;length -1 -> R0
    LDR R0, R5, 5
    ADD R0, R0, #-1

    STR R2, R6, 0
    STR R0, R6, 1

    JSR SELECTION_SORT
    ENDSELECTIONSORT

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

;; Needed to Simulate Subroutine Call in Complx
STACK .fill xF000
.end

.orig x4000	;; Array : You can change these values for debugging!
    .fill 2
    .fill 3
    .fill 1
    .fill 1
    .fill 6
.end