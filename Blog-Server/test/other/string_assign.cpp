#include<iostream>
#include<string>
using namespace std;

int main()
{
   string str;
   string base = "The quick brown fox jumps over a lazy dog.";
   char c_string[] = "c-string";
   char *pCString = "the point to a string of C type";

    //string (1)	string& assign (const string& str);
    str.assign(base);
    cout << "string 1: " << str << endl;

    //substring (2)	string& assign (const string& str, size_t subpos, size_t sublen = npos);
    str.assign(base, 10, 9);
    cout << "substring 2:" << str << endl;

    // c-string 3 string& assign (const char* s);
    str.assign(c_string);
    cout << "c-string 3" << str << endl;

    // buffer (4)	string& assign (const char* s, size_t n);
    str.assign(pCString, 5);
    cout << "buffer 4 : " << str << endl;

    // fill (5)	string& assign (size_t n, char c);
    str.assign(10, '*');
    cout << "fill 5 : " << str << endl; 

    // range 6 template <class InputIterator>
    str.assign(base.begin() + 16, base.end()-12);
    cout << "range 6 : " << str << endl;

    // initializer list(7)	string& assign (initializer_list<char> il);
    initializer_list<char> il{'2','s','b'};
    str.assign(il);
    cout << "initializer list 7:" << str << endl;

    // move 8
    string&& str_move("this is nove");
    str.assign(str_move);
    cout << "move 8 str : " << str << ", str_move : " << str_move << endl;
    
    return 0;
}