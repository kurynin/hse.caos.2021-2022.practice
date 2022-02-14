/*
Программа должна посчитать количество пробельных символов в текстовом файле (имена задаются во входном потоке).
Системным вызовом read() пользоваться запрещено.
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

int main() {
    char buf[PATH_MAX];

    while (fgets(buf, sizeof(buf), stdin)) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0';
        }

        printf("%s\n", buf);

        int fd = open(buf, O_RDONLY);

        if (fd < 0) { // check
            perror(NULL);
            continue;
        }

        struct stat st;
        int res = fstat(fd, &st); // check

        const char *p = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);

        if (p == MAP_FAILED) {
            perror(NULL);
            close(fd);
            continue;
        }

        size_t spaces = 0;

        for (size_t i = 0; i < st.st_size; i++) {
            if (isspace(p[i])) {
                spaces++;
            }
        }

        printf("%lu\n", spaces);
        munmap((void *)p, st.st_size);
        close(fd);
    }


    return 0;
}
