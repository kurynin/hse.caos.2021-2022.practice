// Работа с глобальными переменными
// Вывести длину строки, заданной в глобальной переменной str
    .text
    .global main
main:
    mov $str, %edx // обратить внимание на $
    jmp count
return:
    mov %edx, %eax
    sub $str, %eax
    call writei32
    call finish

count:
    movb (%edx), %bl
    test %bl, %bl
    jz return
    inc %edx
    jmp count
str:
    .asciz "hello 12345"
