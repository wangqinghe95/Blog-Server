#ifndef EPOLL_HPP_
#define EPOLL_HPP_

const int LISTENNUM = 1024;

#include"myError.hpp"
#include<sys/epoll.h>

class Socket
{
public:
    Socket(/* args */);
    // 
    int socketCreate(int port);
    ~Socket();

private:
    // create a socket for listening
    int CreateFd();
    // bind serverIp
    int BindListenFd(int fd, int port);

    // int listen_fd;  // fd for listening
    int err_code;   // conserve what kind of error occur
};

class Epoll {
public:
    // to do
    Epoll();

    epoll_event *my_epoll_event;

    int createEpoll(int size);
};

#endif