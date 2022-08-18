#ifndef _HTTPBASE_HPP__
#define _HTTPBASE_HPP__

#include<string>
#include<vector>
#include<map>

class HttpBase
{
protected:
    std::string m_protocol;
    std::string m_version;

    std::map<std::string, std::string> m_headers;
    std::string m_body;

public:
    const std::string& getProtocol() const;
    void setProtocol(const std::string& protocol);

    const std::string& getVersion() const;
    void setVersion(const std::string &version);

    const std::map<std::string, std::string> &getHeaders() const;
    void setHeader(const std::string& key, const std::string& value);
    std::string getHeaderValueByKey(std::string &key) const;
    std::string getHeaderValueByKey(const char* key) const;
     
    std::string &getBody();

    virtual void clear();
};

#endif 