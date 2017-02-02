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
    operator string(); 
    Time operator+(int);
    Time operator- (int);
    Time& operator++();
    Time& operator--();
    Time operator++(int);
    Time operator--(int);
    bool operator<(const  Time &) const;
    bool operator>(const  Time &) const;
    bool operator<=(const  Time &) const;
    bool operator>=(const  Time &) const;
    bool operator==(const  Time &) const;
    bool operator!=(const  Time &) const;
    friend std::ostream& operator<<(std::ostream&, Time);
    friend std::istream& operator>>(std::istream&, Time);
    
private:
    Time time_Check(Time);
    void Check_Value(int hour, int minute, int second);
    int hour;
    int minute;
    int second;
    bool if_am;
};

std::ostream& operator<<(std::ostream& os, Time t);
std::istream& operator>>(std::istream& is, Time t);		      
#endif
