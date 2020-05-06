//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

class Hashtable{
public:

	// constructor
	Hashtable(int startDay, int startTime);

	// hash function
	int hash(Station* inputStation);

	// recursive path find
	void findPath(Station* ptr, int visted);

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

	int duration;
	int bestDuration;

	std::vector<Station> table;



};
