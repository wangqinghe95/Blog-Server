#include"HttpResponse.hpp"
#include"logger.hpp"
using namespace std;

constexpr int g_nMaxStatusLine = 1024;

const std::unordered_map<std::string, std::string> HttpResponse::m_fileContentType = {
    {"text", "text/plain; charset=utf-8"},
    {"jpg", "image/jpeg"},
    {"png", "images/png"},
    {"json", "application/json"}
};

HttpResponse::HttpResponse(): m_nStatusCode(200)
                            , m_strStatusWord("OK")
{
}


HttpResponse::~HttpResponse()
{
    m_strStatusWord.assign("OK");
    m_nStatusCode = 200;
}

void HttpResponse::generateResHttpData(std::string &dst)
{
    setVersion("1.1");
    setProtocol("HTTP");
    
    if(getHeaderValueByKey("Content-length").empty()) {
        setHeader("Content-Type", m_fileContentType.at("text"));
    }

    m_headers["Content-Length"] = std::to_string(m_body.size());

    char chArrStatusLine[g_nMaxStatusLine];
    int size = snprintf(chArrStatusLine, g_nMaxStatusLine, "%s %s %d %s\r\n"
                        , getProtocol().c_str(), getVersion().c_str()
                        , m_nStatusCode, m_strStatusWord.c_str());
    if(size < 0) {
        LOG_ERROR("generate status line error");
        return;
    }

    dst.append(chArrStatusLine, chArrStatusLine+size);

    for (const auto &header : getHeaders()) {
        dst.append(header.first).append(": ").append(header.second).append("\r\n");
    }

    dst.append("\r\n");

    dst.append(getBody());
}
