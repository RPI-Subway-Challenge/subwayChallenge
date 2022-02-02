//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef station_h_
#define station_h_

#include "trip.h"
#include <utility>	// pair
#include <string>
#include <vector>



class Station{
public:
	// defualt constructor
	Station();

	// constructor
	Station(std::string inName, int inIndex, double lat, double lon, std::list<std::string> inLines);

	// setters
	void setTrips(std::list<Trip> inTrips);

	// getters
	int getIndex()						{return index;}
	std::string getName()				{return name;}
	std::pair <double,double> getCords(){return cords;}
	std::list<std::string> getLines()	{return lines;}
	std::list<Trip> getTrips()			{return trips;}
	bool getOpen()						{return open;}

private:
	int index;
	std::string name;
	std::pair <double,double> cords;
	std::list<std::string> lines;
	std::list<Trip> trips;
	bool open;
	// ? possibly operating hours

};

#endif