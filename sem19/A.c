#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/*
### A

В аргументах командной строки передаются address и port.
Требуется подключиться к указанному сервису и организовать
текстовое общение пользователя с ним (по аналогии с nc address port):
пользователь вводит строки,
эта строка передается серверу, сервер присылает ответ,
который надо распечатать на экран, и т.д.

*/

void sgnl(int code) {
    fprintf(stderr, "SIGPIPE!!!\n");
    _exit(1);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        return 1;
    }
    signal(SIGPIPE, sgnl); // когда прилетает сигнал SIGPIPE из-за разрыва соединения

    char* address = argv[1];
    char* port = argv[2];

    struct addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_STREAM};
    struct addrinfo* result = NULL;
    int err = getaddrinfo(address, port, &hints, &result); // получаем ip address

    if (err) {
        fprintf(stderr, "error: %s\n", gai_strerror(err));
        return 1;
    }
    if (!result) {
        perror("getaddrinfo error\n");
        return 1;
    }
    int fd = socket(result->ai_family, result->ai_socktype, 0); // создание сокета для общения

    if (fd == -1) {
        fprintf(stderr, "Socket error\n");
        freeaddrinfo(result);
        return 1;
    }
    // Чтобы программу, открывающую сокет в режиме прослушивания,
    // можно было запустить немедленно после завершения с тем же самым номером прослушивающего порта,
    // в программу должна быть добавлена следующая последовательность вызовов,
    // настраивающих опции сокета:
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    // соединение
    if (connect(fd, result->ai_addr, result->ai_addrlen) == -1) {
        fprintf(stderr, "Connect error\n");
        freeaddrinfo(result);
        return 1;
    }

    FILE* in = fdopen(dup(fd), "r");
    FILE* out = fdopen(fd, "w");
    char* line = NULL;
    char* ans = NULL;
    // Требуется подключиться к указанному сервису и организовать
    // текстовое общение пользователя с ним (по аналогии с nc address port):
    // пользователь вводит строки,
    // эта строка передается серверу, сервер присылает ответ, который надо распечатать на экран, и т.д.
    while (scanf("%ms", &line) != -1) {
        fprintf(out, "%s\n", line);
        fflush(out);
        if (fscanf(in, "%ms", &ans) != -1) {
            printf("%s\n", ans);
        }
        free(line);
    }

    fclose(in);
    fclose(out);
    freeaddrinfo(result);
}
