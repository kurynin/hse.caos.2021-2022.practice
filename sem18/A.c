// ### A

// Процесс порождает двух сыновей. Они играют в пинг-понг через единственный pipe
// (считывают число из pipe, печатают свой порядковый номер и значение числа,
// инкрементируют это число и отправляют партнеру). Для синхронизации требуется
// использовать сигналы SIGUSR1. Для завершения партнера следует послать сигнал SIGINT.

// Для обработки сигналов использовать signalfd.



#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

void work(int number, int fd[], int maximum, pid_t br, sigset_t mask) {
    struct signalfd_siginfo fdsi;
    ssize_t s;

    int sfd = signalfd(-1, &mask, 0);
    if (sfd == -1) {
        handle_error("signalfd");
    }

    for (;;) {
        s = read(sfd, &fdsi, sizeof(fdsi));
        if (s != sizeof(fdsi)) {
            handle_error("read");
        }

        int buff;
        if (fdsi.ssi_signo == SIGUSR1) {
            read(fd[0], &buff, sizeof(buff));
            printf("%d %d\n", number, buff);
            if (buff == maximum) {
                kill(br, SIGINT);
                exit(0);
            }
            ++buff;
            write(fd[1], &buff, sizeof(buff));
            kill(br, SIGUSR1);
        } else if (fdsi.ssi_signo == SIGINT) {
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    int max = atoi(argv[1]);

    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
            handle_error("sigprocmask");
    }

    int fd[2];
    pipe(fd);

    int f = fork();
    if (!f) {
        int s;
        read(fd[0], &s, sizeof(s));
        work(1, fd, max, s, mask);
        _exit(1);
    }

    int s;
    if (!(s = fork())) {
        work(2, fd, max, f, mask);
        _exit(1);
    }

    write(fd[1], &s, sizeof(s));
    int number = 0;
    kill(f, SIGUSR1);
    write(fd[1], &number, sizeof(number));

    wait(NULL);
    wait(NULL);
}
