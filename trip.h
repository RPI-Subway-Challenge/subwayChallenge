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
	Trip(int inStart, int inEnd, int inDuration, char inType, std::list<Time>& inWeekend, std::list<Time>& inWeekday);
    Trip(int inStart, int inEnd, int inDuration, char inType);

	// setters
	void setType(char inType);
	void updateTrip(char inType, int inDuration);
	void setLine(std::string inLineName);

	// getters
	int getStart()       						{return startIndex;}
	int getEnd() 							    {return endIndex;}
	int getDuration()							{return duration;}
	std::string getLineName()					{return lineName;}
	int getType()								{return type;}
	bool isOpenWeekdays()						{return weekday.size();}
	bool isOpenWeekends()						{return weekend.size();}
	int isOpen(Time current)					{return (open && isOpenWeekdays() && isOpenWeekends());}
	Time timeToNextDeparture(Time current);		// only works on open stations
	bool isDup(Trip& t);						// duplicate if all same but lineName
	
	// operators
	bool operator > (Trip& xTrip)  ;
	bool operator == (Trip& xTrip);

private:
	int startIndex;                 // index of station at start & end, simplier than pointers
	int endIndex;
	int duration;
	std::string lineName;
	char type;						// method of transportation e.g. 0: subway, 1: walking, 2: bus
	std::list<Time> weekday;		// when trains leave from start on weekdays
	std::list<Time> weekend;		// when trains leave from start on weekends
	bool open;
};



#endif