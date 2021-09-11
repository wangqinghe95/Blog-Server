#include"myEpoll.hpp"
#include"logger.hpp"

#include<sys/socket.h>
#include<netinet/in.h>
#include<cstring>
#include<unistd.h>

Socket::Socket(/* args */)
{
    // listen_listen_fd = 0;
    err_code = 0;
}

Socket::~Socket()
{
    err_code = 0;
}

int Socket::CreateFd() {
    // create a listening listen_fd for socket
    int listen_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listen_listen_fd) {
        return SOCKET_CREATE_ERROR;
    }

    return listen_listen_fd; 
}

int Socket::BindListenFd(int listen_fd, int port) {

    // check the validity of port which from caller
    if (port < 1024 || port > 65535) {
        return PORT_INVALID;
    }

    // to solve problem that "address already in use"
    int opt_val = 1;
    if (-1 == setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, opt_val)) {
        return SOCKET_SETSOCKETOPTION_ERROR;
    }

    // bind server ip for listen_fd
    sockaddr_in server_addr;    // include<netinet/in.h>
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (-1 == bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
        return SOCKET_BIND_ERROR;
    }

    //listen listen_fd
    if(-1 == listen(listen_fd, LISTENNUM)) {
        return SOCKET_LISTEN_ERROR;
    }

    return listen_fd;
}

int Socket::socketCreate(int port) {
    int listen_fd = CreateFd();
    if (listen_fd < 0) {
        err_code = listen_fd;
        return err_code;
    }

    int iRet = BindListenFd(listen_fd, port);
    if (iRet < 0) {
        err_code = iRet;
        close(listen_fd);   // #include<unistd.h>
        return err_code;
    }

    return listen_fd;
}

int Epoll::createEpoll(int size) {
    int epoll_fd = epoll_create(size+1);
    if (-1 == epoll_fd) {
        return EPOLL_CREATE_ERROR;
    }

    return epoll_fd;
}