//																	D O W N    W I T H    M A T T H E W    A H N

#include "trip.h"

//												C O N S T R U C T O R S

Trip::Trip(){
	startIndex = -1;
    endIndex = -1;
}

Trip::Trip(int inStart, int inEnd, int inDuration, char inType, std::list<Time>& inWeekend, std::list<Time>& inWeekday){
	startIndex = inStart;
	endIndex = inEnd;
	duration = inDuration;
	type = inType;
	weekday = inWeekend;
	weekend = inWeekday;				// defaults to open
	open = true;				// list of trips assigned in setTrips not constructor
}


//												S E T T E R S

char Trip::setType(char inType){
	// return type of transportation used
	return type;
}

void Trip::updateTrip(char inType, int inDuration){
	// updates the trip type and duration
	type = inType;
	duration = inDuration;
}

Time Trip::timeToNextDeparture(Time current){
	// only works if called on open trip
	
	std::list<Time>::iterator weekday_it = weekday.begin();
	Time ClosestTime = *weekday_it;
	for(std::list<Time>::iterator weekday_it = weekday.begin(); weekday_it != weekday.end(); ++weekday_it){
		if (ClosestTime > *weekday_it){
			ClosestTime = *weekday_it;
		}
	}
	for(std::list<Time>::iterator weekend_it = weekend.begin(); weekend_it != weekend.end(); ++weekend_it){
		if (ClosestTime > *weekend_it){
			ClosestTime = *weekend_it;
		}
	}

	return ClosestTime;
}


//												O P E R A T O R S

bool Trip::operator > (Trip& xTrip){
	// currently only comparing time, but should consider cost and other variables in future iterations
	return this->getDuration() > xTrip.getDuration();
}
bool Trip::operator == (Trip& xTrip){
	return (this->getStart() == xTrip.getStart() && this->getEnd() == xTrip.getEnd() && 
		this->getDuration() == xTrip.getDuration() && this->getType() == xTrip.getType());
};