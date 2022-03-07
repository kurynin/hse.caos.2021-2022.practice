// ## A
// Написать программу, принимающую на вход два пути к файлам.
// ./a.out FILE1 FILE2
// Такой вызов должен быть эквивалентен следующей команде shell:
// diff -y FILE1 FILE2 && echo "Equal"

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (!fork()) {
        execlp("diff", "diff", "-y", argv[1], argv[2], NULL);
        return 1; // если exec() не сработал, то сын должен завершиться (с ошибкой)
    }
    int status;
    wait(&status);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        execlp("echo", "echo", "Equal", NULL);
    }
    return WEXITSTATUS(status);
}
