#include"http.hpp"
using namespace std;

// to do
int Request::requestAnalyzeMessage(string &recv_data) {
    int nRet = 0;
    return nRet;
}

int Request::requestGenerateHttp(string& send_data) {
    int nRet = 0;
    
    getSendData(200, send_data);

    return nRet;
}

int Request::getSendData(int code, string& send_data) {
    string messages;
    messages += "HTTP/1.1 " + to_string(code) + " OK\r\n";
    messages += "access-control-allow-origin: *\r\n";
    messages += "access-control-allow-headers: Content-Type,Content-Length, Authorization, Accept,X-Requested-With\r\n";
    messages += "access-control-allow-methods: PUT,POST,GET,DELETE,OPTIONS";

    messages += "connection: close\r\n";
    
    // const string send_content("{name:wanghao, age:15}");
    string send_data_body;
    getBody(send_data_body);
    
    // int send_content_len = strlen(send_content);

    messages += "Content-type: text/html\r\n";
    messages += "content-length: " + to_string(send_data_body.size()) + "\r\n";
    messages += "\r\n";
    messages += send_data_body;
    send_data = messages;
    return send_data.size();
}


int Request::getBody(std::string& body) {
    body += "{\"name\": \"wanghao\", \"age\": 15}";
    
    // JsonWriter *w = new JsonWriter;
    // w->SetInitialIndentDepth(2);
    return body.size();
}