#ifndef _LOGGER_HPP__
#define _LOGGER_HPP__

enum LogLevel{
    TRACE = 0,
    INFO,
    WARN,
    DEBUG,
    ERROR,
    FATAL,
};

// #define LOG_DEBUG(msg) Log.output(__FILE__, __LINE__,__FUNCTION__,msg);

#define jlog(level, format, ...)    \
    do {                            \
        Logger& Log = Logger::getInstance(); \
        Log.output(__FILE__, __LINE__,__FUNCTION__,format);    \
    }while(0);                      \

#define LOG_TRACE(format, ...) jlog(LogLevel::TRACE, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) jlog(LogLevel::INFO, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) jlog(LogLevel::WARN, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) jlog(LogLevel::DEBUG, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) jlog(LogLevel::ERROR, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) jlog(LogLevel::FATAL, format, ##__VA_ARGS__)

#include<string>

class Logger
{
public:
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }
    // void output(const std::string* strLogName, LogLevel level
    //             , const char* format ,const std::string &file
    //             , const long line, const std::string& function
    //             , const ARGS &...args);
    void output(const std::string &file, long line ,const std::string& func, const std::string& msg );
private:
    Logger(){};
    Logger(const Logger& lg){};
    Logger& operator=(const Logger&lg){
        return getInstance();
    };

    void getTimeStamp(std::string& str_time);
};

#endif
