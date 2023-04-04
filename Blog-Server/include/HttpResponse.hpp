#ifndef _HTTPRESPONSE_HPP_
#define _HTTPRESPONSE_HPP_

#include "HttpBase.hpp"
#include <unordered_map>

class HttpResponse : public HttpBase
{
private:
    int m_nStatusCode;
    std::string m_strStatusWord;

    const static std::unordered_map<std::string, std::string> m_fileContentType;
public:
    HttpResponse(/* args */);
    ~HttpResponse();

    void generateResHttpData(std::string &dst);
};



#endif