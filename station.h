//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef station_h_
#define station_h_

#include <iostream>
#include <utility>	// pair
#include <string>
#include <vector>
#include <list>



/*class Time{
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
};*/



class Station{
public:
	// defualt constructor
	Station();

	// constructor
	Station(std::string inputName);

	// setters
	void addLine(int lineNum, int position);

	// getters
	std::string getName(){return name;}



private:
	std::string name;
	std::list<std::pair<int, int>> linePos;

//	std::vector<Time>weekday;
//	std::vector<Time>weekend;

};

#endif