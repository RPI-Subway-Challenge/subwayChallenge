#include "line.h"


Line::Line(): id{-1} {}

Line::Line(int inID, std::string inName): id{inID}, name{std::move(inName)}
{}

void Line::addStation(const int stationIndex){
    lineVec.push_back(stationIndex);
}
