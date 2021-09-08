#include<iostream>
#include"epoll.hpp"
#include"logger.hpp"
using namespace std;

int main (){
    Socket sock;
    sock.socketCreate();

    LOG_BUG("测试log");

    return 0;
}