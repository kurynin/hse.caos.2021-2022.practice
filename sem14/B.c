// ## B
// Программе в аргументах командной строки передается набор файлов
// (если список пустой, то идет работа с входным потоком).
// Для каждого отдельного файла следует выполнить команду:
// wc < FILE >>stats.out
// Если файл stats.out не существует, его следует создать с правами 0664.

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void process(char* arg) {
    if (!fork()) {
        // >> => > : O_APPEND => O_TRUNC
        int fd = open("stats.out", O_WRONLY | O_APPEND | O_CREAT, 0664);
        if (arg) {
            int fd_main = open(arg, O_RDONLY);
            dup2(fd_main, 0);
            close(fd_main);
        }
        dup2(fd, 1);
        close(fd);
        execlp("wc", "wc", NULL);
        exit(1);
    }
}


int main(int argc, char** argv) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            process(argv[i]);
            wait(NULL); // для синхронного (последовательного) запуска
        }
        // если трибуется параллельно, то:
        //while (wait(NULL) != -1) {
        //}
    } else {
        process(NULL);
        wait(NULL);
    }

}
