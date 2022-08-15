#ifndef EPOLL_HPP_
#define EPOLL_HPP_

const int LISTENNUM = 1024;

#include"myError.hpp"
#include<sys/epoll.h>
#include<unistd.h>
// #include<sys/socket.h>
#include<netinet/in.h>
#include<string>
// #include<unordered_map>

class Socket
{
public:
    Socket(/* args */);
    ~Socket();

    // create a socket for listening
    int createSocketFd();
    // bind serverIp
    int bindListenSocketFd(int fd, int port);
    // accept request from client
    int acceptSocketFd(int listen_fd);

    // get data from client
    int recvSocketFd(int fd, std::string &message);

    int sendSocketFd(int fd, std::string& send_message);

    // get client info by index(clinet_fd)
    void printClientInfo(int index) const;
    
private:

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