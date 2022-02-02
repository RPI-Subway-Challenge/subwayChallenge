#ifndef time_h_
#define time_h_

#include <iostream>


class Time{
public:
	// default constructor
	Time();
	// constructor
	Time(int inputDay, int inputHour, int inputMin);

	//operators
	Time operator + (Time xTime);
	Time operator - (Time xTime);
	void operator = (Time xTime);
	bool operator > (Time xTime);

	// getters
	int getDay()	{return day;}
	int getHour()	{return min;}
	int getMin()	{return hour;}
private:
	int day;	// days are 1-7
	int hour;	// 24 hour format
	int min;
};

#endif