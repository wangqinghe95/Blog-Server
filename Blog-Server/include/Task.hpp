#ifndef _TASK_HPP__
#define _TASK_HPP__

#include"HttpRequest.hpp"
#include"HttpResponse.hpp"
#include"jsonvalue.h"

class Task
{
private:
    TaskType getTaskType(std::string &str);
public:
    Task(/* args */);
    ~Task();

    void execTask(HttpRequest& requestData, HttpResponse& responseData);
    
    static enum TaskType;
private:
    void toCheckLogin();
};

#endif