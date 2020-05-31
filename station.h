//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef station_h_
#define station_h_

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <list>





class Time{
public:
	// default constructor
	Time();

	// constructor
	Time(int inputDay, int inputHour, int inputMinute);

	// operators
	Time operator + (Time addedTime);
	Time operator - (Time addedTime);
	void operator = (Time comparedTime);
	bool operator > (Time comparedTime);

	// setters
	void setDay(int inputDay)		{day = inputDay;}
	void setHour(int inputHour)		{hour = inputHour;}
	void setMinute(int inputMinute)	{minute = inputMinute;}

	// getters
	int getDay()		{return day;}
	int getHour()		{return hour;}
	int getMinute()		{return minute;}

private:
	int day;
	int hour;
	int minute;
};





class Route{
public:
	// constructor
	Route();

	// operator =
	void operator = (Route &route);

	// setters
	void addDuration(Time inputDuration)						{duration = duration + inputDuration;}
	void subDuration(Time inputDuration)						{duration = duration - inputDuration;}
	void addStation(std::pair<std::string,bool> inputStation)	{path.push_back(inputStation);}
	void popStation()											{path.pop_back();}

	// getters
	Time & getDuration()										{return duration;}
	std::list<std::pair<std::string, bool>> & getPath()			{return path;}

private:
	Time duration;
	std::list<std::pair<std::string, bool>> path;
};





class Station{
public:
	// default constructor
	Station();

	// constructor for connections to uninitalized stations
	Station(std::string &inputName, int inputHash);

	// constructor
	Station(std::string &inputName, int inputHash, std::list<std::string> &inputLines, std::vector<std::pair<Time,Time>> &inputHours,
			std::list<std::pair<int,Time>> &inputTrains, std::list<std::pair<int,Time>> &inputWalks);

	//setters
	void setLines(std::list<std::string> &inputLines)				{lines = inputLines;}
	void setHours(std::vector<std::pair<Time,Time>> &inputHours)	{hours = inputHours;}
	void setTrains(std::list<std::pair<int,Time>> &inputTrains)		{trains = inputTrains;}
	void setWalks(std::list<std::pair<int,Time>> &inputWalks)		{walks = inputWalks;}
	void setVisited()												{visited = true;}
	void setUnvisited()												{visited = false;}

	// getters
	std::string & getName()										{return name;}
	std::list<std::string> & getLines()							{return lines;}
	std::pair<Time,Time> & getHours(int day)					{return hours[day];}
	std::list<std::pair<int,Time>> & getTrains()				{return trains;}
	std::list<std::pair<int,Time>> & getWalks()					{return trains;}
	bool getVisited()											{return visited;}


private:
	std::string name;
	int hash;
	std::list<std::string> lines;
	std::vector<std::pair<Time,Time>> hours;	// vector size 7 for days
	std::list<std::pair<int,Time>> trains;		// list of pairs containing hash of next stations & train duration
	std::list<std::pair<int,Time>> walks;		// list of pairs containing hash of next stations & walk duration
	bool visited;
};




#endif