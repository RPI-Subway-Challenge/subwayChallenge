//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef trip_h_
#define trip_h_

#include "time.h"
#include <list>


class Trip{

public:

	// default contructor
	Trip();

	// contructor
	Trip(int inStart, int inEnd, int inDuration, char inType, std::list<Time> inWeekend, std::list<Time> inWeekday);

	// setters


	// getters
	

private:

	int startIndex;              // index of station at start & end, simplier than pointers
	int endIndex;
	int duration;
	char type;
	std::list<Time> weekday;		// when trains leave from start on weekdays
	std::list<Time> weekend;		// when trains leave from start on weekends
	bool open;
};



#endif