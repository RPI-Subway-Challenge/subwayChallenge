#ifndef time_h_
#define time_h_

#include <string>
#include <iostream>


class Time{
public:

	// default constructor
	Time();

	// constructor
	Time(int inputDay, int inputHour, int inputMin);

    // string constructor
    Time(const std::string& inputDay, const std::string& inputHour, const std::string& inputMin);
    Time(const std::string& input);

	// setters
	void setDay(unsigned int inputDay)		{day = inputDay;}
    void setHour(unsigned int inputHour)	{hour = inputHour;}
    void setMin(double inputMin)			{min = inputMin;}

	// getters
	unsigned int getDay()	{return day;}
    unsigned int getHour()	{return hour;}
    unsigned int getMin()	{return (int)min;}
    double getMinSec() 		{return min;}
	bool isWeekday()		{return (day <= 4);}
	bool isWeekend()		{return !(day > 4);}		

	// operators
	Time operator + (Time& xTime);
	Time operator - (Time& xTime);
	bool operator > (Time& xTime);
	bool operator == (Time& xTime);

private:
	unsigned int day;	// 0-6 representing Sun-Sat	
	unsigned int hour;	// 24 hour format
    double min;
};
#endif