// Написать функцию diag
// float diag(float x, float y, float z);
// возвращающую корень из суммы квадратов x, y и z

    .global diag
diag:
    push %ebp
    mov  %esp, %ebp

    movss 8(%ebp), %xmm1      // x
    movss 12(%ebp), %xmm2     // y
    movss 16(%ebp), %xmm3     // z

    mulss %xmm1, %xmm1
    mulss %xmm2, %xmm2
    mulss %xmm3, %xmm3

    addss %xmm1, %xmm3
    addss %xmm2, %xmm3

    sqrtss %xmm3, %xmm3

    sub     $4, %esp        // резервируем память
    movss   %xmm3, (%esp)   // копируем значение float из %xmm3 в стек
    flds    (%esp)          // загружаем из стека на %st(0)
    add     $4, %esp        // очищаем стек

    pop  %ebp
    ret