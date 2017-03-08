#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Time.h"

using namespace std;

// här lägger ni era testfall. 
// Jobba enligt TDD; 
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut

TEST_CASE ("Default constructor")
{
    Time t;

    CHECK(t.get_hour() == 0);
    CHECK(t.get_minute() == 0);
    CHECK(t.get_second() == 0);
}
TEST_CASE ( "Constructor with numeric arguments" )
{
    Time t{12,13,14};
    CHECK(t.get_hour() == 12);
    CHECK(t.get_minute() == 13);
    CHECK(t.get_second() == 14);
}
TEST_CASE ("Constructor with faulty argument")
{
    CHECK_THROWS(( Time{41,0,0} ));
    CHECK_THROWS(( Time{0,99,0} ));
    CHECK_THROWS(( Time{0,0,99} ));
}
TEST_CASE ("String constructor")
{
    Time t{"12:23:12"};
    CHECK(t.get_hour() == 12);
    CHECK(t.get_minute() == 23);
    CHECK(t.get_second() == 12);

    SECTION ("Throws as well")
    {
        CHECK_THROWS(( Time{"02:11:74"} ));
    }
}
TEST_CASE ("am or pm")
{
    Time t{12,12,31};
    CHECK_FALSE(t.is_am());
    Time t2{1,2,3};
    CHECK(t2.is_am());
}
TEST_CASE ("Convert to string" )
{
    CHECK(( Time{12,12,12}.to_string(false)     ==    "12:12:12" ));
    CHECK(( Time{12, 1, 2}.to_string(false)     ==    "12:01:02" ));
    CHECK(( Time{14,33,12}.to_string(true)      ==    "02:33:12 pm" ));
}
TEST_CASE ("Conversion to string" )
{
    CHECK(( string(Time{2,4,1}) == "02:04:01" ));
}

TEST_CASE ("Output operator" )
{
    stringstream ss;
    SECTION("Simple output")
    {
        ss << Time{2,5,1};
        CHECK(ss.str() == "02:05:01");
    }
    SECTION("Chained output")
    {
        ss << Time{23,10,32} << "---";
        CHECK(ss.str() == "23:10:32---");
    }
    SECTION("Const time")
    {
        Time const t{23,23,23};
        ss << t;
        CHECK(ss.str() == "23:23:23");
    }
}
TEST_CASE ("Add" )
{
    Time t2{0,0,0};
    Time t{t2+64};

    CHECK(t.get_hour() == 0);
    CHECK(t.get_minute() == 1);
    CHECK(t.get_second() == 4);
    
}
TEST_CASE ("increment" )
{
    Time t2{0,0,0};
    Time t3{++t2};
    Time t4{t2++};

    CHECK(t2.get_hour() == 0);
    CHECK(t2.get_minute() == 0);
    CHECK(t2.get_second() == 2);

    CHECK(t3.get_hour() == 0);
    CHECK(t3.get_minute() == 0);
    CHECK(t3.get_second() == 1);

    CHECK(t4.get_hour() == 0);
    CHECK(t4.get_minute() == 0);
    CHECK(t4.get_second() == 1);
    
    
}
TEST_CASE ("decrement" )
{
    Time t2{0,0,4};
    Time t3{--t2};
    Time t4{t2--};

    CHECK(t2.get_hour() == 0);
    CHECK(t2.get_minute() == 0);
    CHECK(t2.get_second() == 2);

    CHECK(t3.get_hour() == 0);
    CHECK(t3.get_minute() == 0);
    CHECK(t3.get_second() == 3);

    CHECK(t4.get_hour() == 0);
    CHECK(t4.get_minute() == 0);
    CHECK(t4.get_second() == 3);
    
}
TEST_CASE ("Sub" )
{
   Time t2{0,1,5};
   Time t{t2-64};

   CHECK(t.get_hour() == 0);
   CHECK(t.get_minute() == 0);
   CHECK(t.get_second() == 1);
}
TEST_CASE ("More/less" )
{
    Time t{2,1,1};
    CHECK((t>Time{1,2,2}));
    CHECK_FALSE((t<Time{1,2,2}));
    CHECK((t>=Time{1,2,2}));
    CHECK_FALSE((t<=Time{1,2,2}));
    CHECK_FALSE((t==Time{1,2,2}));
    CHECK((t!=Time{1,2,2}));
}
TEST_CASE ("Operator")
{
    Time t1{23,10,57}, t2;
    stringstream ss;
    ss << t1; 
    ss >> t2;
    CHECK(ss.fail() == false);
    CHECK(string(t1) == "23:10:57");

    ss << "25:01:01";
    ss >> t1;
    CHECK(ss.fail());
}
TEST_CASE ("test")
{
    Time t{10,20,30};
    CHECK(t.to_string() == "10:20:30");
}
TEST_CASE ("test1")
{
    Time t{3,3,3};
    CHECK(t.to_string(true) == "03:03:03 am");
}
TEST_CASE ("test2")
{
    Time t{3,3,3};
    CHECK(string(t) == "03:03:03");
}

TEST_CASE ("test3")
{
    Time t_am{3,3,3};
    CHECK(t_am.is_am());
}


TEST_CASE("Input fail result")
{

    std::stringstream ss{"-2:02:02"};
    Time t;

    CHECK_NOTHROW(ss >> t);

    CHECK(ss.fail());


    INFO("If we try to read an invalid time from the stream "
            "and the failbit is set, the time object we're reading "
            "to should not be left in an invalid state");
    CHECK_FALSE(t.to_string() == "-2:02:2");

    ss.clear();

    ss.str("25:02:02");
    CHECK_NOTHROW(ss >> t);

    CHECK(ss.fail());
    CHECK_FALSE(t.to_string() == "25:02:02");
}
