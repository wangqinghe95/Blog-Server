#include"HttpBase.hpp"

const std::string& HttpBase::getProtocol() const
{
    return m_protocol;
}
void HttpBase::setProtocol(const std::string& protocol)
{
    m_protocol = protocol;
}

const std::string& HttpBase::getVersion() const
{
    return m_version;
}
void HttpBase::setVersion(const std::string &version)
{
    m_version = version;
}

const std::map<std::string, std::string>& HttpBase::getHeaders() const
{
    return m_headers;
}
void HttpBase::setHeader(const std::string& key, const std::string& value)
{
    m_headers[key] = value;
}
std::string HttpBase::getHeaderValueByKey(std::string &key) const
{
    auto it = m_headers.find(key);
    if (it != m_headers.end()) {
        return it->second;
    }

    return "";
}

std::string HttpBase::getHeaderValueByKey(const char* key) const
{
    std::string strKey(key);
    return getHeaderValueByKey(strKey);
}

std::string &HttpBase::getBody()
{
    return m_body;
}

void HttpBase::clear()
{
    m_version.clear();
    m_headers.clear();
    m_protocol.clear();
    m_body.clear();
}