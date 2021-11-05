/*
Author: Roman Kurynin (rkurynin@hse.ru)

Программа должна обойти все элементы массива и инициализировать поля sum суммой остальных полей
struct point
{
    int x, y, sum;
};
Размер - в глобальной переменной sz, а указатель на начало массива - в arr.
Имя функции:make_sum
*/
.global make_sum, sz, arr
.data
sz: .int 0
arr: .int 0

.text
make_sum:
    push    %ebx
    push    %edi
    movl    arr, %edx // голова массива
    xor     %ecx, %ecx // индекс массива
    movl    sz, %edi
    imull     $12, %edi // размер в байтах
while:
    cmp     %edi, %ecx
    jge     fin
    leal    (%edx, %ecx), %eax // eax - указатель на текущий элемент
    movl    (%eax), %ebx
    addl    4(%eax), %ebx
    movl    %ebx, 8(%eax)

    add     $12, %ecx // смещаем индекс на 3 объекта типа int
    jmp     while
fin:
    pop     %edi
    pop     %ebx
    ret
