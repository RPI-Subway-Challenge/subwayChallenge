//																	D O W N    W I T H    M A T T H E W    A H N

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

Time Trip::timeToNextDeparture(Time current){
	// only works if called on open trip
	
	std::list<Time>::iterator weekday_it = weekdayStart.begin();
	Time ClosestTime = *weekday_it;
	for(std::list<Time>::iterator weekday_it = weekdayStart.begin(); weekday_it != weekdayStart.end(); ++weekday_it){
		if (ClosestTime > *weekday_it){
			ClosestTime = *weekday_it;
		}
	}
	for(std::list<Time>::iterator weekend_it = weekendStart.begin(); weekend_it != weekendStart.end(); ++weekend_it){
		if (ClosestTime > *weekend_it){
			ClosestTime = *weekend_it;
		}
	}

	return ClosestTime;
}

// duplicate if all same but lineName
bool Trip::isDup(Trip& t){
	if( this->getStart()==t.getStart() && this->getEnd()==t.getEnd() && this->getDuration()==t.getDuration() && this->getType()==t.getType() ){
		if( lineName != t.getLineName() ){
			return true;
		}
	}
	return false;
}


//												O P E R A T O R S

bool Trip::operator > (const Trip& xTrip) const {
	// currently only comparing time, but should consider cost and other variables in future iterations
	return this->getDuration() > xTrip.getDuration();
}
bool Trip::operator== (const Trip& xTrip) const {
	return (startIndex == xTrip.startIndex && endIndex == xTrip.endIndex &&
		duration == xTrip.duration && type == xTrip.type);
};