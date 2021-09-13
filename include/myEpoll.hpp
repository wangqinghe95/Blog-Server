#ifndef EPOLL_HPP_
#define EPOLL_HPP_

const int LISTENNUM = 1024;

#include"myError.hpp"
#include<sys/epoll.h>
#include<unistd.h>
// #include<sys/socket.h>
#include<netinet/in.h>
// #include<unordered_map>

class Socket
{
public:
    Socket(/* args */);
    ~Socket();

    // delete later
    int socketCreate(int port);
    // create a socket for listening
    int createSocketFd();
    // bind serverIp
    int bindListenSocketFd(int fd, int port);
    // accept request from client
    int acceptSocketFd(int listen_fd);
    int recvSocketFd(int fd);

    // get client info by index(clinet_fd)
    // const sockaddr_in* getSockaddrByIndex(int index);
    const void printClientInfo(int index) const;
private:
    // int listen_fd;  // fd for listening
    int err_code;   // conserve what kind of error occur
    // std::unordered_map<int, sockaddr_in> client_address;

    // conserve content of client requesting, ip, port and so on
    // sockaddr_in* client_addr;
    sockaddr_in* client_addr;
};

class Epoll {
public:
    Epoll();
    ~Epoll();

    // int epollInit(epoll_event& my_epoll_event);
    int epollCreate(int size);
    int epollAdd(int epoll_fd, int listen_fd);
    int epollWait(int epoll_fd, epoll_event* event, int epoll_size);
};

#endif