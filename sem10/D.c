/* Программа должна напечатать
содержимое входного потока:
cat // 0 - input
    // 1 - output

Программа будет собираться без подключения стандартной библиотеки.

*/

#include <asm/unistd_32.h>

int read(int fd, void *buf, int count) {
    int ans;
    asm volatile (
        "mov $3, %%eax\n"
        "mov %1, %%ebx\n"
        "mov %2, %%ecx\n"
        "mov %3, %%edx\n"
        "int $0x80\n"
        "mov %%eax, %0\n"
        : "=g"(ans)
        : "g"(fd), "g"(buf), "g"(count)
        : "eax", "ebx", "ecx", "edx", "memory"
        );
    return ans;
}

int write(int fd, const void *buf, int count) {
    int ans;
    asm volatile (
        "mov $4, %%eax\n"
        "mov %1, %%ebx\n"
        "mov %2, %%ecx\n"
        "mov %3, %%edx\n"
        "int $0x80\n"
        "mov %%eax, %0\n"
        : "=g"(ans)
        : "g"(fd), "g"(buf), "g"(count)
        : "eax", "ebx", "ecx", "edx"
        );
    return ans;
}

void _start() {
    char buf[100];
    int cnt;
    while ((cnt = read(0, &buf, sizeof(buf))) > 0) {
        write(1, &buf, cnt);
    }

    asm (
        "mov $0, %%ebx\n"
        "mov $1, %%eax\n"
        "int $0x80\n"
        :
        :
        : "eax", "ebx"
    );
}
