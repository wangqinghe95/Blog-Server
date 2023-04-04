#ifndef _LOGGER_HPP__
#define _LOGGER_HPP__

#define LOG_DEBUG(msg) Log.output(__FILE__, __LINE__,__FUNCTION__,msg);

#include<string>

class Logger
{
public:
    static Logger& getLogger()
    {
        static Logger instance;
        return instance;
    }
    void output(const std::string &file, const long line, const std::string& function,const std::string& msg);
private:
    Logger(){};
    Logger(const Logger& lg){};
    Logger& operator=(const Logger&lg){};

    void getTimeStamp(std::string& str_time);
};

#endif
