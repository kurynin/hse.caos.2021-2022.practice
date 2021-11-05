// Работа с глобальными переменными
// Вывести длину строки, указатель на которую сохранен в глобальной переменной hello
// Имя функции: print_hello_length

    .text
    .global print_hello_length
print_hello_length:
    mov hello, %edx
    jmp count
return:
    mov %edx, %eax
    sub hello, %eax
    call writei32
    ret

count:
    movb (%edx), %bl
    test %bl, %bl
    jz return
    inc %edx
    jmp count