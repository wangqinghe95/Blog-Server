#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include"HttpRequest.hpp"
using namespace std;

void openFile(string& data)
{
    ifstream infile;
    infile.open("postData.md");
    // infile >> data;
    string tmp;
    while(getline(infile, tmp)){
        data += (tmp + "\r\n");
    }
    // cout << data << endl;
    return;
}

int main()
{
    // string strPostRequest = "POST /xmweb?host=mail.itcast.cn&_t=1542884567319 HTTP/1.1\r\nHost: mail.itcast.cn\r\nConnection: keep-alive\r\nContent-Type: application/x-www-form-urlencoded\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36\r\n\r\nusername=hello&pass=hello";
    string strPostRequest;
    openFile(strPostRequest);
    // return 0;
    HttpRequest CRequest;
    // cin >> strPostRequest;
    cout << strPostRequest << endl;
    if (DecodeState::INVALID == CRequest.analyzeHttpRequestString(strPostRequest)){
        cout << "params error" << endl;
        return 0;
    }

    cout << "method: " << CRequest.getMethod() << endl;
    cout << endl;

    cout << "url: " << CRequest.getURI() << endl;
    cout << endl;

    cout << "protocol :" << CRequest.getProtocol() << endl;
    cout << endl;

    cout << "Version : " << CRequest.getVersion() << endl;
    cout << endl;

    cout << "request params : " << endl;
    map<string,string> mapRequstParams = CRequest.getRequestParams();
    for (auto & iter : mapRequstParams){
        cout << iter.first << " : ";
        cout << iter.second << endl;
    }
    cout << endl;
    
    cout << "request header : " << endl;
    map<string,string> mapHeader = CRequest.getHeaders();
    for (auto & iter : mapHeader){
        cout << iter.first << " : ";
        cout << iter.second << endl;
    }

    cout << endl;
    cout << "Content-Length" << CRequest.getContentLength() << endl;
    cout << "body:" << CRequest.getBody() << endl;

    return 0;
}