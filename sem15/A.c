/*
## A.c
Программа принимает на вход 2 аргумента командной строки:
./a.out CMD1 CMD2
Программа должна выполнить следующую команду shell:
CMD1 | CMD2
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }

    int fds[2];

    if (pipe(fds) < 0) {
        return 1;
    }

    if (!fork()) {

        dup2(fds[1], 1);

        close(fds[0]);
        close(fds[1]);

        execlp(argv[1], argv[1], NULL);
        return 1;
    }

    close(fds[1]);

    if (!fork()) {

        dup2(fds[0], 0);

        close(fds[0]);

        execlp(argv[2], argv[2], NULL);
        return 1;
    }

    close(fds[0]);  // ВАЖНО(!) закрыть в отце все файловые дескрипторы, связанные с pipe, до wait(),
                    // иначе будут deadlocks
    wait(NULL);
    wait(NULL);
    return 0;

}