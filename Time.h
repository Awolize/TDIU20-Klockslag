// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs
#ifndef TIME_H_
#define TIME_H_

#include <iostream>
using std::string;

class Time
{
public:
    bool is_am();
    std::string to_string(bool if_am);
    Time(int hour, int minute, int second);
    Time();
    Time(string time_str);
    int get_hour() const;
    int get_minute() const;
    int get_second() const;
    void Check_Value(int hour, int minute, int second);
    operator string(); 
    Time operator+ (Time);
private:
    string time_str;
    bool if_am;
    int hour;
    int minute;
    int second;
};

#endif
