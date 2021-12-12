/*
Написать программу на Си.
Программа должна считать со входного потока текст и распечатать распечатать его строки в обратном порядке.
Для чтения/записи использовать системный вызовы read/write.
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    BUF_SIZE = 1 << 12,
};

void print(char *mem, unsigned size) {
    if (size == 0) {
        return;
    }
    int count = 0;
    for (int i = size - 1; i != -1; --i) {
        if (mem[i] == '\n') {
            int res;
            while ((res = write(STDOUT_FILENO, mem + i + 1, count)) > 0) {
                count -= res;
            }
            if (res < 0) {
                return;
            }
            ++count;
        } else {
            ++count;
        }
    }
    int res;
    while ((res = write(STDOUT_FILENO, mem, count)) > 0) {
        count -= res;
    }
}

int main() {
    char buf[BUF_SIZE];
    int count;
    char *mem = NULL;
    unsigned size = 0;
    unsigned capacity = 0;
    int flag = 0;
    while (!flag) {
        count = read(STDIN_FILENO, buf, BUF_SIZE);
        if (count < 0) {
            break;
        }
        if (count == 0) {
            if (size == 0 || mem[size - 1] == '\n') {
                break;
            }
            buf[0] = '\n';
            count = 1;
            flag = 1;
        }
        if (size + count > capacity) {
            char *tmp = realloc(mem, capacity + BUF_SIZE);
            if (!tmp) {
                break;
            }
            mem = tmp;
            capacity = capacity + BUF_SIZE;
        }
        memcpy(mem + size, buf, count);
        size += count;
    }

    print(mem, size);
    free(mem);
}
