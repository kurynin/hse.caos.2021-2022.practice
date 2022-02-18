/*
Процесс печатает свой PID и PPID, затем запускает дочерний процесс,
который также печатает свой PID и PPID. После этой печати отцовский процесс
должен напечатать Good-bye и завершиться.
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    printf("father pid - %d, ppid - %d\n", getpid(), getppid());
    if (!fork()) {
        // child
        sleep(1);
        printf("child pid - %d, ppid - %d\n", getpid(), getppid());
        return 0;
    }
    wait(NULL);
    printf("goodbye\n");
    return 0;
}
