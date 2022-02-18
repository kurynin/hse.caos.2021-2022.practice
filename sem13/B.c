/*
Процесс-отец порождает сыновий процесс.
Процесс-сын считывает со стандартного входного потока целое число.
Если число неотрицательное, то оно возвращается в качестве кода возврата.
Если число отрицательное, то процесс должен завершиться вызовом abort().

Отец дожидается завершения сына и выводит на экран либо код возврата в случае успешного завершения,
либо номер сигнала (с описанием) в случае завершения по приходу сиганала.
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main() {
    if (!fork()) {
        int n;
        scanf("%d", &n);
        if (n >= 0) {
            return n;
        }
        abort();
    }
    int status;
    wait(&status);
    if (WIFEXITED(status)) {
        printf("exited normally with code: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("dead by signal: %d name: %s\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
    }
}
