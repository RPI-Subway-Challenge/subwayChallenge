//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef trip_h_
#define trip_h_

#include <list>
#include "time.h"


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
	int getStart() const  						{return startIndex;}
	int getEnd() const						    {return endIndex;}
	int getDuration() const						{return duration;}
	const std::string &getLineName() const		{return lineName;}
	char getType() const							{return type;}
	bool isOpenWeekdays() const					{return weekdayStart.size();}
	bool isOpenWeekends() const					{return weekendStart.size();}
	int isOpen(Time current) const				{return (open && isOpenWeekdays() && isOpenWeekends());}
	Time timeToNextDeparture(Time current) const;		// only works on open stations
	bool isDup(const Trip& t) const;					// duplicate if all same but lineName

	// operators
	bool operator==(const Trip& xTrip) const;

private:
	int startIndex;                 // index of station at start & end, simplier than pointers
	int endIndex;
	int duration;
	std::string lineName; /* TODO warning inefficient memory consumption */
	char type;						// method of transportation e.g. t: train
	std::list<Time> weekdayStart;	// when trains leave from start on weekdays
	std::list<Time> weekendStart;	// when trains leave from start on weekends
	bool open;
};

bool operator<(const Trip &, const Trip &);
bool operator>(const Trip &, const Trip &);

#endif