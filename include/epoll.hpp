#ifndef EPOLL_HPP_
#define EPOLL_HPP_

const int PORT = 8800;  // 后期从配置文件中读取

enum CodeError {
    port_invalid = -1,
    socket_create_error = -2,
};

class Socket
{
private:
    int listen_fd;  // fd for listening
    int err_code;   // conserve what kind of error occur
public:
    Socket(/* args */);
    void socketCreate();
    int getSocket();
    ~Socket();
};




#endif