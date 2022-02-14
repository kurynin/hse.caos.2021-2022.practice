/*
Программа принимает в аргументах командной строки 2 параметра:
    file1 file2
Требуется скопировать содержимое из file1 в file2 в обратном порядке байт.
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0660);
    struct stat st;
    fstat(fd1, &st);
    char *f1 = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd1, 0);
    if (f1 == MAP_FAILED) {
        fprintf(stderr, "f1:\t%s\n", strerror(errno));
        perror(NULL);
        return(1);
    }
    ftruncate(fd2, st.st_size);
    char *f2 = mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, fd2, 0);
    if (f2 == MAP_FAILED) {
        fprintf(stderr, "f2:\t%s\n", strerror(errno));
        perror(NULL);
        return(1);
    }
    for (size_t i = 0; i < st.st_size; ++i) {
        f2[st.st_size - 1 - i] = f1[i];
    }
    munmap(f1, st.st_size);
    munmap(f2, st.st_size);
    close(fd1);
    close(fd2);
}
