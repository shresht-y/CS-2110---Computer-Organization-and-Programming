.orig x0000
LD R0, NUM
LD R1, ZERO 
TWOS R0, R0
HALT



NUM .fill 1
ZERO .fill 0
.end
;R0 = -1, R1 = 0, nzp = 0b100