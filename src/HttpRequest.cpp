#include"HttpRequest.hpp"
#include<cctype>

HttpRequest::HttpRequest():m_emDecodeState(DecodeState::START)
{
}

HttpRequest::~HttpRequest()
{
}

DecodeState HttpRequest::analyzeHttpRequestString(const std::string& strRequestData)
{
    if (strRequestData.empty()){
        return DecodeState::EMPTY;
    }

    for (size_t i = 0; i < strRequestData.size(); ++i) {
        char ch = strRequestData.at(i);
        switch (m_emDecodeState)
        {
            case DecodeState::START:{
                if ('\r' == ch || '\n' == ch || isblank(ch)) {
                    // do nothing
                }
                else if (isupper(ch)) {
                    m_method.assign(1, ch);
                    m_emDecodeState = DecodeState::METHOD;
                }
                else {
                    m_emDecodeState = DecodeState::INVALID;
                }
                break;
            }
            case DecodeState::METHOD:{
                // it shoule be a upper char of method, if it not, then return
                if(isupper(ch)) {
                    m_method.push_back(ch);
                }
                else if (isblank(ch)) {
                    // the process of parsing method is end, then parse URI
                    m_emDecodeState = DecodeState::BEFORE_URI;
                }
                else {
                    m_emDecodeState = DecodeState::INVALID;
                }
                break;
            }
            case DecodeState::BEFORE_URI:{
                // the url begin as char '/'
                if ('/' == ch) {
                    m_url.assign(1,ch);
                    m_emDecodeState = DecodeState::IN_URI;
                }
                else if (isblank(ch)) {

                }
                else {
                    m_emDecodeState = DecodeState::INVALID;
                }
                break;
            }
            case DecodeState::IN_URI:{
                if('?' == ch) {
                    m_emDecodeState = DecodeState::BEFORE_URI_PARAM_KEY;
                }
                else if (isblank(ch)) {
                    m_emDecodeState = DecodeState::BEFORE_PROTOCOL;
                }
                else {
                    m_url.push_back(ch);
                }
                break;
            }
            case DecodeState::BEFORE_URI_PARAM_KEY:{
                if (isblank(ch) || '\n' == ch || '\r' == ch) {
                    m_emDecodeState = DecodeState::INVALID;
                }
                else {
                    m_requestParamKey.assign(1, ch);
                    m_emDecodeState = DecodeState::URI_PARAM_KEY;
                }
                break;
            }
            case DecodeState::URI_PARAM_KEY:            {
                if('=' == ch) {
                    m_emDecodeState = DecodeState::BEFORE_URI_PARAM_VALUE;
                }
                else if (isblank(ch)) {
                    m_emDecodeState = DecodeState::INVALID;
                }
                else {
                    m_requestParamKey.push_back(ch);
                }
                break;
            }
            case DecodeState::BEFORE_URI_PARAM_VALUE:{
                if (isblank(ch) || '\n' == ch || '\r' == ch) {
                    m_emDecodeState = DecodeState::INVALID;
                }
                else {
                    m_requestParamValue.assign(1,ch);
                    m_emDecodeState = DecodeState::URI_PARAM_VALUE;
                }
                break;
            }
            case DecodeState::URI_PARAM_VALUE:{
                if ('&' == ch) {
                    m_requestParams.insert({m_requestParamKey,m_requestParamValue});
                    m_emDecodeState = DecodeState::BEFORE_URI_PARAM_KEY;
                }
                else if (isblank(ch)) {
                    m_requestParams.insert({m_requestParamKey, m_requestParamValue});
                    m_emDecodeState = DecodeState::PROTOCOL;
                }
                else {
                    m_requestParamValue.push_back(ch);
                }
                break;
            }
            case DecodeState::BEFORE_PROTOCOL:{
                if(isblank(ch)){

                }
                else{
                    m_protocol.assign(1, ch);
                    m_emDecodeState = DecodeState::PROTOCOL;
                }
                break;
            }
            case DecodeState::PROTOCOL:{
                if ('/' == ch) {
                    m_emDecodeState = DecodeState::BEFORE_VERSION;
                }
                else {
                    m_protocol.push_back(ch);
                }
                break;
            }
            case DecodeState::BEFORE_VERSION:{
                if(isdigit(ch)){
                    m_version.assign(1, ch);
                    m_emDecodeState = DecodeState::VERSION;
                }
                else {
                    m_emDecodeState = DecodeState::INVALID;
                }
                break;
            }
            case DecodeState::VERSION:{
                if ('\r' == ch) {
                    m_emDecodeState = DecodeState::WHEN_CR;
                }
                else if ('.' == ch) {
                    m_version.push_back(ch);
                    m_emDecodeState = DecodeState::VERSION_SPLIT;
                }
                else if (isdigit(ch)) {
                    m_version.push_back(ch);
                }
                else {
                    m_emDecodeState = DecodeState::INVALID;
                }
                break;
            }
            case DecodeState::VERSION_SPLIT:{
                if(isdigit(ch)){
                    m_version.push_back(ch);
                    m_emDecodeState = DecodeState::VERSION;
                }
                else {
                    m_emDecodeState = DecodeState::INVALID;
                }
                break;
            }
            case DecodeState::WHEN_CR:{
                if('\n' == ch) {
                    m_emDecodeState = DecodeState::CR_LF;
                }
                else{
                    m_emDecodeState = DecodeState::INVALID;
                }
                break;
            }
            case DecodeState::CR_LF:{
                if('\r' == ch) {    // after \r\n, and another \r was encountered, there is a possibilty to end 
                    m_emDecodeState = DecodeState::CR_LF_CR;
                }
                else if(isblank(ch)) {
                    m_emDecodeState = DecodeState::INVALID;
                }
                else {
                    m_headerKey.assign(1, ch);
                    m_emDecodeState = DecodeState::HEADER_KEY;
                }
                break;
            }
            case DecodeState::CR_LF_CR:{
                // after \r\n\r\n, it will be a body possibily 
                if(m_headers.count("Content-Length") > 0) {

                } 
            }
            case DecodeState::HEADER_KEY:{

            }
            case DecodeState::INVALID:
            {
                break;
            }
            case DecodeState::COMPLITED:
            {
                break;
            }
            
            default:
                break;
        }
    }
    return m_emDecodeState;
}