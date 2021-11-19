/*
Написать
int scan(const char *fmt, ...);
*/
    .global scan
    .text
read_d:
    call readi32
    jc end
    jmp return

scan:
    push %ebp
    mov %esp, %ebp
    push %ebx
    push %esi
    lea 12(%ebp), %esi
    mov 8(%ebp), %ebx
    test %ebx, %ebx
    jz end
loop:
    movb (%ebx), %al
    inc %ebx
    test %al, %al
    jz end
    cmp $'d', %al
    je read_d
return:
    mov (%esi), %ecx
    mov %eax, (%ecx)
    add $4, %esi
    jmp loop
end:
    lea -8(%ebp), %esp
    mov %esi, %eax
    lea 12(%ebp), %esi
    sub %esi, %eax
    shr $2, %eax

    pop %esi
    pop %ebx
    pop %ebp
    ret