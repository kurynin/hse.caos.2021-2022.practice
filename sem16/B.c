// # B.c

// Программа каждую 1 сек печатает на экран счетчик секунд (начиная с 0).
// По нажатию на Ctrl+C в первый раз требуется вывести надпись
// Start counter
// При повторном нажатии Ctrl+C следует напечатать кол-во секунд, прошедших
// с прошлого нажатия, и завершить работу программы.

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile int count = 0;
volatile int is_first = 1;
volatile int time;
volatile int flag = 0;

void func(int n) {
    alarm(1);
    flag = 1;
    ++count;
}

void func2(int n) {
    if (is_first == 1) {
        is_first = 3;
        time = count;
    } else {
        is_first = 2;
    }
}


int main() {
    struct sigaction sa = {}; // инициализируем нулями
    sa.sa_flags = SA_RESTART; // restartable system calls
    sa.sa_handler = func;
    sigaction(SIGALRM, &sa, NULL);
    sa.sa_handler = func2;
    sigaction(SIGINT, &sa, NULL);
    alarm(1);
    while (1) {
        if (flag) {
            printf("%d\n", count);
            flag = 0;
        }
        if (is_first == 3) {
            printf("%s\n", "Start counter");
            is_first = 5;
        } else if (is_first == 2) {
            printf("Seconds: %d\n", count - time);
            exit(0);
        }
        pause();
    }
}
