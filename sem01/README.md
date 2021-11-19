# Семинар 1

## Дополнительные материалы

* [Методичка 2020-21 года](https://github.com/blackav/hse-caos-2020/tree/master/07-asm1)

## Компиляция и запуск программ

```
>> gcc -m32 -Wall -Werror file.S simpleio_i686.S -ofile

>> ./file
```

*Note* Вместо добавления simpleio_i686.S в список файлов для компиляции можно внутри file.S использовать
директиву ```#include "simpleio_i686.S"``` — это позволит локально успешно скомпилировать решение,
на при посылке на сервер ejudge этот способ работать **не будет**.

## Задачи на семинар

### 00.S

Демонстрация печати числа 1.

### 01.S (Решение с семинара)

Программа читает c stdin знаковые 64-битное и 32-битное число
и выводит их сумму. В случае знакового переполнения программа
печатает -1. Если числа считать не удалось, программа печатает 0.