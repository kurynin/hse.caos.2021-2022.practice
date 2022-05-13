#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/epoll.h>


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
    freeaddrinfo(result);

    int efd = epoll_create1(0);
    struct epoll_event eev = {};
    eev.events = EPOLLIN;
    eev.data.fd = 0;
    epoll_ctl(efd, EPOLL_CTL_ADD, 0, &eev);
    eev.data.fd = fd;
    epoll_ctl(efd, EPOLL_CTL_ADD, fd, &eev);

    while (1) {
        int count = epoll_pwait(
            efd,
            &eev,
            1,
            -1,
            NULL);
        if (count < 0) {
            return 1;
        }
        if (!count) {
            continue;
        }
        if (!eev.data.fd) {
            char buf[100];
            int s = read(0, buf, sizeof(buf));
            if (!s) {
                return 0;
            }
            write(fd, buf, s);
        }
        if (eev.data.fd == fd) {
            char buf[100];
            int s = read(fd, buf, sizeof(buf) - 1);
            if (!s) {
                return 0;
            }
            buf[s] = '\0';
            printf("%s\n", buf);
        }
    }
}
