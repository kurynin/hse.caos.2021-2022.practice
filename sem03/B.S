/*
Написать программу-приветствие.
Программа печатает приглашение представиться, ожидает ввода беспробельной строки (<user>), длиной не более 20 символов,
и выводит фразу-приветствие HELLO <user>
*/
    .global main
    .text
main:
    push %ebp
    mov %esp, %ebp

    sub $21, %esp   // char buf[21]
    lea -21(%ebp), %ebx // вычисление адреса начала buf, сохранение в callee-saved регистре
    push $greeting  // stack: ebp ..21.. greeting
    call printf
    add $4, %esp    // stack: ebp ..21.. greeting
    // scanf("%20s", buf)

    push %ebx
    push $str   // stack: ebp ..21.. &buf &str
    call scanf

    add $8, %esp
    cmp $1, %eax
    jne j1

    // printf("Hello %s\n", buf)
    push %ebx
    push $hello
    call printf

j1:
    mov %ebp, %esp
    pop %ebp
    mov $0, %eax
    ret

greeting:
    .asciz "Enter name:"
hello:
    .asciz "Hello %s\n"
str:
    .asciz "%20s"
