// ## B.c
// Программа принимает на вход 6 аргументов командной строки:
// ./a.out CMD1 CMD2 CMD3 CMD4 FILE1 FILE2
// Программа должна выполнить следующую команду shell:
// CMD1 < FILE1 | (CMD2; CMD3) | CMD4 >> FILE2

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    if (argc != 7) {
        return 1;
    }
    int fd1[2], fd2[2];
    pipe(fd1);
    if (!fork()) {
        // cmd1

        int fd_file_1 = open(argv[5], O_RDONLY);
        dup2(fd_file_1, 0);
        dup2(fd1[1], 1);
        close(fd1[0]);
        close(fd1[1]);
        close(fd_file_1);
        execlp(argv[1], argv[1], NULL);
        return 1;
    }
    pipe(fd2);
    close(fd1[1]);
    if (!fork()) {
        // cmd2 and cmd3
        dup2(fd1[0], 0);
        dup2(fd2[1], 1);
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);
        if (!fork()) {
            execlp(argv[2], argv[2], NULL);
            return 1;
        }
        wait(NULL); // Реализуем последовательный запуск cmd2; cmd3
        if (!fork()) {
            execlp(argv[3], argv[3], NULL);
            return 1;
        }
        wait(NULL);
        return 0; // Можно возвращать статус cmd3
    }
    close(fd1[0]);
    close(fd2[1]);
    if (!fork()) {
        // cmd4
        int fd_file_2 = open(argv[6], O_WRONLY | O_APPEND | O_CREAT, 0664);
        dup2(fd2[0], 0);
        dup2(fd_file_2, 1);
        close(fd2[0]);
        close(fd_file_2);
        execlp(argv[4], argv[4], NULL);
        return 1;
    }
    close(fd2[0]);
    wait(NULL);
    wait(NULL);
    wait(NULL);
}
