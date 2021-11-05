/*
Программа должна обойти все элементы массива и инициализировать поля sum суммой остальных полей
struct point
{
    int x, y, sum;
};
Размер - в глобальной переменной sz, а указатель на начало массива - в arr.
Глобальные переменные объявить в S-файле.
Имя функции:make_sum
*/
    .global make_sum, sz, arr
    .text
make_sum:
    mov sz, %edx
    mov arr, %ecx
loop:
    cmp $0, %edx
    jz end
    dec %edx
    mov (%ecx), %ebx    //  x = ... arr(%ecx, R, s)
    add $4, %ecx
    mov (%ecx), %eax  // y = ...
    add %ebx, %eax
    add $4, %ecx
    mov %eax, (%ecx)
    add $4, %ecx
    jmp loop
end:
    ret

    .data
sz:
    .int 0
arr:
    .int 0
