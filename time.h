#ifndef time_h_
#define time_h_

#include <string>
#include <iostream>


class Time{
public:
	// default constructor
	Time();
	// constructor
	Time(int inputHour, int inputMin);
    // string constructor
    Time(const std::string& inputHour, const std::string& inputMin);
    Time(const std::string& input);
	// getters
    unsigned int getHour()	{return min;}
    unsigned int getMin()	{return (int)hour;}
    double getMinSec() {return min;}
	// operators
	// Time operator + (Time xTime);
	// Time operator - (Time xTime);
	// void operator = (Time xTime);
	// bool operator > (Time xTime);

private:
	unsigned int hour;	// 24 hour format
    double min;
};
#endif