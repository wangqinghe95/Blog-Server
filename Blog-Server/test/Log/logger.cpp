#include"logger.hpp"
#include<iostream>
#include<string>
// #include<string>
#include<sstream>
#include<ctime>
using namespace std;
    // void output(const std::string* strLogName, LogLevel level
    //             , const char* format ,const std::string &file
    //             , const long line, const std::string& function
    //             , const ARGS &...args);
void Logger::output(const std::string &file, long line ,const std::string& func, const std::string& msg )
{
    stringstream ss;
	string str_time;
	getTimeStamp(str_time);
	ss << "[" << str_time << "] ";
    ss << "[" << file << ":" << func << ":" << line << "] " << msg << endl;
    cout << ss.str() << endl;
}

void Logger::getTimeStamp(std::string& str_time)
{
	time_t now_time;
	struct tm* time_info;
	time(&now_time);
	time_info = localtime(&now_time);
	str_time += (to_string(time_info->tm_year+1900) + "-");
	str_time += (to_string(time_info->tm_mon) + "-");
	str_time += (to_string(time_info->tm_mday) + " ");
	str_time += (to_string(time_info->tm_hour) + ":");
	str_time += (to_string(time_info->tm_min) + ":");
	str_time += (to_string(time_info->tm_sec));
}
