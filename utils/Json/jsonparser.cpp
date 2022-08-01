#include"jsonparser.h"
// #include"Log/Logger.hpp"

using namespace std;

enum class ParserState{
    BEGIN = 0,
    
    OBJECT_OR_ARRAY_BEGIN,
    
    STRING_BEGIN,
    STRING,

    NUMBER_BEGIN,
    NUMBER_POINT,
    NUMBER_BEFORE_POINT,
    NUMBER_AFTER_POINT,

    END,

    N_IN_NULL,
    NU_IN_NULL,
    NUL_IN_NULL,

    T_IN_TRUE,
    TR_IN_TRUE,
    TRU_IN_TRUE,

    F_IN_FALSE,
    FA_IN_FALSE,
    FAL_IN_FALSE,
    FALS_IN_FALSE,

    ESCAPE,
    ERROR
};

JsonValue JsonParser::toJsonValue(const std::string &json)
{
    auto p = json.begin();
    ParserState state = ParserState::BEGIN;
    
    std::list<JsonToken> tokens;

    while (ParserState::ERROR != state && json.end() != p)
    {
        char ch = *p;
        auto cur = p++;

        switch (state)
        {
        case ParserState::BEGIN:
        {

            if (isSpace(ch)){
                // do nothing
            } 
            else if (isBeginOfValue(ch)) {
				pushBackIfToken(tokens, ch, cur);
				state = ParserState::OBJECT_OR_ARRAY_BEGIN;
            }
			else if ('"' == ch){
				state = ParserState::STRING_BEGIN;	
			}
			else if ('0' <= ch && '9' >= ch){
				tokens.emplace_back(TokenType::Double, cur);
				p--;
				state = ParserState::NUMBER_BEGIN;
			}
			else if ('-' == ch){
				tokens.emplace_back(TokenType::Double, cur);
				state = ParserState::NUMBER_BEGIN;
			}
            else if ('f' == ch) {
                tokens.emplace_back(TokenType::False, cur);
                state = ParserState::F_IN_FALSE;
            }
            else if ('t' == ch) {
                tokens.emplace_back(TokenType::True, cur);
                state = ParserState::T_IN_TRUE;
            }
            else if ('n' == ch) {
                tokens.emplace_back(TokenType::Null, cur);
                state = ParserState::N_IN_NULL;
            }
            else {
                state = ParserState::ERROR;
            }
			break;
        }
        case ParserState::OBJECT_OR_ARRAY_BEGIN:
        {
            if (isSpace(ch)) {
                // do nothing
            }
            else if (isEndOfValue(ch)) {
                pushBackIfToken(tokens, ch, cur);
                state = ParserState::END;
            }
            else {
                p--;
                state = ParserState::BEGIN;
            }
            break;
        }
        case ParserState::N_IN_NULL:
        {
            state = ('u' == ch ? ParserState::NU_IN_NULL : ParserState::ERROR);
            break;
        }
        case ParserState::NU_IN_NULL:
        {
            state = ('l' == ch ? ParserState::NUL_IN_NULL : ParserState::ERROR);
            break;
        }
        case ParserState::NUL_IN_NULL:
        {
            if ('l' == ch) {
                tokens.back().end = cur;
                state = ParserState::END;
            }
            else {
                state = ParserState::ERROR;
            }
            break;
        }
        case ParserState::T_IN_TRUE:
        {
            state = ('r' == ch ? ParserState::TR_IN_TRUE : ParserState::ERROR);
            break;
        }
        case ParserState::TR_IN_TRUE:
        {
            state = ('u' == ch ? ParserState::TRU_IN_TRUE : ParserState::ERROR);
            break;
        }
        case ParserState::TRU_IN_TRUE:
        {
            if ('e' == ch) {
                tokens.back().end = cur;
                state = ParserState::END;
            }
            else {
                state = ParserState::ERROR;
            }
            break;
        }
        case ParserState::F_IN_FALSE:
        {
            state = ('a' == ch ? ParserState::FA_IN_FALSE : ParserState::ERROR);
            break;
        }
        case ParserState::FA_IN_FALSE:
        {
            state = ('l' == ch ? ParserState::FAL_IN_FALSE : ParserState::ERROR);
            break;
        }
        case ParserState::FAL_IN_FALSE:
        {
            state = ('s' == ch ? ParserState::FALS_IN_FALSE : ParserState::ERROR);
            break;
        }
        case ParserState::FALS_IN_FALSE:
        {
            if ('e' == ch) {
                tokens.back().end = cur;
                state = ParserState::END;
            }
            else {
                state = ParserState::ERROR;
            }
            break;
        }
        case ParserState::ESCAPE:
        {
            state = ParserState::STRING;
            break;;
        }
        case ParserState::STRING_BEGIN:
        {
            tokens.emplace_back(TokenType::String, cur);
            state = ParserState::STRING;
            break;
        }
        case ParserState::STRING:
        {
            if ('"' == ch) {
                tokens.back().end = cur;
                state = ParserState::END;
            }
            else if ('\\' == ch) {
                state = ParserState::ESCAPE;
            }
            break;
        }
        case ParserState::NUMBER_BEGIN:
        {
            if ('0' == ch) {
                state = ParserState::NUMBER_POINT;
            }
            else if ('1' <= ch && '9' >= ch) {
                state = ParserState::NUMBER_BEFORE_POINT;
            }
            else {
                state = ParserState::ERROR;
            }
            break;
        }
        case ParserState::NUMBER_POINT:
        {
            if ('.' == ch) {
                state = ParserState::NUMBER_AFTER_POINT;
            }
            else if (',' == ch || isSepartor(ch) || isEndOfValue(ch)) {
                tokens.back().type = TokenType::LongLong;
                tokens.back().end = cur;
                p--;
                state = ParserState::END;
            }
            else {
                state = ParserState::ERROR;
            }
            break;
        }
        case ParserState::NUMBER_BEFORE_POINT: {
            if ('0' <= ch && '9' >= ch) {
                // do nothing
            }
            else {
                p--;
                state = ParserState::NUMBER_POINT;
            }
            break;
        }
        case ParserState::NUMBER_AFTER_POINT:
        {
            if ('0' <= ch && '9' >= ch) {
                // do nothing
            }
            else if(',' == ch || isSpace(ch) || isEndOfValue(ch)) {
                tokens.back().end = cur;
                p--;
                state = ParserState::END;
            }
            else {
                state = ParserState::ERROR;
            }
            break;
        }
        case ParserState::END:
        {
            bool isEnd = isSpace(ch) || isSepartor(ch) || isEndOfValue(ch);
            if (isEnd) {
                pushBackIfToken(tokens, ch, cur);
            }
            else {
                p--;
                state = ParserState::BEGIN;
            }
            break;
        }

        default:
            break;
        }

    }

    if (ParserState::ERROR == state) {
        return JsonValue();
    }

    return generateJsonValueViaTokens(tokens);
}

JsonValue JsonParser::generateJsonValueViaTokens(std::list<JsonToken>& tokens)
{
    JsonToken token = tokens.front();
    tokens.pop_front();

    if (TokenType::objectBegin == token.type)
    {
        JsonValue res = generateJsonObjectViaTokens(tokens);
        return res;
    }
    else if (TokenType::ArrayBegin == token.type) {
        return generateJsonArrayViaTokens(tokens);
    }

    if (TokenType::String == token.type) {
        return JsonValue(token.start, token.end);
    }
    else if (TokenType::True == token.type) {
        return JsonValue(true);
    }
    else if (TokenType::False == token.type) {
        return JsonValue(false);
    }
    else if (TokenType::Double == token.type) {
        return JsonValue(std::atof(std::string(token.start,token.end).c_str()));
    }
    else if (TokenType::LongLong == token.type) {
        std::string str_value = std::string(token.start, token.end).c_str();
        return JsonValue(std::atoll(std::string(token.start, token.end).c_str()));
    }
    else if (TokenType::Null == token.type) {
        return JsonValue();
    }
    return JsonValue();
}

JsonValue JsonParser::generateJsonObjectViaTokens(std::list<JsonToken> &tokens)
{
    JsonObject json_object;
    while(TokenType::objectEnd != tokens.front().type){
        JsonToken key = tokens.front();
        tokens.pop_front();

        if (tokens.front().type != TokenType::ObjectKeyValueSeparator) {
            return false;
        }

        if (tokens.empty()) {
            return JsonValue();
        }

        tokens.pop_front();

        json_object.insert(std::string(key.start, key.end),generateJsonValueViaTokens(tokens));

        if (tokens.empty()) {
            return JsonValue();
        }

        if (TokenType::MemberSeparator == tokens.front().type) {
            tokens.pop_front();
        }
        else if (TokenType::objectEnd == tokens.front().type) {
            // do nothing
        }
        else {
            return JsonValue();
        }

    }
    tokens.pop_front();
    return json_object;
}

JsonValue JsonParser::generateJsonArrayViaTokens(std::list<JsonToken>& tokens)
{
    JsonArray json_array;

    while(TokenType::ArrayEnd != tokens.front().type) {
        json_array.append(generateJsonValueViaTokens(tokens));

        if (tokens.empty()){
            return JsonValue();
        }

        if(TokenType::MemberSeparator == tokens.front().type) {
            tokens.pop_back();
        }
        else if(TokenType::ArrayEnd == tokens.front().type) {
            // do nothing
        }
        else {
            return JsonValue();
        }
    }

    tokens.pop_front();
    return json_array;
}

std::string JsonParser::toJson(const JsonValue& root)
{
    std::string str_json;

    switch (root.type())
    {
    case JsonValueType::Null:{
        str_json.append("null");
        break;
    }
    case JsonValueType::Double:{
        str_json.append(std::to_string(root.ToDouble()));
        break;
    }
    case JsonValueType::LongLong:{
        str_json.append(std::to_string(root.toLongLong()));
        break;
    }
    case JsonValueType::String:{
        str_json.push_back('"');
        for (char ch : root.toString()){
            switch (ch)
            {
                case '\"':{
                    str_json.append({'\\','\"'});
                    break;
                }
                case '\\':{
                    str_json.append({'\\', '\\'});
                    break;
                }
                case '\b':{
                    str_json.append({'\\','b'});
                    break;
                }
                case '\f':{
                    str_json.append({'\\','f'});
                    break;
                }
                case '\n':{
                    str_json.append({'\\','n'});
                    break;
                }
                case '\r':{
                    str_json.append({'\\','n'});
                    break;
                }
                case '\t':{
                    str_json.append({'\\','t'});
                    break;
                }
                default:
                    str_json.push_back(ch);
            }
        }
        str_json.push_back('"');
        break;;
    }
    case JsonValueType::Boolean:{
        if (root.toBoolean()){
            str_json.append("true");
        }
        else {
            str_json.append("false");
        }
        break;
    }
    case JsonValueType::Array:{
        str_json.push_back('[');
        bool isFirst = true;
        for (const auto& v : root.toArray()) {
            if(isFirst) {
                isFirst = false;
            }
            else {
                str_json.push_back(',');
            }
            str_json.append(toJson(v));
        }
        str_json.push_back(']');
        break;
    }
    case JsonValueType::Object:{
        str_json.push_back('{');
        bool isFirst = true;
        for (const auto& kv : root.toObject()){
            if (isFirst){
                isFirst = false;
            }
            else {
                str_json.push_back(',');
            }
            str_json.append(toJson(kv.first));
            str_json.push_back(':');
            str_json.append(toJson(kv.second));
        }
        str_json.push_back('}');
        break;
    }
    
    default:
        break;
    }
    return str_json;
}

bool JsonParser::isSpace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

bool JsonParser::isBeginOfValue(char ch)
{
    return ch == '[' || ch == '{';
}

bool JsonParser::isEndOfValue(char ch)
{
    return ']' == ch || '}' == ch;
}

bool JsonParser::isSepartor(char ch)
{
    return ':' == ch || ',' == ch;
}

void JsonParser::pushBackIfToken(list<JsonToken> &tokens, char ch, const string::const_iterator &pos)
{
    switch (ch)
    {
    case '{':
        tokens.emplace_back(TokenType::objectBegin, pos);
        break;
    case '}':
        tokens.emplace_back(TokenType::objectEnd, pos);
        break;
    case '[':
        tokens.emplace_back(TokenType::ArrayBegin, pos);
        break;
    case ']':
        tokens.emplace_back(TokenType::ArrayEnd, pos);
        break;
    case ':':
        tokens.emplace_back(TokenType::ObjectKeyValueSeparator, pos);
        break;
    case ',':
        tokens.emplace_back(TokenType::MemberSeparator, pos);
        break;
    default:
        break;
    }
}
