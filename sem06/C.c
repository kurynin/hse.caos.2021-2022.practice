/*
В аргументах командной строки задаются 3 параметра: `file`, `offset`, `length`.
Написать программу, которая напечатает на экран `length` байт из файла с именем `file`,
начиная с позиции `offset`.
*/

#include <stdio.h>
#include <stdlib.h>

enum {
    N = 16,
};


int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "r");
    long offset;
    sscanf(argv[2], "%ld", &offset);
    long length;
    sscanf(argv[3], "%ld", &length);
    char string[N + 1];
    if (fseek(file,  offset, SEEK_SET) == 0) {
        while (length > 0) {
            int n = (length > N) ? N : length;
            int u = fread(string, 1, n, file);
            string[u] = '\0';
            printf("%s", string);
            if (u != n) {
                if (!feof(file)) {
                    fprintf(stderr, "error/n");
                }
                printf("\n");
                exit(0);
            }
            length -= n;
        }
    }
    printf("\n");
    fclose(file);
}