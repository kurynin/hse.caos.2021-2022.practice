/*
Процесс считывает с входного потока положительное число n.
Требуется запустить 2 сыновьих процесса (работающих параллельно):
* один сын должен рассчитать n-ое число Фибоначчи;
* другой сын должен распечать n!
Отец получает ответы от сыновей и выводит их на экран.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>


int main() {
    int tmp = open("first_ans", O_RDWR | O_CREAT | O_TRUNC, 0644);
    close(tmp);
    if (!fork()) {
        char answer[] = "1337\n";
        int fd = open("first_ans", O_RDWR | O_APPEND, 0644);
        write(fd, answer, sizeof(answer) - 1);
        close(fd);
        return 0;
    }
    if (!fork()) {
        usleep(50000);
        char answer[] = "755\n";
        int fd = open("first_ans", O_RDWR | O_APPEND, 0644);
        write(fd, answer, sizeof(answer) - 1);
        close(fd);
        return 0;
    }
    wait(NULL);
    wait(NULL);
    int fd = open("first_ans", O_RDONLY);
    char buf[20] = {};
    read(fd, buf, sizeof(buf));
    printf("%s", buf);
}
