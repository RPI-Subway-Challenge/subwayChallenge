//																	D O W N    W I T H    M A T T H E W    A H N

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <list>

class Station{
public:
	// default constructor
	Station();

	// constructor for connections to uninitalized stations
	Station(std::string &inputName, int inputHash);

	// constructor
	Station(std::string &inputName, int inputHash, std::list<std::string> &inputLines, std::vector<std::pair<int,int>> &inputHours,
			std::list<std::pair<int,int>> &inputTrains, std::list<std::pair<int,int>> &inputWalks);

	// update incomplete info from 2nd constructor
	void updateInfo(std::list<std::string> &inputLines, std::vector<std::pair<int,int>> &inputHours,
					std::list<std::pair<int,int>> &inputTrains, std::list<std::pair<int,int>> &inputWalks);

	// getters
	std::string getName()						{return name;}
	std::list<std::string> getLines()			{return lines;}
	std::pair<int,int> getHours(int day)		{return hours[day];}
	std::list<std::pair<int,int>> getTrains()	{return trains;}
	std::list<std::pair<int,int>> getWalks()	{return trains;}


private:
	std::string name;
	int hash;
	std::list<std::string> lines;
	std::vector<std::pair<int,int>> hours;		// vector size 7 for days
	std::list<std::pair<int,int>> trains;		// list of pairs containing hash of next stations & train duration
	std::list<std::pair<int,int>> walks;		// list of pairs containing hash of next stations & walk duration

};