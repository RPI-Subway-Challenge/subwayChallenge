#include "line.h"


Line::Line(){
    id = -1;
    numStations = 0;
}

Line::Line(int inID, const std::string& inName){
    id = inID;
    name = inName;
    numStations = 0;
}

void Line::addStation(const int stationIndex){
    lineVec.push_back(stationIndex);
    numStations++;
}
