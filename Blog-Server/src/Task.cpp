#include"Task.hpp"

enum Task::TaskType{
    USER_LOGIN,
    ADD_FILE,
    ADD_PNG,
    ADD_MP3,
    NOT_SUPPORT
};

void Task::execTask(HttpRequest& requestData, HttpResponse& responseData)
{
    TaskType emTaskType = getTaskType(requestData.getURI);
    switch(emTaskType){
        case Task::USER_LOGIN:{

        }
        case Task::ADD_FILE:{

        }
        case Task::ADD_PNG:{

        }
        case Task::ADD_MP3:{

        }
        case Task::NOT_SUPPORT:{

        }
    }
}

void Task::toCheckLogin()
{
    
}

TaskType Task::getTaskType(std::string &str)
{
    if(0 == str.compare("/user/login")){
        return Task::USER_LOGIN;
    }
    if(0 == str.compare("/add/file")){
        return Task::ADD_FILE;
    }
    if (0 == str.compare("/add/png")){
        return Task::ADD_PNG;
    }
    if (0 == str.compare("/add/MP3")) {
        return Task::ADD_MP3;
    }
    return Task::NOT_SUPPORT;
}