///1-7
///se bifogad testfil för kompileringsfel och misslyckade testfall
#ifndef TIME_H_
#define TIME_H_
#include <iostream>
using std::string;

class Time
{
public:
    bool is_am() const;
    ///la till defaultvärde för att testprogrammet inte skulle misslyckas på allting
    string to_string(bool if_am = false);
    Time(int hour, int minute, int second);
    Time();
    Time(int);
    Time(int, int);
    explicit Time(const string &); ///5-4 FIXED, 6-10 FIXED
    int get_hour() const;
    int get_minute() const;
    int get_second() const;
    explicit operator string();  ///6-10 FIXED
    Time operator+(int);
    Time operator- (int);
    Time& operator++();
    Time& operator--();
    Time operator++(int);
    Time operator--(int);
    bool operator<(const Time &) const;
    bool operator>(const Time &) const;
    bool operator<=(const Time &) const;
    bool operator>=(const Time &) const;
    bool operator==(const Time &) const;
    bool operator!=(const Time &) const;
    friend std::ostream& operator<<(std::ostream&, Time);
    friend std::istream& operator>>(std::istream&, Time);   
private: 
    void Check_Value(int hour, int minute, int second);
    Time time_Check(Time);
    int hour;
    int minute;
    int second;
};

Time operator+(int, Time); 
std::ostream& operator<<(std::ostream& os, Time t);
std::istream& operator>>(std::istream& is, Time t);		      
#endif
