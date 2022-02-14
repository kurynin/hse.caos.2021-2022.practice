# Семинар 12

## Дополнительные материалы

* [Материалы по mmap 2020-21 года](https://github.com/blackav/hse-caos-2020/tree/master/14-mmap)

## Задачи на семинар

### A.c

Программа принимает на вход положительные числа `n` и `k`.
Следует распечатать в обратном порядке `n` первых чисел, делящихся на `k`.
Рекурсией и функциями `*alloc()` пользоваться запрещено.

### B.c

Программа должна посчитать количество пробельных символов в текстовом файле (имена задаются во входном потоке).
Системным вызовом `read()` пользоваться запрещено.

### C.c

Программа принимает в аргументах командной строки 2 параметра:

```text
    file1 file2
```

Требуется скопировать содержимое из `file1` в `file2` в обратном порядке байт.