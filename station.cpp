//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

Station::Station(){
	name = "NONE";
}

Station::Station(int inId, const std::string& inName, double lat, double lon, const std::list<std::pair<std::string,int>>& inLines){
	id = inId; // pop
	name = inName;
	cords.first = lat;
	cords.second = lon;
	lines = inLines;
	open = true;				// defaults to open
	//list has default constructor, so we should be good on this end
}

Station::Station(int inId, const std::string& inName, double lon, double lat){
    id = inId; // pop
    name = inName;
    cords.first = lat;
    cords.second = lon;
    open = true;				// defaults to open
    //list has default constructor, so we should be good on this end
}

void Station::setTrips(const std::list<Trip>& inTrips){
	trips = inTrips;
}
std::ostream& operator<<(std::ostream& os, const Station& s){
    os << s.getId() << " | ";
    os << s.getName()<< " | ";
    os << s.getCordStr() << std::endl;

    return os;
}

std::string Station::getCordStr() const {
    return "(" + std::to_string(cords.first) + ", " + std::to_string(cords.second) + ")";
}

