/*
В аргументах командной строки передается путь к каталогу.
Распечать список файлов (путями относительно заданного параметра), вложенных в данный каталог.
*/

#include <dirent.h>
#include <stdio.h>
#include <limits.h>

int main (int argc, char** argv) {
    char *path = argv[1];

    DIR *dir = opendir(path);
    if (!dir) {
        return 1;
    }

    char fullpath[PATH_MAX];

    struct dirent *curdir;
    while ((curdir = readdir(dir))) {
        snprintf(fullpath, PATH_MAX, "%s/%s", path, curdir->d_name);
        printf("%s\n", fullpath);
    }

    closedir(dir);

    return 0;
}
