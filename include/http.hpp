#ifndef HTTP_HPP_
#define HTTP_HPP_

#include<string>
// #include"jsonpar.hpp"
// #include "serialization.h"
#include"jsonparser.h"
#include "logger.hpp"

class Request{
public:
    Request();
    /*
     * [desc] analyze the request from client
     * [in] message: a string will be analyzed which from client
    */
    int requestAnalyzeMessage(std::string& recv_data);

    /*
     * [desc] generate http header message and body that will be send to web
     * [out] send_data: data sending to clent be generated
    */    
    int requestGenerateHttp(std::string& send_data);

private:
    int getSendData(int code, std::string& send_data);
    int getBody(std::string& body);
    //int Request::getBody(std::string& body)

};

#endif