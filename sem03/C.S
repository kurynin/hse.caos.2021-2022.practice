/*
Написать функции с использованием системных вызовов read/write

void print(const char *buf, int length);
int input(char *buf, int buf_size); - возвращает число считанных байт
*/

#include <asm/unistd_32.h>

    .global print, input
    .text
input:
    // пролог
    push    %ebp
    mov     %esp, %ebp
    push    %ebx

    movl    $__NR_read, %eax      // или $3, %eax, если заголовочный файл не найден
    movl    $0, %ebx              // первый аргумент (0 - стандартный поток ввода) в %ebx
    movl    8(%ebp), %ecx         // второй аргумент (адрес переменной c) в %ecx
    movl    12(%ebp), %edx        // третий аргумент (размер переменной c) в %edx
    int     $0x80
    // в %eax будет возвращаемое значение read

    pop     %ebx
    // эпилог
    mov     %ebp, %esp
    pop     %ebp
    ret

// void print(const char *buf, int length);
print:
    // пролог
    push    %ebp
    mov     %esp, %ebp
    push    %ebx

    movl    $__NR_write, %eax      // или $4, %eax, если заголовочный файл не найден
    movl    $1, %ebx              // первый аргумент (1 - стандартный поток вывода) в %ebx
    movl    8(%ebp), %ecx         // второй аргумент (адрес переменной c) в %ecx
    movl    12(%ebp), %edx        // третий аргумент (размер переменной c) в %edx
    int     $0x80
    // в %eax будет возвращаемое значение write, но мы проигнорируем его

    pop    %ebx
    // эпилог
    mov     %ebp, %esp
    pop     %ebp
    ret
