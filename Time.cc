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
    cout << ss.str();
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
/*
Time::operator std::string() {
    return "rhs.to_string(false)";    
}
*/

Time Time::operator+ (Time rhs) {
    return Time{0,0,0};
}
