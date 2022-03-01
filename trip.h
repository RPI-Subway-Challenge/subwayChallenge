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
	Trip(int inStart, int inEnd, Time inDuration, char inType, std::list<Time>& inWeekend, std::list<Time>& inWeekday);

	// setters
	char setType(char inType);
	void updateTrip(char inType, Time inDuration);

	// getters
	inline int getStart(){return startIndex;}
	inline int getEnd(){return endIndex;}
	inline Time getDuration(){return duration;}
	inline int getType(){return type;}
	inline bool isOpenWeekdays(){return weekday.size();}
	inline bool isOpenWeekends(){return weekend.size();}
	inline int isOpen(Time current){return (open && isOpenWeekdays() && isOpenWeekends());}
	inline Time timeToNextDeparture(Time current);			// only works on open stations
	
	// operators
	bool operator > (Trip& xTrip);
	bool operator == (Trip& xTrip);

private:
	int startIndex;                 // index of station at start & end, simplier than pointers
	int endIndex;
	Time duration;
	char type;						// method of transportation e.g. 0: subway, 1: walking, 2: bus
	std::list<Time> weekday;		// when trains leave from start on weekdays
	std::list<Time> weekend;		// when trains leave from start on weekends
	bool open;
};



#endif