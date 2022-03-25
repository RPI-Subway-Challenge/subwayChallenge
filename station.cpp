//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

//                                          C O N S T R U C T O R S

Station::Station(){
	name = "NONE";
}

Station::Station(int inId, const std::string& inName, double lat, double lon, const std::list<std::pair<std::string,int> >& inLines){
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

//                                          G E T T E R S

std::string Station::getCordStr() const {
    return "(" + std::to_string(cords.first) + ", " + std::to_string(cords.second) + ")";
}


void Station::addLine(const std::pair<std::string, int> &line) {
    lines.push_back(line);
}


void Station::setTrips(const std::list<Trip>& inTrips){
	trips = inTrips;
}

void Station::addTrip(Trip& inTrip){
    trips.push_back(inTrip);
}

void Station::addLine(std::string inStr, int inIndex){
    lines.push_back(std::make_pair(inStr, inIndex));
}

void Station::removeDups(){
    for(std::list<Trip>::iterator iter1 = trips.begin(); iter1 != trips.end(); iter1++){
        for(std::list<Trip>::iterator iter2 = iter1; iter2 != trips.end(); iter2++){
            if( iter1->isDup(*iter2) ){
               iter2 = trips.erase(iter2);
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Station& s){
    os << s.getId() << " | ";
    os << s.getName()<< " | ";
    os << s.getCordStr() << std::endl;
    os << "            Trips";
    os << "            ";

    std::list<Trip> t  = s.getTrips(); // local copy will be deleted
    for(std::list<Trip>::iterator i = t.begin(); i != t.end(); i++){
        os << "            "  << i->getStart()  << "------>" << i->getEnd()  << "   Type: " << i->getType() << std::endl;
    }


    return os;
}