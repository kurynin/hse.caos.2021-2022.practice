/*
### B

В аргументах командной строки передается port.
Требуется организовать работу сервиса, работающего по указанному порту.
К сервису может подключиться клиент, который отправляет текстовую строку
к серверу. Сервер печатает полученную строку в свой поток вывода и
отправляет клиенту сообщение "bye!".

Если клиент прислал сообщение "exit", сервер завершает свою работу.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int port = atoi(argv[1]);
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror(argv[0]);
        _exit(1);
    }
    int val = 1;
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(port);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));
    if (bind(fd, (void *) &sa, sizeof(sa)) < 0) {
        _exit(1);
    }
    if (listen(fd, 5) < 0) {
        _exit(1);
    }
    char buf[128];
    while(1) {
        struct sockaddr_in ss;
        socklen_t sz = sizeof(ss);
        int afd = accept(fd, (void *) &ss, &sz);
        if (afd < 0) {
            _exit(1);
        }
        int n_bytes = read(afd, buf, sizeof(buf));
        buf[n_bytes] = '\0';
        printf("%s\n", buf);
        write(afd, "bye!", 4);
        close(afd);
        if (!strcmp(buf, "exit")) {
            break;
        }
    }
    close(fd);
}
