#include"jsonparser.h"
#include<string>
#include<iostream>
using namespace std;

int main()
{
    // string str = "{\"age\":18,\"isStudent\":false,\"isWork\":true}";
    // string str = "{\"age\":18}";
    // string str = "{\"name\":\"wanghao\"}";
    string str = "{\"s\":[\"age\",18,false]}";
    JsonValue root = JsonParser::toJsonValue(str);
    string str_json = JsonParser::toJson(root);
    str_json.push_back('\0');
    cout << str_json.data() << endl;

    JsonObject js_object;
    js_object.insert("1234\"",root);
    string str_json1 = JsonParser::toJson(js_object);
    cout << str_json1.c_str() << endl;

    return 0;
}