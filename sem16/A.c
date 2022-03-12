/*
 * # A.c

Программа должна выполнить команду

CMD1 | CMD2

где CMD1, CMD2 - параметры командной строки.
Если CMD1 завершается из-за попытки записи в канал, из которого
никто не читает, следует вывести строку в поток ошибок:
Broken pipe.

 */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char** argv) {
    if (argc < 3) {
        return 1;
    }
    int fd[2];
    // read, write
    pipe(fd);
    int one = fork();
    if (!one) {
        // CMD1
        dup2(fd[1], STDOUT_FILENO); // write to stdout 1
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        return 0;
    }
    int two = fork();
    if (!two) {
        // CMD2
        dup2(fd[0], STDIN_FILENO); // read from stdin 0
        close(fd[1]);
        close(fd[0]);
        execlp(argv[2], argv[2], NULL);
        return 0;
    }
    close(fd[0]);
    close(fd[1]);
    int status_one, status_two;
    waitpid(one, &status_one, 0);
    waitpid(two, &status_two, 0); // wait(NULL)
    if (WIFSIGNALED(status_one) && WTERMSIG(status_one) == SIGPIPE) {
        fprintf(stderr, "Broken pipe\n");
    }

    return 0;
}
