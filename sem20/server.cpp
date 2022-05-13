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
#include <unistd.h>
#include <sys/epoll.h>
#include <unordered_set>
#include <vector>
#include <iostream>

#define MAX_EVENTS 10


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
    if (bind(fd, (const sockaddr*)&sa, sizeof(sa)) < 0) {
        _exit(1);
    }
    if (listen(fd, 5) < 0) {
        _exit(1);
    }
    signal(SIGPIPE, SIG_IGN);

    int efd = epoll_create1(0);
    struct epoll_event eev = {};
    struct epoll_event events[MAX_EVENTS];


    eev.events = EPOLLIN;
    eev.data.fd = fd;
    if (epoll_ctl(efd, EPOLL_CTL_ADD, fd, &eev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    std::unordered_set<int> fds;
    while(1) {
        struct sockaddr_in ss;
        socklen_t sz = sizeof(ss);
        int nfds = epoll_wait(efd, events, MAX_EVENTS, -1);
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == fd) {
                int conn_sock = accept(fd, (sockaddr *) &ss, &sz);
                if (conn_sock == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                // setnonblocking(conn_sock);
                eev.events = EPOLLIN;
                eev.data.fd = conn_sock;
                if (epoll_ctl(efd, EPOLL_CTL_ADD, conn_sock,
                            &eev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
                std::cout << "Connected " << conn_sock << std::endl;
                fds.insert(conn_sock);
            } else {
                int cur_fd = events[i].data.fd;
                char buf[100];
                int s = read(cur_fd, buf, sizeof(buf) - 1);
                if (!s) {
                    if (epoll_ctl(efd, EPOLL_CTL_DEL, cur_fd, NULL) == -1) {
                        perror("epoll_ctl: conn_sock");
                        exit(EXIT_FAILURE);
                    }
                    std::cout << "Removed " << cur_fd << std::endl;
                    fds.erase(cur_fd);
                    close(cur_fd);
                    continue;
                }
                // std::vector<int> to_remove;
                for (auto& el : fds) {
                    if (el != cur_fd) {
                        int sw = write(el, buf, s);
                        std::cout << "Send message to " << el << "." << "Send " << sw << " bytes" << std::endl;
                    }
                }
            }
        }
     }
    close(fd);
}
