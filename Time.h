// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs
#ifndef TIME_H_
#define TIME_H_

#include <iostream>


class Time
{
public:
    //std::string get_time();
    //void set_time(int & hour,int & minute,int & second);
    bool is_am();
    std::string to_string(bool if_am);
    Time();
    Time(int hour,int minute,int second);
    Time(int hour,int minute,int second, bool if_am);
    int get_hour() const;
    int get_minute() const;
    int get_second() const;
private:
    bool if_am;
    int hour;
    int minute;
    int second;
};

#endif
