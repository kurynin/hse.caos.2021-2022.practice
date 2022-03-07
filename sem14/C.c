// ## C.c
// Программа в аргументах командной строки получает неотрицательное число
// (разрядность заранее не определена).
// Требуется вывести на экран значение квадрата этого числа.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int fd = open("my.py", O_WRONLY | O_TRUNC | O_CREAT, 0700); // обратить внимание на флаг x(!)
    FILE* f = fdopen(fd, "w");
    fprintf(f,
            "#! /bin/python3\n"
            "import os\n"
            "print(%s ** 2)\n"
            "os.remove('my.py')\n",
            argv[1]);
    fclose(f);
    int status = execl("my.py", "my.py", NULL);
    return status;
}
