//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

class Hashtable{
public:
	Hashtable(int startDay, int startTime);

	int Hash(*Station inputStation);

private:
	int size;
	int day
	int time;
	int occupancy;

	int duration;
	int bestDuration;

	std::vector<Station> table;



};
