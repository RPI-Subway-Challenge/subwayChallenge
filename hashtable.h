//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef hashtable_h_
#define hashtable_h_

#include "station.h"

class Hashtable{
public:

	// constructor
	Hashtable(Time startTime);

	// hash function
	int hash(std::string &inputName);
	// hash function but returns index when found station
	int findHash(std::string &inputName);

	// recursive path find
	void findPath(Station* & ptr, int visted, Route &route);

	//setters
	void addStation(int inputHash, Station &inputStation);
	void updateStation(int inputHash, std::list<std::string> &inputLines, std::vector<std::pair<Time,Time>> &inputHours,
						std::list<std::pair<int,Time>> &inputTrains, std::list<std::pair<int,Time>> &inputWalks);

	// getters
	Time getTime()						{return time;}
	int getSize()						{return size;}
	int getOccupancy()					{return occupancy;}
	Time getBestDuration()				{return bestDuration;}
	Route & getBestRoute()				{return bestRoute;}
	Station & getStation(int inputHash)	{return table[inputHash];}

private:
	Time time;

	int size;
	int occupancy;
	int maxProbe;		// furthest distance linear probe has gone

	Time bestDuration;

	Route bestRoute;

	std::vector<Station> table;



};


#endif