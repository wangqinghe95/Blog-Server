#ifndef MY_ERROR_HPP_
#define MY_ERROR_HPP_

enum SocketError {
    SOCKET_CREATE_ERROR = -1,
    SOCKET_PORT_INVALID = -2,
    SOCKET_SETSOCKETOPTION_ERROR = -3,
    SOCKET_BIND_ERROR = -4,
    SOCKET_LISTEN_ERROR = -5,
    SOCKET_ACCEPT_ERROR = -6,
    SOCKET_SEND_ERROR = -7
};

enum EpollError {
    EPOLL_CREATE_ERROR = -1,
    EPOLL_CTL_ADD_ERROR = -2,
    EPOLL_WAIT_ERROR = -3,
};

#endif