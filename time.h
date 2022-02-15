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
    //String constructor
    Time(const std::string& inputHour, const std::string& inputMin);

    Time(const std::string& input)
    //operators
	Time operator + (Time xTime);
	Time operator - (Time xTime);
	void operator = (Time xTime);
	bool operator > (Time xTime);

	// getters
    unsigned int getHour()	{return min;}
    unsigned int getMin()	{return (int)hour;}
    unsigned double getMinSec() {return min;}
private:
	unsigned int hour;	// 24 hour format
    unsigned double min;
};

#endif