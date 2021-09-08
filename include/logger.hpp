#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include<string>
#include<iostream>
using namespace std;
/*
    如何去将C风格的日志输出函数封装成类形式
*/

// #define LOG_DEBUG(msg) cout << "(" << __FILE__ << ":" << __LINE__ << ")" << endl;
// [2021-9-8 12：13：32] [hello.cpp:225] [CRITICAL] 
// #define LOG_DEBUG(msg) cout << "[" << __FILE__ << ":" << __LINE__  << "]" << endl;

#define LOG_BUG(msg) cout << "[" << __FILE__ << ":" << __LINE__  << "]" << msg << endl; 

enum log_level {
    INFO,
    DEBUG,
    WARNING,
    ERROR,  
    CRITICAL,
};

class Logger
{
private:
    /* data */
public:
    Logger(/* args */);
    void logger_debug(string& msg, int level);
    ~Logger();
};

#endif