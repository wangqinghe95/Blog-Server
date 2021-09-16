#include"myEpoll.hpp"
#include"logger.hpp"

#include<netinet/in.h>
#include<cstring>
#include<string>
// #include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;

Socket::Socket(/* args */)
{
    // 1024 is the max number of default file description in keneral 
    // if that number is modified by mannual, please update this number at that time
    client_addr = new sockaddr_in[1024];
}

Socket::~Socket()
{
    if (client_addr != nullptr) {
        delete client_addr;
    }
}

int Socket::createSocketFd() {
    // create a listening listen_fd for socket
    int listen_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listen_listen_fd) {
        return SOCKET_CREATE_ERROR;
    }

    return listen_listen_fd; 
}

int Socket::bindListenSocketFd(int listen_fd, int port) {

    // check the validity of port which from caller
    if (port < 1024 || port > 65535) {
        return SOCKET_PORT_INVALID;
    }

    // to solve problem that "address already in use"
    int opt_val = 1;
    if (-1 == setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(int))) {
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

int Socket::acceptSocketFd(int listen_fd) {
    socklen_t sockaddr_len = sizeof(sockaddr_in);
    sockaddr_in request_add;
    int client_fd = accept(listen_fd, (sockaddr*)&request_add, &sockaddr_len);

    if (client_fd < 0) {
        return SOCKET_ACCEPT_ERROR;
    }

    client_addr[client_fd] = request_add;

    return client_fd;
}

int Socket::recvSocketFd(int fd, string &message) {
    char buf[BUFSIZ] = {0};
    int len = recv(fd, buf, BUFSIZ, 0);
    if (0 == len) {
        close(fd);
        bzero(&client_addr[fd], sizeof(sockaddr_in));
    }
    else {
        message = buf;
    }
    return len;
}

void Socket::printClientInfo(int index) const {
    sockaddr_in print_info = client_addr[index];
    const string client_IP = inet_ntoa(print_info.sin_addr);
    const string client_Port = to_string(ntohs(print_info.sin_port));
    const string client_Fd = to_string(index);
    const string str_info = "client connection from : " + client_IP + 
        +" : " + client_Port + "(IP:PORT) client_fd = " + client_Fd + "\n";
    LOG_BUG(str_info);
}

int Socket::sendSocketFd(int fd, std::string& send_message) {
    int ret = send(fd, send_message.c_str(), 4096, 0);
    if (ret < 0) {
        return SOCKET_SEND_ERROR;
    }
    return ret;
}

// const sockaddr_in* Socket::getSockaddrByIndex(int index) {
//     return &client_addr[index];
// }


Epoll::Epoll(){

}

Epoll::~Epoll() {
}

// int Epoll::epollInit(epoll_event& my_epoll_event, int size) {
//     my_epoll_event = new epoll_event[size];
//     if 
// }

int Epoll::epollCreate(int size) {
    int epoll_fd = epoll_create(size+1);
    if (-1 == epoll_fd) {
        return EPOLL_CREATE_ERROR;
    }

    // my_epoll_event = new epoll_event[size+1];

    return epoll_fd;
}

int Epoll::epollAdd(int epoll_fd, int listen_fd) {
    epoll_event ev;
    ev.data.fd = listen_fd;

    /*
        EPOLLET:edge triggered,kernel can only noticed user one time
        if a file descripition is prepared
        Level triggered:kernel will always notice user when a file description is prepared
        and user aren't to operator this file description. this mode is the defalut
    */
    ev.events = EPOLLIN | EPOLLET;

    if (-1 == epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev)) {
        return EPOLL_CTL_ADD_ERROR;
    }

    // set listen_fd as nonblocking
    fcntl(listen_fd, F_SETFL, fcntl(listen_fd, F_GETFD, 0) | O_NONBLOCK);

    return 0;
}

int Epoll::epollWait(int epoll_fd, epoll_event* event, int epoll_size) {
    
    int event_count = epoll_wait(epoll_fd, event, epoll_size, -1);
    if (event_count < 0) {
        return EPOLL_WAIT_ERROR;
    }

    return event_count;
}