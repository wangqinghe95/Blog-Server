#include"Task.hpp"

void Task::execTask(HttpRequest& requestData, HttpResponse& responseData)
{
    TaskType emTaskType = getTaskType(requestData.getURI());
    switch(emTaskType){
        case TaskType::USER_LOGIN:{

        }
        case TaskType::ADD_FILE:{

        }
        case TaskType::ADD_PNG:{

        }
        case TaskType::ADD_MP3:{

        }
        case TaskType::NOT_SUPPORT:{

        }
    }
}

void Task::toCheckLogin()
{
    
}

TaskType Task::getTaskType(std::string str)
{
    if(0 == str.compare("/user/login")){
        return TaskType::USER_LOGIN;
    }
    if(0 == str.compare("/add/file")){
        return TaskType::ADD_FILE;
    }
    if (0 == str.compare("/add/png")){
        return TaskType::ADD_PNG;
    }
    if (0 == str.compare("/add/MP3")) {
        return TaskType::ADD_MP3;
    }
    return TaskType::NOT_SUPPORT;
}