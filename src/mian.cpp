#include<iostream>
#include"myEpoll.hpp"
#include"logger.hpp"
using namespace std;

const int PORT = 8800;  // 后期从配置文件中读取
const int EPOLLSIZE = 5000;

// get listen fd from socket class by call function of socket in linux
int getListenFd();

int main (){
    
    int listen_fd = getListenFd();
    if (listen_fd < 0) {
        return -1;
    }
    
    return 0;
}

int getListenFd() {
    Socket sock;
    
    int listen_fd = sock.socketCreate(PORT);
    if (listen_fd < 0) {
        switch (listen_fd)
        {
        case -1:
            LOG_BUG("Port 无效");break;
            break;
        case -2:
            LOG_BUG("socket 创建失败");break;
        case -3:
            LOG_BUG("setsockoption 设置失败");break;
        case -4:
            LOG_BUG("bind 绑定失败");break;
        case -5:
            LOG_BUG("listen 监听失败");break;
        default:
            break;
        }
    }

    return listen_fd;
}