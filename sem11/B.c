/*
В аргументах командной строки передается путь к файлу.
Определить, является ли данный файл регулярным/каталогом/символической связью (на регулярный файл/каталог/прочее)/прочее.
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void print_info(mode_t st_mode) {
    if (S_ISREG(st_mode)) {
        printf("Регулярный файл\n");
    } else if (S_ISDIR(st_mode)) {
        printf("Директория\n");
    } else {
        printf("Прочее\n");
    }
}

void print_error() {
    printf("нет прав\n");
    exit(0);
}

int main(int argc, char** argv) {
    char* file_name = argv[1];
    struct stat s;
    if (lstat(file_name, &s) < 0) {
        print_error();
    }
    if (S_ISLNK(s.st_mode)) {
        printf("Символическая ссылка на: ");
        if(stat(file_name, &s) < 0) {
            print_error();
        }
        print_info(s.st_mode);
    } else {
        print_info(s.st_mode);
    }

    return 0;
}
