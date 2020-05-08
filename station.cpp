//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

// default constructor
Station::Station(){
	name = "NONE";				// indicator of empty node in hashtable
}

Station::Station(std::string &inputName, int inputHash){
	name = inputName;
	hash = inputHash;
	lines.push_back("NONE");	// indicator of incomplete station in hashtable
}

// constructor
Station::Station(std::string &inputName, int inputHash, std::list<std::string> &inputLines, std::vector<std::pair<int,int>> &inputHours,
				std::list<std::pair<int,int>> &inputTrains, std::list<std::pair<int,int>> &inputWalks){

	name = inputName;
	lines = inputLines;
	hours = inputHours;
	trains = inputTrains;
	walks = inputWalks;
}
