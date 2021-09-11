#ifndef EPOLL_HPP_
#define EPOLL_HPP_

const int LISTENNUM = 1024;

#include"myError.hpp"

class Socket
{
private:
    // int listen_fd;  // fd for listening
    int err_code;   // conserve what kind of error occur
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
};

class Epoll {
public:
    int createEpoll(int size);
};

#endif