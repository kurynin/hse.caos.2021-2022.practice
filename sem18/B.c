#include <sys/eventfd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// ### B

// Процесс порождает трех сыновей. Они пересылают некоторое число друг другу по кругу: 1 - 2 - 3 - 1 - ...
// Каждый раз при получении числа процесс печатает свой номер, значение числа,
// инкрементирует его и отправляет дальше по цепочке.
// Для синхронизации использовать eventfd.

void work(int num, int fd_from, int fd_to, int fd[], int max) {
    int res = 0;
    while (!res) {
        uint64_t tmp;
        read(fd_from, &tmp, sizeof(tmp));
        int val;
        read(fd[0], &val, sizeof(val));
        if (val != max) {
            printf("%d - %d\n", num, val);
            ++val;
        } else {
            res = 1;
        }
        write(fd[1], &val, sizeof(val));
        write(fd_to, &tmp, sizeof(tmp));
    }
    exit(0);
}


int main(int argc, char** argv) {
    int max = atoi(argv[1]);
    int fd1 = eventfd(1, 0);
    int fd2 = eventfd(0, 0);
    int fd3 = eventfd(0, 0);
    int fd[2];
    pipe(fd);
    if (!fork()) {
        work(1, fd1, fd2, fd, max);
    }
    if (!fork()) {
        work(2, fd2, fd3, fd, max);
    }
    if (!fork()) {
        work(3, fd3, fd1, fd, max);
    }
    int cur = 0;
    write(fd[1], &cur, sizeof(cur));
    close(fd1);
    close(fd2);
    close(fd3);
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    printf("DONE!\n");
    return 0;
}
