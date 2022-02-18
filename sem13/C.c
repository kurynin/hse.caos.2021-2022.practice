/*
Процесс считывает с входного потока положительное число n.
Требуется запустить 2 сыновьих процесса (работающих параллельно):
* один сын должен рассчитать n-ое число Фибоначчи;
* другой сын должен распечать n!
Отец получает ответы от сыновей и выводит их на экран.
*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main() {
    int *ptr = mmap(NULL, sizeof(int) * 2,
                    PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);
    *ptr = 142;
    if (!fork()) { // fibonacci
        printf("first %d\n", ptr[0]);
        int answer = 133; // simulation
        *ptr = answer;
        printf("first %d\n", ptr[0]);
        return 0;
    }
    if (!fork()) {
        usleep(500000);
        ptr[1] = 148; // n! - simulation
        printf("second son\n");
        return 0;
    }
    wait(NULL);
    wait(NULL);
    printf("first son result:\t%d\nsecond son result:\t%d\n", ptr[0], ptr[1]);
    munmap(ptr, sizeof(int) * 2);
}
