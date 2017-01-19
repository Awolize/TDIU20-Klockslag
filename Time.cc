// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "Time.h"

using namespace std;

Time::Time(int hour, int minute, int second, bool if_am) :hour{hour}, minute{minute}, second{second}, if_am{false} {
    if ( hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0) {
	Throw Invalid_Exception("Invalid Input");
    }
												      }

Time::Time(int hour, int minute, int second) :hour{hour}, minute{minute}, second{second}, if_am{false} {   
    if ( hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0) {
	Throw Invalid_Exception("Invalid Input");
    }
											  }

Time::Time() :hour{0}, minute{0}, second{0}, if_am{false} {}

string Time::to_string(bool if_am) {
    stringstream ss;
    ss << hour << ":" << minute << ":" << second;

    if (if_am){
	if (is_am())
	    ss << " am";
	else 
	    ss << " pm";
    }
    string return_string = ss.str();
    return return_string;
}

int Time::get_hour() const {return hour;}
int Time::get_minute() const { return minute;}
int Time::get_second() const {return second;}

bool Time::is_am() {
    if (hour < 13) {
	if_am = true;
	return true;
    }
    else { 
	if_am = true;
	return false;	
    }
}

    
    
