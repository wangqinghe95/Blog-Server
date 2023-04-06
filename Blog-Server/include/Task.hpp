#ifndef _TASK_HPP__
#define _TASK_HPP__

#include"HttpRequest.hpp"
#include"HttpResponse.hpp"
#include"jsonvalue.h"

enum TaskType{
    USER_LOGIN,
    ADD_FILE,
    ADD_PNG,
    ADD_MP3,
    NOT_SUPPORT
};

class Task
{
private:
    TaskType getTaskType(std::string str);
public:
    Task(/* args */);
    ~Task();

    void execTask(HttpRequest& requestData, HttpResponse& responseData);
    
private:
    void toCheckLogin();
};

#endif