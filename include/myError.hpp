#ifndef MY_ERROR_HPP_
#define MY_ERROR_HPP_

enum SocketError {
    PORT_INVALID = -1,
    SOCKET_CREATE_ERROR = -2,
    SOCKET_SETSOCKETOPTION_ERROR = -3,
    SOCKET_BIND_ERROR = -4,
    SOCKET_LISTEN_ERROR = -5,
};

enum EpollError {
    EPOLL_CREATE_ERROR = -1,
    EPOLL_CTL_ADD_ERROR = -2,
};

#endif