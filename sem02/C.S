/*
Стековый калькулятор.
Определяем статический стек ёмкостью N машинных слов.
На стандартный вход поступают команды:
0 x (положить в стек число x),
1 (сложить два верхних числа в стеке и положить на стек результат),
2 (распечатать верхнее число в стеке),
3 (удалить верхний элемент стека).
*/

    .text
    .global main
main:
    call readi32
    jc exit
    movl jmptab(,%eax,4), %eax  // загружаем адрес из таблицы адресов
    jmp *%eax                   // косвенный переход
jmptab: .int D0, D1, D2, D3     // записываем адреса меток
D0:
    call readi32
    push %eax
    jmp main
D1:
    pop %eax
    mov %eax, %edx
    pop %eax
    add %edx, %eax
    push %eax
    jmp main
D2:
    mov (%esp), %eax
    call writei32
    jmp main
D3:
    pop %eax
    jmp main
exit:
    call finish
