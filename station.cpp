//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"



Station::Station(){
	name = "NONE";
}


Station::Station(std::string inName, int inIndex, double lat, double lon, std::list<std::string> inLines){
	name = inName;
	index = inIndex;
	cords.first = lat;
	cords.second = lon;
	lines = inLines;
	open = True;				// defaults to open
	trips = NULL;				// list of trips assigned in setTrips not constructor
}

void Station::setTrips(){

}

