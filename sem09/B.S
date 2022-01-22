/*
На языке ассемблера напишите подпрограмму dp
со следующим прототипом (на Си):

double dp(int n, const double *x, const double *y);

Подпрограмма должна вычислить скалярное произведение
векторов x и y, каждый из которых имеет размер n.

Воспользоваться горизонтальным сложением.
*/

    .global dp
dp:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %eax
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx

    xorpd %xmm0, %xmm0 // answer

loop:
    cmp $2, %eax
    jl last_digit
    // movupd - загрузить дабл
    movupd (%ecx), %xmm1 // тут два дабла
    movupd (%edx), %xmm2 // тут тоже
    mulpd  %xmm2, %xmm1
    addpd %xmm1, %xmm0
    sub $2, %eax
    add $16, %ecx
    add $16, %edx
    jmp loop

last_digit:
    haddpd %xmm0, %xmm0
    cmp $1, %eax
    jne end

    movsd (%ecx), %xmm1
    mulsd (%edx), %xmm1
    addsd %xmm1, %xmm0

end:
    sub     $8, %esp        // резервируем память
    movsd   %xmm0, (%esp)   // копируем значение double из %xmm0 в стек
    fldl    (%esp)          // загружаем из стека на %st(0)
    add     $8, %esp        // очищаем стек

    mov %ebp, %esp
    pop %ebp
    ret
