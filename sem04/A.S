/*
Написать функцию

typedef void (*modifier)(int *);
void foreach(int *arr, unsigned size, modifier p);
*/
    .global foreach
foreach:
    push %ebp
    mov %esp, %ebp
    push %esi
    push %edi
    push %ebx
    mov 8(%ebp), %esi
    mov 12(%ebp), %edi
    lea (%esi, %edi, 4), %edi
    mov 16(%ebp), %ebx
while:
    cmp %esi, %edi
    je ender
    push %esi
    call *%ebx
    add $4, %esp
    add $4, %esi
    jmp while

ender:
    lea -12(%ebp), %esp
    pop %ebx
    pop %edi
    pop %esi
    pop %ebp
    ret

