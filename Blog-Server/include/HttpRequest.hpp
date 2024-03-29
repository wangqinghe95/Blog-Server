#ifndef _HTTPREQUEST_HPP__
#define _HTTPREQUEST_HPP__

#include<iostream>
#include<map>
#include<string>


enum DecodeState{
    EMPTY = -1,
    INVALID = 0,

    START,  // request line start
    METHOD, // request method

    BEFORE_URI,
    IN_URI,
    BEFORE_URI_PARAM_KEY,
    URI_PARAM_KEY,
    BEFORE_URI_PARAM_VALUE,
    URI_PARAM_VALUE,

    BEFORE_PROTOCOL,
    PROTOCOL,
    
    BEFORE_VERSION,
    VERSION_SPLIT,
    VERSION,

    HEADER_KEY,
    HEADER_BEFROE_COLON,
    HEADER_AFTER_COLON,
    HEADER_VALUE,

    WHEN_CR,
    CR_LF,
    CR_LF_CR,

    BODY,

    COMPLITED,  // analyze complete

};

class HttpRequest
{

public:
    HttpRequest(/* args */);
    ~HttpRequest();

    DecodeState analyzeHttpRequestString(const std::string& strRequestData);

    std::string getURI(){
        return m_url;
    }

    std::string getMethod(){
        return m_method;
    }

    std::string getProtocol(){
        return m_protocol;
    }

    std::string getVersion(){
        return m_version;
    }

    size_t getContentLength(){
        return m_contentLength;
    }

    std::string getBody()
    {
        return m_body;
    }

    std::map<std::string,std::string> getRequestParams(){
        return m_requestParams;
    }

    std::map<std::string,std::string> getHeaders(){
        return m_headers;
    }

private:
    DecodeState m_emDecodeState;

    std::string m_method;

    std::string m_url;

    std::map<std::string, std::string> m_requestParams;

    size_t m_contentLength;

private:
    std::string m_requestParamKey;
    std::string m_requestParamValue;

    std::string m_headerKey;
    std::string m_headerValue;

private:
    std::string m_protocol;
    std::string m_version;
    std::string m_body;
    std::map<std::string, std::string> m_headers;
};



#endif