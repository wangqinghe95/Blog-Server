#include"Logger.hpp"
#include<iostream>
// #include<string>
#include<sstream>
#include<ctime>
using namespace std;
void Logger::output(const string &file, const long line,const string& function,const string& msg)
{
    stringstream ss;
	string str_time;
	getTimeStamp(str_time);
	ss << "[" << str_time << "] ";
    ss << "[" << file << ":" << function << ":" << line << "]" << endl;
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
