#include "line.h"


Line::Line(){
    id = -1;
}

Line::Line(int inID, const std::string& inName){
    id = inID;
    name = inName;
}

void Line::addStation(const int stationIndex){
    lineVec.push_back(stationIndex);
}
