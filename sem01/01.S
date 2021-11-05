/*
Программа читает c stdin знаковые 64-битное и 32-битное число
и выводит их сумму. В случае знакового переполнения программа
печатает -1. Если числа считать не удалось, программа печатает 0.
*/

//#include "simpleio_i686.S"

.global main
main:
    call readi64
    jc fail
    mov %eax, %ebx
    mov %edx, %ecx
    call readi32
    jc fail
    cdq
    add %ebx, %eax
    adc %ecx, %edx
    jo bad
    call writei64
    call nl
    call finish
bad:
    mov $-1, %eax
    call writei32
    call nl
    call finish
fail:
    xor %eax, %eax
    call writei32
    call nl
    call finish
// x < 0 => ~(-x) + 1 for x = -1 => 1110 + 1 = 1111 = 0xf
// -2 => 0010 1101 + 1 => 1110
//    1111
//    1110 +
// (1)1101 => 0010 + 1 => -3
//    0111 (+7)    (-8) 1000
//    1100 (-4)
// (1)0011