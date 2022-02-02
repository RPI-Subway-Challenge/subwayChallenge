//																	D O W N    W I T H    M A T T H E W    A H N

#include "trip.h"

Trip::Trip(){
	startIndex = -1;
    endIndex = -1;
}



Trip::Trip(int inStart, int inEnd, int inDuration, char inType, std::list<Time> inWeekend, std::list<Time> inWeekday){
	startIndex = inStart;
	endIndex = inEnd;
	duration = inDuration;
	type = inType;
	inWeekend = NULL;
	inWeekday = NULL;				// defaults to open
	open = true;				// list of trips assigned in setTrips not constructor
}

