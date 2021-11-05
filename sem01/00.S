//#include "1.txt"
/* */
.globl main
main:
    mov $1, %eax // eax := 1
    call writei32
    call nl
    call finish

