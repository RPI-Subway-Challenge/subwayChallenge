//																	D O W N    W I T H    M A T T H E W    A H N

#include <iostream>
#include <utility>		// pair
#include <string>
#include <vector>
#include <list>

class Station{
public:
	// default constructor
	Station();

	// constructor
	Station(std::string inputName, int inputHash, std::list<char> inputLines, std::vector<std::pair<int,int>> inputHours,
									std::list<std::pair<int,int>> inputTrains, std::list<std::pair<int,int>> inputWalks);
	// getters
	std::string getName()						{return name;}
	std::list<char> getLines()					{return lines;}
	std::pair<int,int> getHours(int day)		{return hours[day];}
	std::list<std::pair<int,int>> getTrains()	{return trains;}
	std::list<std::pair<int,int>> getWalks()	{return trains;}


private:
	std::string name;
	int hash;
	std::list<char> lines;
	std::vector<std::pair<int,int>> hours;		// vector size 7 for days
	std::list<std::pair<int,int>> trains;		// list of pairs containing hash of next stations & train duration
	std::list<std::pair<int,int>> walks;		// list of pairs containing hash of next stations & walk duration

};