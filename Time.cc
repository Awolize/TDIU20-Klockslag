#include "Time.h"
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include <stdexcept>

using namespace std;

// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
void Time::Check_Value(int hour, int minute, int second){
 if (hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0) {
	throw invalid_argument("Invalid Input");
    } 
}
 

Time::Time(int hour, int minute, int second):hour{hour}, minute{minute}, second{second} {
    Check_Value(hour, minute, second);
}

Time::Time(std::string time_str) {
    stringstream ss{""};
    int h{0},m{0},s{0};   
    char ch;
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

Time::Time()
    :hour{0}, minute{0}, second{0} {};

string Time::to_string(bool if_am) {
    stringstream ss;
    if(if_am) 
	hour -= 12;
   
    if (hour < 10) {
	ss << '0';
    }
    ss << hour << ":";
    if (minute < 10) {
	ss << '0';
    }
    ss << minute  << ":";
    if (second < 10) {
	ss << '0';
    }
    ss  << second;
    
    if (if_am){
	if (is_am())
	    ss << " pm";
    }

    string return_string = ss.str();
    return return_string;
}

int Time::get_hour() const {return hour;}
int Time::get_minute() const {return minute;}
int Time::get_second() const {return second;}

bool Time::is_am() {
    if (hour < 12) {
	if_am = true;
	return true;
    }
    else { 
	if_am = false;
	return false;	
    }
}
Time::operator string() {return to_string(false);}


std::ostream& operator<<(std::ostream& os, Time t) {
    return os << t.to_string(false);
}
Time operator- (Time lhs, int rhs) {
    rhs = -rhs;
    operator+(lhs,rhs);
}
Time operator+ (Time lhs, int rhs) {
    for (int i; i >= rhs; i++) {
	lhs++;
    } 
    return Time{lhs.hour,lhs.minute,lhs.second};
}
Time Time::operator++() {
    *this.second + 1;
    time_Check();
    return *this;
}
Time Time::operator--() {
    *this.second - 1;
    time_Check();
    return *this;
}
Time Time::operator++(int) {
    *this + ;
    time_Check();
    return *this;
}
Time Time::operator--(int) {
    *this.second - 1;
    time_Check();
    return *this;
}


void Time::time_Check() {
    while(hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0) {
	if (second > 59) {
	    second -= 60;
	    minute++;
	}
	if(minute > 59) {
	    minute -= 60;
	    hour++;
	}
	if(hour > 23) {
	    hour -= 24;
	}
	if(hour < 0) {
	    hour += 24;
	}
	if(minute < 0) {
	    minute += 60;
	    hour--;
	}
	if (second < 0) {
	    second += 60;
	    minute--;
	}
	
    }
}

bool operator<(Time lhs,Time rhs){
    if (lhs.hour < rhs.hour)
	return true;
    else if (lhs.hour == rhs.hour && lhs.minute < rhs.minute) 
	return true;
    else if(lhs.hour == rhs.hour && lhs.minute == rhs.minute && lhs.second < rhs.second)
	return true;
    return false;
}

bool operator>(Time lhs,Time rhs){
    return rhs<lhs;
}

bool operator<=(Time lhs,Time rhs){
    return !(rhs<lhs);
}

bool operator>=(Time lhs,Time rhs){
    return !(lhs<rhs);
}

bool operator==(Time lhs,Time rhs){
    return !(rhs<lhs || lhs<rhs);
}

bool operator!=(Time lhs,Time rhs){
    return rhs<lhs || lhs<rhs;
}

