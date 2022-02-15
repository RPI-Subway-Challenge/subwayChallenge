//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"



Station::Station(){
	name = "NONE";
}


Station::Station(int inId, const std::string& inName, double lat, double lon, const std::list<std::string>& inLines){
	id = id; // pop
	name = inName;
	cords.first = lat;
	cords.second = lon;
	lines = inLines;
	open = true;				// defaults to open
	//list has default constructor, so we should be good on this end
}

void Station::setTrips(const std::list<Trip>& inTrips){
	trips = inTrips;
}

