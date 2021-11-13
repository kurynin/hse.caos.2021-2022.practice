/*
Написать функцию int nth_element(int a, int d, int n) для расчета n-ого члена (An) арифметической прогрессии
с первым членом A1=a и разностью d.
Программа должна следовать стандартным соглашениям о вызовах

Состояние стека после пролога:
├── (+16)   n
├── (+12)   d
├── (+8)    a
├── (+4)    A_ret
└── (0)     ebp_prev  <- esp, ebp

*/
    .global nth_element
    .text
nth_element:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %eax  // %eax = a
    mov 12(%ebp), %edx // %edx = d
    mov 16(%ebp), %ecx // %ecx = n
    dec %ecx            // n -= 1
    imul %edx, %ecx     // n *=  d
    add %ecx, %eax      // a += n

    mov %ebp, %esp
    pop %ebp
    ret













