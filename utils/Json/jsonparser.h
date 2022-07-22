#ifndef _JSON_PARSER_H__
#define _JSON_PARSER_H__

#include"jsonvalue.h"
#include<list>
#include<string>

enum class TokenType
{
    objectBegin = 0,
    objectEnd,

    ArrayBegin,
    ArrayEnd,

    ObjectKeyValueSeparator,    // ':'
    MemberSeparator,            // ','

    String,
    Double,
    LongLong,
    True,
    False,
    Null
};

struct JsonToken {
    TokenType type;

    std::string::const_iterator start;
    std::string::const_iterator end;

    JsonToken(TokenType type, const std::string::const_iterator &start)
            : type(type)
            , start(start)
            , end(start)
    {}
};

class JsonParser
{
private:
    /* data */
public:

    static JsonValue toJsonValue(const std::string &json);
    static std::string toJson(const JsonValue& root);

    JsonParser(/* args */);
    ~JsonParser();
private:
    static bool isSpace(char ch);
    static bool isBeginOfValue(char ch);
    static bool isEndOfValue(char ch);
    static bool isSepartor(char ch);
    static void pushBackIfToken(std::list<JsonToken> &tokens, char ch, const std::string::const_iterator &pos);

};

JsonParser::JsonParser(/* args */)
{
}

JsonParser::~JsonParser()
{
}






#endif