/*
Написать программу, которая должна вызывать несколько раз функцию, имитирующую какую-то длительную работу.
Эта имитация заключается в "засыпании" на 1 секунду. Будем считать, что каждый раз функция выполняет `5%`
всей запланированной работы.

Программа должна печатать на экран ProgressBar и после каждого вызова указанной функции его обновлять.
По достижению 100% программа должна завершиться.

[--------------------] 0%
... // через 2 секунды работы
[**------------------] 10%
... // и т.д.
*/
#include <unistd.h>
#include <stdio.h>

enum {
    PERCENT = 5,
    LEN = 100 / PERCENT,
};

void print(unsigned p) {
    int p_ = p / PERCENT;
    printf("\r[");
    for (int i = 0; i != p_; ++i) {
        printf("*");
    }
    for (int i = p_; i != LEN; ++i) {
        printf("-");
    }
    printf("]%4u%%", p);
    fflush(stdout);
}

void f() {
    sleep(1);
}

int main() {
    print(0);
    for (int i = 0; i <= LEN; ++i) {
        f();
        print(PERCENT * i);
    }
    printf("\n");
}