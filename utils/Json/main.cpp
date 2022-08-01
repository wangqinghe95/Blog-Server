#include"jsonparser.h"
#include<string>
#include<iostream>
using namespace std;

int main()
{
    // string str = "{\"age\":18,\"isStudent\":false,\"isWork\":true}";
    // string str = "{\"age\":18}";
    // string str = "{\"name\":\"wanghao\"}";
    string str = "{\"infomation\":[\"name\":\"wanghao\",\"age\":18]}";
    JsonValue root = JsonParser::toJsonValue(str);
    string str_json = JsonParser::toJson(root);
    str_json.push_back('\0');
    cout << str_json.data() << endl;
    return 0;
}