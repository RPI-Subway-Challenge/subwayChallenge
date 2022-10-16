//																	D O W N    W I T H    M A T T H E W    A H N

#ifndef station_h_
#define station_h_

#include "trip.h"
#include <utility>	// pair
#include <vector>
#include "time.h"
#include "set"



class Station{
public:
	// defualt constructor
	Station();

	// constructor
	Station(int id, const std::string& inName, double lon, double LAT, const std::list<std::pair<std::string,int> >& inLines = {});

	// setters
	void setTrips(const std::list<Trip>& inTrips);
	void addTrip(Trip& inTrip);
	void addLine(std::string inStr, int inIndex);
	// void removeTrip(Trip& t)									{trips.remove(t);}
	void removeDups();
    void setVisited(bool isVisited)                             {visited = isVisited;}
    void addLine(const std::pair<std::string, int>& line);
	void setReduced(bool isReduced)                             {reduced = isReduced;}

	// getters
	int getId() const 	 	 				    				{return id;}
	const std::string &getName() const 		        			{return name;}
    const std::list<std::pair<std::string,int>> &getLines() const
	                                                            {return lines;}
    const std::list<Trip> &getTrips() const						{return trips;}
	bool isOpen() const											{return open;}
    bool isVisited() const                                      {return visited;}
	bool isReduced() const                                      {return reduced;}
	std::string getCordStr() const;
	int getNumTrainTrips() const;

    const std::pair<double, double>& getCords() const           {return cords;}

private:
	int id;
	std::string name;
	std::pair<double,double> cords;
	std::list<std::pair<std::string,int> > lines;
	std::list<Trip> trips;
	bool open;
    bool visited;
	bool reduced; // reduced = true if this station is an reduced station
	// ? possibly operating hours
};
std::ostream& operator<<(std::ostream& os, const Station& s);

#endif