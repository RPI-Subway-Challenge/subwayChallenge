//																	D O W N    W I T H    M A T T H E W    A H N

#include "line.h"

//                                          C O N S T R U C T O R S
Line(){
    name = NULL;
    int = -1
}

Line::Line(int inID, const std::string& inName){
    id = inID;
    name = inName;
}



//                                          S E T T E R S

void Line::addStation(const int stationIndex){
    lines.push_back(stationIndex);
}
