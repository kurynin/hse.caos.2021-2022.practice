#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

volatile int flag = 0; 

void func(int u) {
    flag = 1;
}

int main() {
    struct sigaction sa = {}; // инициализируем нулями
    sa.sa_flags = SA_RESTART; // restartable system calls
    sa.sa_handler = func;     // обработчик сигнала
    sigaction(SIGUSR1, &sa, NULL);
    int fd[2];
    pipe(fd);
    int pid1 = fork();
    int pid2;
    if (pid1) {
        pid2 = fork();
    }
    if (!pid1) {
        int pid2;
        read(fd[0], &pid2, sizeof(pid2));
        flag = 1; // либо выставляем этот флаг тут, либо отец посылает первому сыну сигнал (см. ниже)
        while(1) {
            if (flag == 1) {
                int num;
                read(fd[0], &num, sizeof(num));
                printf("1\t%d\n", num++);
                if (num == 8) {
                    kill(pid2, SIGINT);
                    exit(0);
                }
                write(fd[1], &num, sizeof(num));
                kill(pid2, SIGUSR1);
                flag = 0;
                pause();
            }
        }
    }
    if (!pid2) {
        while(1) {
            if (flag == 1) {
                int num;
                read(fd[0], &num, sizeof(num));
                printf("2\t%d\n", num++);
                if (num == 8) {
                    kill(pid1, SIGINT);
                    exit(0);
                }
                write(fd[1], &num, sizeof(num));
                kill(pid1, SIGUSR1);
                flag = 0;
                pause();
            }
        }
    }
    int zero = 0;
    write(fd[1], &pid2, sizeof(pid2));
    write(fd[1], &zero, sizeof(zero));
    //kill(pid1, SIGUSR1); // альтернатива выставлению флага в первом сыне
    wait(NULL);
    wait(NULL);
}
