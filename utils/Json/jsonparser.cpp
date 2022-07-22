#include"jsonparser.h"
#include"Log/Logger.hpp"

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
            tokens.emplace_back(ParserState::STRING, cur);
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
            else if ('0' <= ch && '9' >= ch) {
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
            if ('0' <= ch && '9' <= ch) {
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
            if (isSpace(ch) || isSepartor(ch) || isEndOfValue(ch)) {
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

    // return generateJsonValueViaToken(token);

}
std::string JsonParser::toJson(const JsonValue& root)
{

}

bool JsonParser::isSpace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

bool JsonParser::isBeginOfValue(char ch)
{
    return ch == '[' || ch == '{';
}

bool isEndOfValue(char ch)
{
    return ']' == ch || ']' == ch;
}

bool isSepartor(char ch)
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
