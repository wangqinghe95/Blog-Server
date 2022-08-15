#include<iostream>
#include"myEpoll.hpp"
#include"logger.hpp"
#include"http.hpp"
using namespace std;

const int PORT = 8800;  // 后期从配置文件中读取
const int EPOLLSIZE = 5000;

Logger& Log = Logger::getInstance();

// get listen fd from socket class by call function of socket in linux
int getListenFd(Socket &sock);

int main (){
   Socket sock; 

    int listen_fd = getListenFd(sock);
    if (listen_fd < 0) {
        return -1;
    }

    // create epoll event in kernel
    Epoll myEpoll;
    epoll_event *my_epoll_event = new epoll_event[EPOLLSIZE];

    int epoll_fd = myEpoll.epollCreate(EPOLLSIZE);
    if (epoll_fd == -1) {
        LOG_DEBUG("Create Epoll error");
        exit(1);
    }

    //add event to kernel
    if (EPOLL_CTL_ADD_ERROR == myEpoll.epollAdd(epoll_fd, listen_fd)) {
        LOG_DEBUG("Add Epoll error")
        exit(0);
    }

    Request httpRequest;
    while (1) {
        int event_num = myEpoll.epollWait(epoll_fd, my_epoll_event, EPOLLSIZE);
        if (event_num < 0) {
            LOG_DEBUG("wait Epoll error");
            break;
        }

        for (int i = 0; i < event_num; ++i) {
            int sockfd = my_epoll_event[i].data.fd;
            
            // request from new user to connect
            if (sockfd == listen_fd) {
                int clien_fd = sock.acceptSocketFd(listen_fd);
                myEpoll.epollAdd(epoll_fd, clien_fd);
            }
            else {
                string message;
                int len = sock.recvSocketFd(sockfd, message);
                sock.printClientInfo(sockfd);
                if (len > 0) {
                    // LOG_DEBUG(message);
                    string send_data;
                    httpRequest.requestGenerateHttp(send_data);
                    // request to slove message from client
                    if (SOCKET_SEND_ERROR == sock.sendSocketFd(sockfd, send_data)) {
                        string error = "send data to " + to_string(sockfd) + "error";
                        // LOG_DEBUG(error)
                    }
                    else {
                        string success = "send data to " + to_string(sockfd) + " success : \r\n" + send_data;
                        // LOG_DEBUG(success);
                    }
                }
            }
        }
    }
    return 0;
}

int getListenFd(Socket &sock) {
    
    // int listen_fd = sock.socketCreate(PORT);
    int listen_fd = sock.createSocketFd();
    if (listen_fd < 0) {
        if (listen_fd == SOCKET_CREATE_ERROR)
        {
            LOG_DEBUG("socket 创建失败");
        }
        else {
            LOG_DEBUG("createSocketFd unknow error")
        }
        return listen_fd;
    }

    int iRet = sock.bindListenSocketFd(listen_fd, PORT);
    if (iRet < 0) {
        switch (iRet)
        {
        case -2:
            LOG_DEBUG("Port 无效");break;
            break;
        case -3:
            LOG_DEBUG("setsockoption 设置失败");break;
        case -4:
            LOG_DEBUG("bind 绑定失败");break;
        case -5:
            LOG_DEBUG("listen 监听失败");break;
        default:
            break;
        }

        close(listen_fd);   // #include<unistd.h>
        return iRet;
    }
    else {
        const string mess = "starting listen PORT:" + to_string(PORT);
        LOG_DEBUG(mess);
    }

    return listen_fd;
}