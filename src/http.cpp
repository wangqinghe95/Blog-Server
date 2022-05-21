#include "http.hpp"
#include "jsonparser.h"
#include "logger.hpp"
#include <map>
// #include "../include/json/serialization.h"
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
    // string send_data_body = "{\"date\": \"2022-05-12\",\"name\": \"wanghao\", \"address\": suzhou}";
    // string send_data_body("{\"date\":2022-05-12,\"name\":wanghao, \"age\":15}");
    string send_data_body;
    getBody(send_data_body);
    
    // int send_content_len = strlen(send_content);
    LOG_BUG(send_data_body);
    messages += "Content-type: application/json\r\n";
    messages += "content-length: " + to_string(send_data_body.size()) + "\r\n";
    messages += "\r\n";
    messages += send_data_body;
    send_data = messages;
    return send_data.size();
}


int Request::getBody(std::string& body) {
    // string str = "{\"name\": \"wanghao\", \"age\": 15}";

    // JsonValue root = JsonParser::toJsonValue(str);
    
    // JsonObject jsonObj;
    // body = JsonParser::toJson(root);
    // body.push_back('\0');

    map<string,string> data;
    data["name"] = "wanghao";
    data["age"] = "18";

    string res;

    res.push_back('{');
    for (auto it = data.begin(); it != data.end(); ++it) {
        // insertIteratorToRes(res,it->first);
        res.push_back('"');
        res.append(it->first);
        res.push_back('"');
        res.push_back(':');
        res.push_back('"');
        res.append(it->second);
        res.push_back('"');
        res.push_back(',');
    }
    res.pop_back();
    res.push_back('}');

    res.push_back('\0');
    body = move(res);
    // return
    return body.size();
}