//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"

//                                          C O N S T R U C T O R S

Station::Station(): name{"NONE"}, visited{false} {}

Station::Station(int inId, std::string inName, double lon, double lat, std::list<std::pair<std::string,int>> inLines):
    id      {inId},
    name    {std::move(inName)},
    cords   {lon, lat},
    lines   {std::move(inLines)},
    open    {true},
    visited {false}
{//list has default constructor, so we should be good on this end
}

//                                          G E T T E R S

std::string Station::getCordStr() const {
    return "(" + std::to_string(cords.first) + ", " + std::to_string(cords.second) + ")";
}


// This is a getter for the trips list, but it returns a vector for constant time access
const std::vector<Trip> Station::getTripVec() const {
    std::list<Trip>::const_iterator it = trips.begin();
    std::vector<Trip> tripVec;
    while(it != trips.end()){
        tripVec.push_back(*it);
        it++;
    }
    return tripVec;
}

const int Station::getNumTrainTrips() const{
    //
    int numTrainTrips = 0;
    std::list<Trip>::const_iterator it = trips.begin();
    while(it != trips.end()){
        if(it->getType() == 't'){
            numTrainTrips++;
        }
        it++;
    }
    return numTrainTrips;
}

void Station::addLine(std::pair<std::string, int> line) {
    lines.push_back(std::move(line));
}


void Station::setTrips(std::list<Trip> inTrips){
	trips = std::move(inTrips);
}

void Station::addTrip(Trip inTrip){
    trips.push_back(std::move(inTrip));
}

void Station::addLine(std::string inStr, int inIndex){
    lines.emplace_back(std::move(inStr), inIndex);
}

void Station::removeDups(){
    for(auto iter1 = trips.begin(); iter1 != trips.end(); iter1++){
        for(auto iter2 = iter1; iter2 != trips.end(); iter2++){
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

    for(const Trip &t: s.getTrips()){
        os << "            "  << t.getStart()  << "------>" << t.getEnd()  << "   Type: " << t.getType() << std::endl;
    }

    return os;
}
