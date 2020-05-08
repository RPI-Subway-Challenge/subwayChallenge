//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

class Hashtable{
public:

	// constructor
	Hashtable(int startDay, int startTime);

	// hash function
	int hash(std::string &inputName);
	// hash function but returns index when found station
	int findHash(std::string &inputName);

	// recursive path find
	void findPath(Station* ptr, int visted);

	//setters
	void addStation(int inputHash, Station &inputStation);
	void addOcc()			{occupancy++;}

	// getters
	int getDay()			{return day;}
	int getTime()			{return time;}
	int getSize()			{return size;}
	int getOccupancy()		{return occupancy;}
	int getDuration()		{return duration;}
	int getBestDuration()	{return bestDuration;}

private:
	int day;
	int time;

	int size;
	int occupancy;
	int maxProbe;		// furthest distance linear probe has gone

	int duration;
	int bestDuration;

	std::vector<Station> table;



};
