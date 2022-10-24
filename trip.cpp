//																	D O W N    W I T H    M A T T H E W    A H N

#include <algorithm>
#include "trip.h"


//												C O N S T R U C T O R S
Trip::Trip(): startIndex{-1}, endIndex{-1} {}

Trip::Trip(int inStart, int inEnd, int inDuration, char inType, std::list<Time>& inWeekend, std::list<Time>& inWeekday){
	startIndex = inStart; // start index of station
	endIndex = inEnd; // end index of station
	duration = inDuration; // is going to be random number
	type = inType; // train bus etc
	weekendStart = inWeekday;				// defaults to open
	open = true;				// list of trips assigned in setTrips not constructor
}


Trip::Trip(int inStart, int inEnd, int inDuration, char inType){
    startIndex = inStart; // start index of station
    endIndex = inEnd; // end index of station
    duration = inDuration; // is going to be random number
    type = inType; // train bus etc
    open = true; // default to open
}

void Trip::setType(char inType){
	// return type of transportation used
	type = inType;
}

void Trip::setLine(std::string inLineName){
	lineName = std::move(inLineName);
}

void Trip::updateTrip(char inType, int inDuration){
	// updates the trip type and duration
	type = inType;
	duration = inDuration;
}

Time Trip::timeToNextDeparture(Time current) const {
	// only works if called on open trip
	return std::min(
		*std::min_element(weekdayStart.begin(), weekdayStart.end()),
		*std::min_element(weekendStart.begin(), weekendStart.end())
	);
}

// duplicate if all same but lineName
bool Trip::isDup(const Trip& t) const {
	if( this->getStart()==t.getStart() && this->getEnd()==t.getEnd() && this->getDuration()==t.getDuration() && this->getType()==t.getType() ){
		if( lineName != t.getLineName() ){
			return true;
		}
	}
	return false;
}


//												O P E R A T O R S

bool Trip::operator==(const Trip& xTrip) const {
	return (startIndex == xTrip.startIndex && endIndex == xTrip.endIndex &&
		duration == xTrip.duration && type == xTrip.type);
}

template<template <class T> class Cmp>
bool cmpOpHelper(const Trip &t0, const Trip &t1) {
	// TODO currently only comparing time, but should consider cost and other variables in future iterations
	return Cmp{}(t0.getDuration(), t1.getDuration());
}

bool operator>(const Trip& t0, const Trip& t1) {
	return cmpOpHelper<std::greater>(t0, t1);
}

bool operator<(const Trip& t0, const Trip& t1) {
	return cmpOpHelper<std::less>(t0, t1);
}
