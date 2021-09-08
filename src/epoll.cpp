#include"epoll.hpp"

#include<sys/socket.h>
#include"logger.hpp"

Socket::Socket(/* args */)
{
    listen_fd = 0;
    err_code = 0;
}

Socket::~Socket()
{
}

void Socket::socketCreate() {

    // 读取配置文件的端口需要检测，如果失败应该输入logger
    // looger 文件后期补充
    if (PORT < 1024 || PORT > 65535) {
        err_code = port_invalid;
        LOG_BUG("The Port is invalid");
        return;
    }

    // 创建监听的socket套接字
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listen_fd) {
        err_code = socket_create_error;
        return;
    }

    // 绑定地址
    
}
