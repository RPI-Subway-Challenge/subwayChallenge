//																	D O W N    W I T H    M A T T H E W    A H N

#include <iostream>
#include <utility>
#include <string>




class Station{
public:
	// constructor
	Station(std::string inputName, int inputHash, std::list<char> inputLines, std::vector<std::pair<int,int>> inputHours, std::list<Routes> inputRoutes);

	// getters
	std::string getName()					{return name;}
	std::list<char> getLines()				{return lines;}
	std::pair<int,int> getHours(int day)	{return hours[day];}
	std::list<Route> getRoutes()			{return routes;}

private:
	std::string name;
	int hash;
	std::list<char> lines;
	std::vector<std::pair<int,int>> hours;		// vector size 7 for days
	std::list<int> trains;						// list of hashs of next stations
	std::list<int> walks;						// list of hashs of next stations

};