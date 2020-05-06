//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

// default constructor
Station::Station(){
	name = "NONE";
}

// constructor
Station::Station(std::string inputName, int inputHash, std::list<char> inputLines, std::vector<std::pair<int,int>> inputHours,
										std::list<std::pair<int,int>> inputTrains, std::list<std::pair<int,int>> inputWalks){
	name = inputName;
	lines = inputLines;
	hours = inputHours;
	trains = inputTrains;
	walks = inputWalks;
}
