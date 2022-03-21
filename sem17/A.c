/*
### A.c

Программе в аргументах командной строки передаются:
* целое число delta
* путь к каталогу

Следует найти в данном каталоге (без учета подкаталогов) все регулярные файлы,
которые были изменены не раньше, чем delta секунд назад (от текущего времени).
*/

#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

int main (int argc, char *argv[]) {
    int delta = atoi(argv[1]);

    DIR *directory = opendir(argv[2]);

    struct dirent *dir;

    time_t compare_time = time(NULL) - delta;
    while ((dir = readdir(directory))) {
        if (!strcmp(".", dir->d_name)|| !strcmp("..", dir->d_name)) {
            continue;
        }
        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", argv[2], dir->d_name);
        struct stat st;
        lstat(fullpath, &st);

        mode_t filemode = st.st_mode;


        if (S_ISREG(filemode) && (st.st_mtim.tv_sec > compare_time)) {
            printf("%s\n", fullpath);
        }
    }

    closedir(directory);
    return 0;
}
