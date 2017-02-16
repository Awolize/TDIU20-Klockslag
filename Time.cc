#include "Time.h"
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include <stdexcept>
using namespace std;

void Time::Check_Value(int hour, int minute, int second)
{
    if (hour > 23 || hour < 0 || minute > 59 ||
	minute < 0 || second > 59 || second < 0) 
    { ///1-4 FIXED
	throw invalid_argument("Invalid Input");
    } 
}
Time::Time(int hour, int minute, int second)
    :hour{hour}, minute{minute}, second{second}
{ ///1-4 FIXED
    Check_Value(hour, minute, second);
} ///1-3 FIXED
Time::Time(const std::string & time_str) 
    :hour{0}, minute{0}, second{0}
{ ///1-4 FIXED
    stringstream ss{""};
    int h{0},m{0},s{0};   
    char ch{' '};
    ss << time_str;
    ss >> h;
    ss.ignore();
    ss >> m;
    ss.ignore();
    ss >> s;
    Check_Value(h,m,s);
    hour = h;
    minute = m;
    second = s;
}
Time::Time(int)
    :hour{0}, minute{0}, second{0}
{
    throw invalid_argument("Invalid Input");
}
Time::Time(int, int) 
    :hour{0}, minute{0}, second{0}
{
    throw invalid_argument("Invalid Input");
}
Time::Time()
    :hour{0}, minute{0}, second{0} {}

string Time::to_string(bool if_am) 
{
    stringstream ss;
    int temp_hour {hour};
    if(if_am && hour > 12) 
    {
	temp_hour -= 12;
    }
    if (temp_hour < 10) 
    {
	ss << '0';
    }
    ss << temp_hour << ":";
    if (minute < 10)
    {
	ss << '0';
    }
    ss << minute  << ":";
    if (second < 10) 
    {
	ss << '0';
    }
    ss  << second;  
    if (if_am)
    {
	if (is_am())
	{
	    ss << " am";
	}
	else 
	{
	    ss << " pm";
	    hour -= 12;
	}
    }
    ///returnera ss.str() direkt FIXED
    
    return ss.str();
}
int Time::get_hour() const 
{
    return hour;
}
int Time::get_minute() const 
{
    return minute;
}
int Time::get_second() const 
{
    return second;
}
bool Time::is_am() const 
{
    if (hour < 12) 
    {
	return true;
    }
    else 
    { 
	return false;	
    }
}
Time::operator string() 
{
    return to_string(false);
}

Time Time::operator-(int rhs) 
{
    rhs = -rhs; //------
    return operator+(rhs);
}

Time Time::operator+(int rhs) 
{
    Time t{hour, minute, second};
    t.second += rhs;
    return time_Check(t);
}
Time operator+(int lhs, Time rhs) 
{
    return rhs+lhs;
}


Time& Time::operator++() 
{
    second++;
    if (second > 59) 
    {
	second -= 60;
	minute++;
    }
    if(minute > 59) 
    {
	minute -= 60;
	hour++;
    }
    if(hour > 23)
    {
	hour -= 24;
    }

    return *this;
}
Time& Time::operator--() 
{
    second--;
    if (hour < 0)
    {
	hour += 24;
    }
    if (minute < 0) 
{
	minute += 60;
	hour--;
    }
    if (second < 0) 
{
	second += 60;
	minute--;
    }

    return *this;
}
Time Time::operator++(int) 
{
    Time t{hour,minute,second};
    second++;
    time_Check(*this);

    return t;
}
Time Time::operator--(int) 
{
    Time t{hour,minute,second};
    second--;
    time_Check(*this);

    return t;
}


Time Time::time_Check(Time rhs)
{
    while(rhs.hour > 23 || rhs.hour < 0 || rhs.minute > 59
	  || rhs.minute < 0 || rhs.second > 59 || rhs.second < 0) 
    {
	if (rhs.second > 59) 
	{
	    rhs.second -= 60;
	    rhs.minute++;
	}
	if (rhs.minute > 59) 
	{
	    rhs.minute -= 60;
	    rhs.hour++;
	}
	if (rhs.hour > 23)
	{
	    rhs.hour -= 24;
	}
	if (rhs.hour < 0) 
	{
	    rhs.hour += 24;
	}
	if (rhs.minute < 0) 
	{
	    rhs.minute += 60;
	    rhs.hour--;
	}
	if (rhs.second < 0) 
	{
	    rhs.second += 60;
	    rhs.minute--;
	}	
    }
    return rhs;
}

bool Time::operator<(const Time & rhs) const
{
    if (hour < rhs.hour)
	return true;
    else if (hour == rhs.hour && minute < rhs.minute) 
	return true;
    else if(hour == rhs.hour && minute == rhs.minute && second < rhs.second)
	return true;
    return false;
}

bool Time::operator>(const Time & rhs) const
{
    return rhs<*this;
}

bool Time::operator<=(const Time & rhs) const
{
    return !(rhs<*this);
}

bool Time::operator>=(const Time & rhs) const
{
    return !(*this<rhs);
}

bool Time::operator==(const Time & rhs) const
{
    return !(rhs<*this || *this<rhs);
}

bool Time::operator!=(const Time & rhs) const 
{
    return rhs<*this || *this<rhs;
}

std::ostream& operator<<(std::ostream& os, Time t) 
{
    os << t.to_string(false);
    return os;
}

std::istream& operator>>(std::istream& is,Time t) 
{
    char c{':'};
    is >> t.hour >> c >> t.minute >> c >> t.second;
    if (t.hour > 23 || t.hour < 0 || t.minute > 59 ||
	t.minute < 0 || t.second > 59 || t.second < 0) 
    {
	is.setstate(ios::failbit);
    }
    return is;
}



